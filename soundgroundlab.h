
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
* Module:   soundgroundlab.h                                                  *
******************************************************************************/

#include <stdio.h>

void sgl_stereosample_processing(void (*stereosample_func) (unsigned long,short*,short*));
