/*
Copyright 2013 Elbert van de Put
*/
#ifndef MEMORY_H
#define MEMORY_H
//this file contains the data structure used by simultor and schematizer
#include <glib.h>

//general purpose
typedef enum {
AND,
OR,
NOT,
XOR,
//this is the best way
MODULE
} GateType;

typedef struct {
//type
GateType type;
//connections
int inputSize;
int inputsHigh;

//if the output is a negative number it means it is an output
int output[8];
int outputSize;

int moduleID;

gboolean state;
} Gate;

typedef struct {
int ID;
Gate gates[128];
int gateSize;

//input array is used to indicate in compiler and is boolean array in simulator
int input[32];
int inputSize;
int inputGate[32][8];
int inputGateSize[32];

int output[32];
int outputSize;
} Module;

//simulator

//scheme
typedef enum {
GATE,
INPUT,
OUTPUT,
CONNECTION
} PosType;

//TODO: find a good way for the grid to communicate with the gate array
typedef struct {
short ID;
PosType type;
gboolean state;
gboolean occupied;
} Cell;

#endif
