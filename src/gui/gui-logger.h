#ifndef __GUI_LOGGER_H
#define __GUI_LOGGER_H

#include <gtk/gtk.h>
#include <glib.h>

typedef struct _LoggerGui LoggerGui;

struct _LoggerGui {
    GtkWidget* textview;
};

LoggerGui*
loggergui_init(GtkBuilder* builder);
#endif
