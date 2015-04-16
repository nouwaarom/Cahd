#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <glib.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

#include "gui/gui-editor.h"

typedef struct _Editor Editor;

struct _Editor {
    gchar* filename;
    gchar* basename;

    //gui related stuff
    GtkWidget *source;
};

Editor*
editor_init();

#endif
