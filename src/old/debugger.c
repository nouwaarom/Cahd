#include "debugger.h"

void displayModule(Module module)
{
    int i, j;
    g_printf("\n*******DEBUGGING********\n");

    g_printf("module %s(%d)\n", g_quark_to_string(module.ID), module.ID);

    //input
    for(i = 0; i < module.inputSize; i++)
    {
        g_printf("input[%d] state:%d gates:", i, module.input[i]);

        for(j = 0; j < module.inputGateSize[i]; j++)
        {
            g_printf("%d, ", module.inputGate[i][j]);
        }
        g_printf("\n");
    }

    //gates
    for(i = 0; i < module.gateSize; i++)
    {
        g_printf("gate[%d] output:",i);
        for(j = 0; j < module.gates[i].outputSize; j++)
        {
            g_printf("%d, ", module.gates[i].output[j]);
        }
        g_printf("\n");
    }

    //output
    for(i = 0; i < module.outputSize; i++)
    {
        g_printf("output[%d] state:%d\n", i ,module.output[i]);
    }

}
