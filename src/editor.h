#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <glib.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

#include "gui/gui-editor.h"

typedef struct _Editor Editor;

struct _Editor {
    gchar* filename;
    gchar* basename;
};

Editor*
editor_init();

void
editorgui_save_file(gchar* filename);

void
editorgui_open_file(gchar* filename);
#endif
