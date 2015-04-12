/*
Copyright 2013 Elbert van de Put
*/
#include "schematizer.h"
#include <glib/gstdio.h>

//fill the grid
void fillGrid(Module *modules, GtkWidget *area)
{
	//run the placement algorithm
	quadraticPlace(modules, &_grid);
    
    //run the local routing algorithm
    
    //run the global routing algorithm
    
    //check if the produced grid is valid
	
    gtk_widget_queue_draw(area);
    return;
}

//draw the grid
void drawGrid(cairo_t *cairo, Module module, int width, int height)
{   
	double rowWidth = (double)(width / 128.0);
	double columnHeight = (double)(height / 96.0);
	int i, j;
	char gateNames[4][4] = {"And", "Or", "Not", "Xor"};
	
	//initialization
    cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cairo, 8.0);
    cairo_set_line_width(cairo, 0.2);
    cairo_set_source_rgb(cairo, 0.33, 0.33, 0.33);
	
	//horizontal lines
	for(i = 0; i <= 96; i++)
	{
		cairo_move_to(cairo, 0.0,   (double)(i * columnHeight));
		cairo_line_to(cairo, width, (double)(i * columnHeight));
		cairo_stroke(cairo);
	}
	//vertical lines
	for(i = 0; i <= 128; i++)
	{
		cairo_move_to(cairo, (double)(i * rowWidth), 0.0);
		cairo_line_to(cairo, (double)(i * rowWidth), height);
		cairo_stroke(cairo);
	}
	
	//blocks
	cairo_set_line_width(cairo, 0.6);
	
	for(i = 0; i < 128; i++)
	{
		for(j = 0; j < 96; j++)
		{
			if(_grid[i][j].occupied == TRUE)
			{
				//give different colors to all types
				if(_grid[i][j].type == INPUT)
					cairo_set_source_rgb(cairo, 1.0, 0.0, 0.0);
				else if(_grid[i][j].type == OUTPUT)
					cairo_set_source_rgb(cairo, 0.7, 0.0, 0.0);
				else if(_grid[i][j].type == GATE)
				{
					cairo_set_source_rgb(cairo, 0.0, 0.0, 0.5);
					cairo_move_to(cairo, (double)(rowWidth*i), (double)(columnHeight*j)+columnHeight);
					cairo_show_text(cairo, gateNames[ module.gates[ _grid[i][j].ID ].type ]);
					char buffer[4];
					g_sprintf(buffer, ":%d",_grid[i][j].ID);
					cairo_show_text(cairo, buffer);
				}

				cairo_rectangle(cairo, (double)(rowWidth*i), 
								       (double)(columnHeight*j),
								  	   rowWidth , columnHeight);
				if(_grid[i][j].state == TRUE)
					cairo_fill(cairo);			
				
				cairo_stroke(cairo);
				
			}
		}
	}
	
    return;   
}

//respond to input on the grid
gboolean inputGrid(Module *modules, GtkWidget *area, int width, int height, double x, double y)
{	
	double rowWidth = (double)(width / 128.0);
	double columnHeight = (double)(height / 96.0);
	
	int row = floor(x / rowWidth);
	int column = floor(y / columnHeight);
	
	if(_grid[row][column].occupied && _grid[row][column].type == INPUT)
	{
		if(_grid[row][column].state == TRUE)
		{
			_grid[row][column].state = FALSE;
			modules->input[ _grid[row][column].ID ] = FALSE;
		}
		else
		{
			_grid[row][column].state = TRUE;
			modules->input[ _grid[row][column].ID ] = TRUE;
		}
	}
	
	gtk_widget_queue_draw(area);
	return(TRUE);
}

//upate the grid according to the state of the modules
void updateGrid(Module *modules, GtkWidget *area)
{
	int x, y;
	int i;
	
	for(x = 0; x < 128; x++)
	{
		for(y = 0; y < 96; y++)
		{
			//update the output
			if(_grid[x][y].type == OUTPUT)
			{
				if(modules->gates[ _grid[x][y].ID ].inputsHigh)
					_grid[x][y].state = TRUE;
				else
					_grid[x][y].state = FALSE;
			}
			
			//update the gates
			if(_grid[x][y].type == GATE)
			{
				if(modules->gates[ _grid[x][y].ID ].state)
					_grid[x][y].state = TRUE;
				else
					_grid[x][y].state = FALSE;
			}
			
			//update the wiring
		}
	}
	
	gtk_widget_queue_draw(area);
	return;
}

