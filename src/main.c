/*
* Copyright 2013 Elbert van de Put

* TODO:
* Use getopt for command line parsing
*/
//includes:
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

//#include "memory.h"
//#include "defines.h"
//#include "statusbar.h"
//#include "logs.h"

//functions:
int main( int argc, char **argv)
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GError *error = NULL;

    //menu bar with items
    GtkWidget *menubar;
        GtkWidget *fileMenu, *fileMenuItem;
            GtkWidget *newFile, *openFile, *saveFile, *closeFile;
        GtkWidget *projectMenu, *projectMenuItem;
        GtkWidget *buildMenu, *buildMenuItem;
        GtkWidget *debugMenu, *debugMenuItem;
        GtkWidget *settingsMenu, *settingsMenuItem;
        GtkWidget *toolsMenu, *toolsMenuItem;
            GtkWidget *uploadTool, *serialTool;
        GtkWidget *helpMenu, *helpMenuItem;

    //toolbar with items
    GtkWidget *toolbar;
        GtkToolItem *open, *save, *sep, *build, *run, *draw, *debug;

    //tabbed area
    GtkWidget *notebook;

    //home screen
    GtkWidget *homeArea;
    GtkWidget *homeLabel;

    //cairo draw area
    GtkWidget *drawArea;
    GtkWidget *drawLabel;

    //text area
    GtkWidget *textArea;
    GtkWidget *scrollTextArea;
    GtkTextBuffer *textBuffer;
    GtkWidget *textLabel;

    //communication & upload area
    GtkWidget *communicationArea;
    GtkWidget *communicationLabel;

    //log & message board
    GtkWidget *logbook;
    GtkRequisition logbooksize;
        GtkWidget *scrollBuildLog;
        GtkWidget *labelBuildLog;
        GtkWidget *buildLog;

        GtkWidget *scrollDebugLog;
        GtkWidget *labelDebugLog;
        GtkWidget *debugLog;

    //statusbar
    GtkWidget *statusbar;

	g_printf("\nThis program is free software: you can redistribute it and/or modify\n"
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


    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if( !gtk_builder_add_from_file(builder, "../data/ui/cahd.glade", &error))
    {
        g_warning("%s", error->message);
        g_free(error);
        return 1;
    }

    //window declaration
    window = GTK_WIDGET( gtk_builder_get_object(builder, "main-window"));

    gtk_builder_connect_signals(builder , NULL);

    g_object_unref( G_OBJECT(builder));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
