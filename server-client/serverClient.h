//
// Created by qwerty on 12.01.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef UNTITLED1_SERVERCLIENT_H
#define UNTITLED1_SERVERCLIENT_H

void saveFile(FILE* f,char* sending,char* msg)
{
    fprintf(f,"\nDate: %s-%s\n",__DATE__,__TIME__);
    fprintf(f,"User: %s",sending);
    fprintf(f,"You:  %s",msg);
}

#endif //UNTITLED1_SERVERCLIENT_H
