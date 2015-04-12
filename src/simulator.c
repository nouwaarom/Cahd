/*
Copyright 2013, 2014 Elbert van de Put

TODO:
add support for module calls
*/
#include "simulator.h"
#include <glib/gstdio.h>

//module 0 is entry other modules get called from entry or modules called by entry
void simulate(Module *modules)
{
    int i, j;
    int index;

    g_printf("\nSIMULATING...\n");

    g_printf("module0ID:%d\n", modules[0].ID);
    g_printf("module1ID:%d\n", modules[1].ID);

	//start at input
	g_printf("\nInput:");
	for(i = 0; i < modules->inputSize; i++)
	{
		//check if we got input
		if(modules->input[i] == TRUE)
		{
			//notify all connected outputs
			for(j = 0; j < modules->inputGateSize[i]; j++)
			{
				index = modules->inputGate[i][j];

				//update inputs
				modules->gates[index].inputsHigh++;
			}
		}
		g_printf(" input[%d]<%d>", i, modules->input[i]);
	}

	//TODO make this dynamic
	//update the status of all gates
	for(i = 0; i < modules->gateSize; i++)
	{
		//update status
		if(updateStatus(&modules->gates[i]))
		{
			for(j = 0; j < modules->gates[i].outputSize; j++)
			{
				modules->gates[ modules->gates[i].output[j] ].inputsHigh++;
			}
		}

		g_printf("\nGate[%d]([%d][%d])<%d>: ", i, modules->gates[i].inputSize,
												  modules->gates[i].inputsHigh,
												  modules->gates[i].state);
		for(j = 0; j < modules->gates[i].outputSize && j < 8; j++)
		{
			g_printf(" output[%d]", modules->gates[i].output[j]);
		}
	}

	//check output status
	for(i = 0; i < modules[0].outputSize; i++)
	{
		//the value is stored in the gate array
		g_printf("\nOutput[%d]<%d>", i, modules[0].output);
	}

	g_printf("\n");
	//output

    return;
}

gboolean updateStatus(Gate *gate)
{
	if(gate->type == AND)
	{
		if(gate->inputsHigh == gate->inputSize)
			gate->state = TRUE;
		else
			gate->state = FALSE;
	}

	else if(gate->type == OR)
	{
		if(gate->inputsHigh > 0)
			gate->state = TRUE;
		else
			gate->state = FALSE;
	}

	else if(gate->type == NOT)
	{
		if(gate->inputsHigh > 0)
			gate->state = FALSE;
		else
			gate->state = TRUE;
	}

	else if(gate->type == XOR)
	{
		if(gate->inputsHigh == 1)
			gate->state = TRUE;
		else
			gate->state = FALSE;
	}

	return(gate->state);
}
