/*
* Copyright 2013 Elbert van de Put

* TODO:
* Use getopt for command line parsing
*/
#include "gui/gui-main.h"
#include "logger.h"
#include "editor.h"
#include "simulator.h"
#include "compiler.h"
#include "environment.h"

Environment* environment;

int main(int argc, char **argv)
{
    environment = environment_init();

    gui_init(argc, argv, "../data/ui/cahd.glade");

    return 0;
}
