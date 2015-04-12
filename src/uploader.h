/*
Copyright 2013 Elbert van de Put
*/
#ifndef UPLOADER_H
#define UPLOADER_H

//includes:
#include "defines.h"
#include "protocontroller.h"

//data types:
typedef enum{
Elbert
} fpgaPlatform;

//functions:
int uploadDesign(fpgaPlatform platform, char *fileName, char *portName);

#endif
