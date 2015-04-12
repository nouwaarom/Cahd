/*
Copyright 2013 Elbert van de Put
*/
#ifndef COMPILER_H
#define COMPILER_H
//FIXME I think gLib uses quarks so now the program doesn't work correctly

//includes:
#include <glib.h>
#include <glib/gstdio.h>
#include "memory.h"
#include "logs.h"

//functions:
guint32 isOperation(GScanner *scanner, Module *module);

//searches for a valid argument
guint32 getArgument(GScanner *scanner, Module *module, int mode);

guint compile(GScanner *scanner, Module *moduleArray);

int compileEntry(Module *moduleArray, char *fileName);

#endif
