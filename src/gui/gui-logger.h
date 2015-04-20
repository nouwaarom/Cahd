#ifndef __GUI_LOGGER_H
#define __GUI_LOGGER_H

#include <gtk/gtk.h>
#include <glib.h>

typedef struct _LoggerGui LoggerGui;

struct _LoggerGui {
    GtkTextView* textview;
    GtkTextBuffer* buffer;
    GtkStatusbar* statusbar;
};

LoggerGui*
loggergui_init(GtkBuilder* builder);

//keeps a local copy of the buffer so you only need to pass it once
void
gui_log_append(gchar* markup, GtkTextBuffer* buffer);

void
gui_log_set_statusbar(gchar* message, gchar* context, GtkStatusbar* statusbar);
#endif
