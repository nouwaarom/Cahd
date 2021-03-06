/*
* Copyright 2013 Elbert van de Put

* TODO: Add verbose mode to output logs to terminal
*/
#ifndef __LOGGER_H__
#define __LOGGER_H__
//includes:
#include <glib.h>
#include <gtk/gtk.h>

#include "gui/gui-logger.h"

typedef enum {EDITOR, COMPILER, SIMULATOR, UPLOADER, PROGRAM} LogSource;
typedef enum {INFORMATION, WARNING, ERROR, DEBUG} LogLevel;

void
add_log(LogSource source, LogLevel level, gchar *message);

gchar*
create_markup(LogSource source, LogLevel level, gchar *message, gboolean title);
#endif
