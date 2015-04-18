/*
Copyright 2013, 2014 Elbert van de Put

TODO:
add support for module calls
*/
#include "simulator.h"

G_MODULE_EXPORT
void on_simulate_button_clicked(GtkWidget* widget, void* user)
{
    simulate("");
    return;
}

int simulate(gchar *filename)
{
    add_log(SIMULATOR, INFORMATION, "Starting simulation\n");
    g_printf("I am starting my simulation\n");
    return 1;
}
