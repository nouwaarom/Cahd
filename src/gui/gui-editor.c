#include "gui/gui-editor.h"

EditorGui* editorgui_init(GtkBuilder* builder)
{
    EditorGui* editorgui = g_new0(EditorGui,1);

    editorgui->textview = GTK_WIDGET(gtk_builder_get_object(builder, "source_gtksourceview"));

    return editorgui;
}
