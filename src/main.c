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

int main(int argc, char **argv)
{
	printf("\nThis program is free software: you can redistribute it and/or modify\n"
    		 "it under the terms of the GNU General Public License as published by\n"
    		 "the Free Software Foundation, either version 3 of the License, or\n"
    		 "(at your option) any later version.\n"
			 "\n"
             "This program is distributed in the hope that it will be useful,\n"
    		 "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    		 "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    		 "GNU General Public License for more details.\n"
			 "\n"
    		 "You should have received a copy of the GNU General Public License\n"
    		 "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n");

    //setup gui for our application
    gui_init(argc, argv, "../data/ui/cahd.glade");

    return 0;
}
