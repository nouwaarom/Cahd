/*
Copyright 2013 Elbert van de Put

TODO:
add more functions for the control and transfer protocol
updata data types
*/
#ifndef PROTOCONTROLLER_H
#define PROTOCONTROLLER_H

//includes:
#include "defines.h"
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

//defines:
#define ERROR_FILE_TOO_LARGE 0xEFFF0001
#define MAX_PORTS    100

//data types:
typedef enum{
upload,
message,
control,
transfer
} protocolType;

typedef struct{
protocolType type;
int fd;
} protocol;

//functions:
int loadProtocol(protocol *self, char *fileName);
int openPort(protocol *self, char *portName);
int uploadFile(protocol *self, char *fileName);
int closePort(protocol *self);
#endif

