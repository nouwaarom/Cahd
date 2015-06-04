/*
Copyright 2013 Elbert van de Put
*/
#include "logger.h"

void add_log(LogSource source, LogLevel level, gchar* message)
{
    gchar* StatusString[] = {"Editing", "Compiling", "Simulating", "Uploading", "Fuu"};
    //only add title if the source of this log is different from the last one
    static LogSource localSource = PROGRAM;
    gboolean title;

    if(localSource == source)
        title = FALSE; 
    else{
        title = TRUE;
        gui_log_set_statusbar(StatusString[source], "EDITOR", NULL);
    }

    localSource = source;

    gchar* markup = create_markup(source, level, message, title);

    gui_log_append(markup, NULL);
    return;
}

gchar* create_markup(LogSource source, LogLevel level, gchar* message, gboolean title)
{
    gchar* LogSourceString[] = {"Editor", "Compiler", "Simulator", "Uploader", "Program"};

    gchar* Title = "";
    if(title) {
        Title = g_strdup_printf("<big>%s:</big>", LogSourceString[source]);
        return g_strdup_printf("\n%s\n%s", Title, message);
    }
    return g_strdup_printf("\n%s", message);
}
