/*
Copyright 2013 Elbert van de Put
*/
#ifndef SIMULATOR_H
#define SIMULATOR_H
//includes:
#include "memory.h"
#include <glib.h>
//functions
void simulate(Module *modules);

gboolean updateStatus(Gate *gate);
#endif
