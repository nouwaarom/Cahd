/*
Copyright 2013 Elbert van de Put
*/
#ifndef SCHEMATIZER_H
#define SCHEMATIZER_H
//includes:
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include "memory.h"
#include "placer.h"

//global declarations
Cell _grid[128][96];

//functions:
void fillGrid(Module *modules, GtkWidget *area);

void drawGrid(cairo_t *cairo, Module module, int width, int height);

gboolean inputGrid(Module *modules, GtkWidget *area, int width, int height, double x, double y);

void updateGrid(Module *modules, GtkWidget *area);
#endif
