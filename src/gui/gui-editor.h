#ifndef __GUI_EDITOR_H__
#define __GUI_EDITOR_H__

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

typedef struct _EditorGui EditorGui;

struct _EditorGui {
    GtkTextView* textview;
    GtkSourceBuffer* buffer;
};

EditorGui*
editorgui_init(GtkBuilder* builder);

gchar*
ask_filename();

//super asesome function
GtkSourceBuffer*
get_set_sourcebuffer(GtkSourceBuffer* buffer);
#endif
