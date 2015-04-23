#ifndef __GUI_MAIN_H__
#define __GUI_MAIN_H__

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

#include "gui/gui-editor.h"
#include "gui/gui-logger.h"

typedef struct _Gui Gui;

struct _Gui {
    EditorGui* editorgui;
    LoggerGui* loggergui;

    GtkWindow* mainwindow;

    GtkWidget* statusbar;
};

void
gui_init(int argc, char** argv, char* builderFile);
#endif
