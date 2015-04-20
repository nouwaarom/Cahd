#ifndef __GUI_EDITOR_H__
#define __GUI_EDITOR_H__

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

typedef struct _EditorGui EditorGui;

struct _EditorGui {
    GtkWidget* textview;
    GtkTextBuffer* buffer;
};

EditorGui*
editorgui_init(GtkBuilder* builder);
#endif
