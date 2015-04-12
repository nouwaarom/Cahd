/*
Copyright 2013 Elbert van de Put
*/
#ifndef PLACER_H
#define PLACER_H
//includes:
#include "defines.h"
#include <math.h>
#include "memory.h"

//global data:
float **inverse;

//function:
void quadraticPlace(Module *modules, Cell ***grid);

float determinant(float **a, float k);
void cofactor (float **num,float f);
void transpose(float **num,float **fac,float r);

#endif
