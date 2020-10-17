
/******************************************************************************
 ____                      _                                 _ _         _     
/ ___| ___  _   _ _ __  __| | __ _ _ __ ___  _   _ _ __   __| | |   __ _| |__  
\___ \/ _ \| | | | '_ \/ _` |/ _` | '__/ _ \| | | | '_ \ / _` | |  / _` | '_ \
 ___)  (_) | |_| | | |  (_| | (_| | | | (_) | |_| | | | | (_| | |_| (_| | |_) |
|____/\___/ \__,_|_| |_\__,_|\__, |_|  \___/ \__,_|_| |_|\__,_|____\__,_|_.__/ 
                             |___/                                             
*******************************************************************************
* Autor:    Benjamin Hedert                                     Oktober 2020  *
* Version:  0.01                                                              *
* Module:   waveout (prototype)                                               *
******************************************************************************/

#include <stdio.h>

int main()
{
   FILE *fp;

   fp = fopen("raus.wav","wb");

   if(fp==NULL)
   {
      return 1;
   }

   char *fgetsretVal = 0;
   char buffer[80];
   char type[80];

   int x;
   short l,r;

   while(1)
   {
      fgetsretVal=fgets(buffer,80,stdin);

      if(fgetsretVal==NULL)
      {
         break;
      }

      if(buffer[0] == 'H')
      {
         //puts("HEAD DETECTED");
	 sscanf(buffer,"%s %X",type,&x);
	 //printf("HEX: %X  %c\n",x,x);
	 fprintf(fp,"%c",x);
      }
      if(buffer[0] == 'S')
      {  
	 sscanf(buffer,"%s %hi %hi",type,&l,&r);

	 fwrite(&l,2,1,fp);
	 fwrite(&r,2,1,fp);
      }
   }
   return 0;
}
