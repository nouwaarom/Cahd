/*
Copyright 2013 Elbert van de Put

TODO:
Fix log bar to work with compiler and debugger
*/
//includes:
#include <gtk/gtk.h>
#include <cairo.h>

#include "memory.h"
#include "defines.h"
#include "statusbar.h"
#include "logs.h"

//defines:

//data types:
typedef struct{
GtkWidget *label;
GtkWidget *window;
GtkWidget *parent;
} editWindow;

//global variables:
Module _modules[8];
int _moduleSize;

char *_filename;
char *_content;
gsize _length;

//callbacks:
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	drawGrid(cr, _modules[0], gtk_widget_get_allocated_width (widget), gtk_widget_get_allocated_height (widget));

	return(FALSE);
}

gboolean draw_input(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	gdouble x, y;
	//first get the usefull data
	gdk_event_get_coords(event, &x, &y);

	if(inputGrid(_modules, widget, gtk_widget_get_allocated_width (widget), gtk_widget_get_allocated_height (widget), x, y))
		status_bar_set_status(barHandle ,"Input changed");

	return(TRUE);
}

void open_file(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *dialog;

	//open file dialog
    dialog = gtk_file_chooser_dialog_new("Open Hardware Design", NULL,
    									  GTK_FILE_CHOOSER_ACTION_OPEN,
										  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
										  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        _filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        //load file into the text buf that is coupled to the view

		if(g_file_get_contents(_filename, &_content, &_length, NULL))
        {
			g_printf("File succesfully loaded.\n");
			gtk_text_buffer_set_text(user_data, _content, _length);
        }
        else
        {
        	g_printf("Error: couldnt load file.\n");
        }
    }
    gtk_widget_destroy(dialog);
    return;
}

void save_file(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *dialog;

	//open file dialog
    dialog = gtk_file_chooser_dialog_new("Save Hardware Design", NULL,
    									  GTK_FILE_CHOOSER_ACTION_SAVE,
										  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
										  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
    	GtkTextIter start;
    	GtkTextIter end;

        _filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        //load file into the text buf that is coupled to the view

        //get text
        gtk_text_buffer_get_start_iter(user_data, &start);
        gtk_text_buffer_get_end_iter(user_data, &end);

        _content = gtk_text_buffer_get_text(user_data, &start, &end, TRUE);

        g_printf("%s\n", _content);

        //save it
		if(g_file_set_contents(_filename, _content, -1, NULL))
        {
			g_printf("File succesfully saved.\n");
        }
        else
        {
        	g_printf("Error: couldnt save file\n");
        }
    }
    gtk_widget_destroy(dialog);
    return;
}

void close_file(GtkWidget *widget, gpointer user_data)
{
    _filename = '\0';
    _content =  '\0';
    _length =   '\0';

    return;
}

void make_schematic(GtkWidget *widget, gpointer area)
{
	status_bar_set_status(barHandle ,"Make Schematic");

    fillGrid(_modules, GTK_WIDGET(area));

    return;
}

void build_project(GtkWidget *widget, gpointer user_data)
{
    status_bar_set_status(barHandle ,"Compiling ...");

    compileEntry(_modules, _filename);

    status_bar_set_status(barHandle ,"Compiling finished.");
    return;
}

void run_project(GtkWidget *widget, gpointer user_data)
{
    status_bar_set_status(barHandle ,"Simulate Design");

    //simulate the design
    simulate(_modules);

    //update the grid so we can see what happened
    updateGrid(_modules, user_data);
    return;
}

void debug_build(GtkWidget *widget, gpointer user_data)
{
    status_bar_set_status(barHandle ,"Displaying Module Data");

    displayModule(_modules[0]);

    return;
}

void open_communication_window(GtkWidget *widget, gpointer user_data)
{
    static gboolean windowExists = FALSE;
    editWindow *commWindow = user_data;

    status_bar_set_status(barHandle, "Communication & Upload window opened");

    if(!windowExists)
    {
        gtk_notebook_append_page(GTK_NOTEBOOK(commWindow->parent), commWindow->window, commWindow->label);
        gtk_notebook_set_current_page(GTK_NOTEBOOK(commWindow->parent), 3);

        //gtk_notebook_set_show_tabs(GTK_NOTEBOOK(commWindow->parent), FALSE);
        //this line is a must
        gtk_widget_show_all(commWindow->parent);
        windowExists = TRUE;
    }

    return;
}

//functions:
int main( int argc, char *argv[])
{
    //window and box
    GtkWidget *window;
        GtkWidget *vbox;

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

    //window declaration
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 1000);
    gtk_window_set_title(GTK_WINDOW(window), "Cahd Alpha 0.3");

    //make the verticalbox the child of window and add the allignment to the vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(vbox), FALSE);
    //gtk_box_set_spacing(GTK_BOX(vbox), 1);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    //menubar declaration
    menubar = gtk_menu_bar_new();
        fileMenu = gtk_menu_new();
        fileMenuItem = gtk_menu_item_new_with_label("File");
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMenuItem), fileMenu);
            gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMenuItem);
                newFile = gtk_menu_item_new_with_label("New");
                gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), newFile);
                openFile = gtk_menu_item_new_with_label("Open");
                gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openFile);
                saveFile = gtk_menu_item_new_with_label("Save");
                gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveFile);
                closeFile = gtk_menu_item_new_with_label("Close");
                gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), closeFile);

        projectMenu = gtk_menu_new();
        projectMenuItem = gtk_menu_item_new_with_label("Project");
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(projectMenuItem), projectMenu);
            gtk_menu_shell_append(GTK_MENU_SHELL(menubar), projectMenuItem);

        buildMenu = gtk_menu_new();
        buildMenuItem = gtk_menu_item_new_with_label("Build");
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(buildMenuItem), buildMenu);
            gtk_menu_shell_append(GTK_MENU_SHELL(menubar), buildMenuItem);

        debugMenu = gtk_menu_new();
        debugMenuItem = gtk_menu_item_new_with_label("Debug");
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(debugMenuItem), debugMenu);
            gtk_menu_shell_append(GTK_MENU_SHELL(menubar), debugMenuItem);

        settingsMenu = gtk_menu_new();
        settingsMenuItem = gtk_menu_item_new_with_label("Settings");
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(settingsMenuItem), settingsMenu);
            gtk_menu_shell_append(GTK_MENU_SHELL(menubar), settingsMenuItem);

        toolsMenu = gtk_menu_new();
        toolsMenuItem = gtk_menu_item_new_with_label("Tools");
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(toolsMenuItem), toolsMenu);
            gtk_menu_shell_append(GTK_MENU_SHELL(menubar), toolsMenuItem);
                uploadTool = gtk_menu_item_new_with_label("Upload");
                gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), uploadTool);
                serialTool = gtk_menu_item_new_with_label("Serial");
                gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), serialTool);

        helpMenu = gtk_menu_new();
        helpMenuItem = gtk_menu_item_new_with_label("Help");
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(helpMenuItem), helpMenu);
            gtk_menu_shell_append(GTK_MENU_SHELL(menubar), helpMenuItem);

    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    //toolbar declaration
    toolbar = gtk_toolbar_new();

    sep   = gtk_separator_tool_item_new();
    open  = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
    save  = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    build = gtk_tool_button_new_from_stock(GTK_STOCK_REFRESH);
    run   = gtk_tool_button_new_from_stock(GTK_STOCK_EXECUTE);
    draw  = gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
    debug = gtk_tool_button_new_from_stock(GTK_STOCK_HELP);

    gtk_tool_item_set_tooltip_text(build, "Compile the current design");
    gtk_tool_item_set_tooltip_text(debug, "Print the output of the compiler");

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open,  -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save,  -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep,   -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), build, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), run,   -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), draw,  -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), debug, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep,   -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

	//declare notebook
	notebook = gtk_notebook_new();

    //home area
    homeLabel = gtk_label_new("Home");
    homeArea = gtk_label_new("Welcome to the alpha version of Cahd.\n"
                             "For more information please refer to the manual.");
    gtk_misc_set_alignment(GTK_MISC(homeArea), 0,  0);
    gtk_misc_set_padding(GTK_MISC(homeArea), 40, 10);

    //text area
    textLabel = gtk_label_new("Design");
    scrollTextArea = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(scrollTextArea, GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    textBuffer = gtk_text_buffer_new(NULL);
    textArea = gtk_text_view_new_with_buffer(textBuffer);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(textArea), 40);
    gtk_container_add(GTK_CONTAINER(scrollTextArea), textArea);

    //draw area
    drawLabel = gtk_label_new("Scematic");
    drawArea = gtk_drawing_area_new();
    gtk_widget_add_events(GTK_WIDGET(drawArea), GDK_BUTTON_PRESS_MASK);

    //communication area
    communicationLabel = gtk_label_new("Communication");
    communicationArea = gtk_label_new("This is the communication tab.\nCool huh?");

    editWindow communicationWindow;
    communicationWindow.label = communicationLabel;
    communicationWindow.window = communicationArea;
    communicationWindow.parent = notebook;

    //add items to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), homeArea, homeLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrollTextArea, textLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), drawArea, drawLabel);

    //add notebook to window
    gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

    //log & others status
    logbook = gtk_notebook_new();

    buildLog = gtk_label_new("Welcome to the build log.\n");
    debugLog = gtk_label_new("Welcome to the debug log.\n");

    labelBuildLog = gtk_label_new("Build log");
    labelDebugLog = gtk_label_new("Debug Log");

    scrollBuildLog = gtk_scrolled_window_new(NULL, NULL);
    scrollDebugLog = gtk_scrolled_window_new(NULL, NULL);

    gtk_scrolled_window_set_policy(scrollBuildLog, GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    gtk_scrolled_window_set_policy(scrollDebugLog, GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

     //set the text to allign at the top left corner
    gtk_misc_set_alignment(GTK_MISC(buildLog), 0,  0);
    gtk_misc_set_alignment(GTK_MISC(debugLog), 0,  0);

    gtk_misc_set_padding(GTK_MISC(buildLog), 40, 10);
    gtk_misc_set_padding(GTK_MISC(debugLog), 40, 10);

    gtk_widget_set_size_request(GTK_WIDGET(scrollBuildLog), 0, 150);
    gtk_widget_set_size_request(GTK_WIDGET(scrollDebugLog), 0, 150);

    gtk_container_add(GTK_CONTAINER(scrollBuildLog), buildLog);
    gtk_container_add(GTK_CONTAINER(scrollDebugLog), debugLog);

    gtk_notebook_append_page(GTK_NOTEBOOK(logbook), GTK_WIDGET(scrollBuildLog), labelBuildLog);
    gtk_notebook_append_page(GTK_NOTEBOOK(logbook), GTK_WIDGET(scrollDebugLog), labelDebugLog);

    gtk_box_pack_start(GTK_BOX(vbox), logbook, FALSE, FALSE, 0);

    //initialize the log manager object
    logHandle = g_object_new(LOGS_TYPE, NULL);
    logs_build_set_widget(logHandle, buildLog);
    logs_build_update_status(logHandle, "logHandler initialized\n");

    //the statusbar has alwas to be at the bottom
    statusbar = gtk_statusbar_new();
    gtk_widget_set_valign(statusbar, GTK_ALIGN_END);

    //innitialize the statusbar object
    barHandle = g_object_new(STATUS_TYPE_BAR, NULL);
    status_bar_set_widget(barHandle, statusbar);

    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 0);

    //draw area
	g_signal_connect(G_OBJECT(drawArea), "draw",               G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(G_OBJECT(drawArea), "button-press-event", G_CALLBACK(draw_input),    NULL);

    //connect to exit button
    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    //editor buttons
    g_signal_connect(G_OBJECT(newFile),  "activate", G_CALLBACK(open_file), textBuffer);

    g_signal_connect(G_OBJECT(open),     "clicked",  G_CALLBACK(open_file), textBuffer);
    g_signal_connect(G_OBJECT(openFile), "activate", G_CALLBACK(open_file), textBuffer);

    g_signal_connect(G_OBJECT(save),     "clicked",  G_CALLBACK(save_file), textBuffer);
    g_signal_connect(G_OBJECT(saveFile), "activate", G_CALLBACK(save_file), textBuffer);

    g_signal_connect(G_OBJECT(closeFile),"activate", G_CALLBACK(close_file), NULL);

    //program buttons
    g_signal_connect(G_OBJECT(build), "clicked", G_CALLBACK(build_project), NULL);
    g_signal_connect(G_OBJECT(run),   "clicked", G_CALLBACK(run_project),   drawArea);
    g_signal_connect(G_OBJECT(draw),  "clicked", G_CALLBACK(make_schematic),drawArea);
    g_signal_connect(G_OBJECT(debug), "clicked", G_CALLBACK(debug_build),   NULL);

    g_signal_connect(G_OBJECT(uploadTool), "activate", G_CALLBACK(open_communication_window), &communicationWindow);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
