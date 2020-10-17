
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
* Module:   soundgroundlab.c                                                  *
******************************************************************************/

#include <stdio.h>
#include "soundgroundlab.h"

void sgl_stereosample_processing(void (*stereosample_func) (unsigned long,short*,short*))
{
   char *fgetsretVal = 0;
   char buffer[80];
   char type[80];
   unsigned long sample = 0;

   short l,r;

   while(1)
   {
      fgetsretVal=fgets(buffer,80,stdin);

      if(fgetsretVal==NULL)
      {
         break;
      }

      if(buffer[0] == 'S')
      {  
	 sscanf(buffer,"%s %hi %hi",type,&l,&r);
	 sample++;
	 stereosample_func(sample,&l,&r);
         printf("STEREOSAMPLE %hi %hi\n",l,r);
      }
      else
      {
         printf("%s",buffer);
      }
   }
}
