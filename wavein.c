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
* Module:   wavein (prototype)                                                *
******************************************************************************/

#include<string.h>
#include<stdio.h>

void tool_description()
{
   /* Tool Description*/
}

int main(int argc, char **argv)
{
   FILE *fp;

   //fp = fopen(argv[1],"rb");
   fp = fopen("test.wav","rb");

   if(fp==NULL)
   {
      return 1;
   }
   short i = 0;
   char data = 0;
   int countdown = 4;
   int read = 0;
   int x = 0; 
   int head;
   char history[5];
   char channel = 'l';

   while(1)
   {
      if(data && countdown==0)
      {
	 if(read != 1)
	 {
	    read = 1;
	    printf("\n");
	 }
         fread(&i,2,1,fp);
      }
      else
      {
         head = fgetc(fp);
	 if(data)
	 {
	    (countdown!=0)?countdown--:0;
	 }
      }

      if(feof(fp))
      {
         break;
      }
      
      history[0] = history[1];
      history[1] = history[2];
      history[2] = history[3];
      history[3] = head;
      history[4] = '\n';
      
      
      if(data == 0 &&
	 history[0] == 0x64 &&
         history[1] == 0x61 &&
         history[2] == 0x74 &&
         history[3] == 0x61)
      {
         data = 1;
      }

      if(read)
      {
         if(channel=='r')
	 {
	    channel = 'l';
            //printf("( %d %04X)\n",i,i&0xFFFF);
            printf("%d \n",i);
	 }
	 else
	 {
	    channel = 'r';
           // printf("STEREOSAMPLE ( %d %04X ) ",i,i&0xFFFF);
           printf("STEREOSAMPLE %d ",i);
	    
	 }
      }
      else
      {
         printf("HEAD %02X\n",head);
      }

   }

   return 0;
}
