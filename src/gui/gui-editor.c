#include "gui/gui-editor.h"

G_MODULE_EXPORT
void on_open_button_clicked(GtkWidget* widget, void* user)
{
}

G_MODULE_EXPORT
void on_save_button_clicked(GtkWidget* widget, void* user)
{
}

EditorGui* editorgui_init(GtkBuilder* builder)
{
    EditorGui* editorgui = g_new0(EditorGui,1);

    editorgui->textview = GTK_WIDGET(gtk_builder_get_object(builder, "source_gtksourceview"));

    return editorgui;
}
