#include "gui/gui-editor.h"

EditorGui* editorgui_init(GtkBuilder* builder)
{
    EditorGui* editorgui = g_new0(EditorGui,1);
 
    editorgui->textview = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "sourceview")); 
    
    editorgui->buffer = gtk_text_view_get_buffer(editorgui->textview);
    gtk_source_buffer_set_highlight_matching_brackets(editorgui->buffer, TRUE);

    get_set_sourcebuffer(editorgui->buffer);

    return editorgui;
}

gchar* ask_filename(GtkFileChooserAction action)
{
    GtkWidget* dialog;
    gchar* window_name;
    gchar* accept_name;

    gchar* filename = NULL;

    switch(action){
        case GTK_FILE_CHOOSER_ACTION_OPEN:
            window_name = "Open File";
            accept_name = "Open";
            break;
        case GTK_FILE_CHOOSER_ACTION_SAVE:
            window_name = "Save File";
            accept_name = "Save";
            break;
        default:
            return NULL;
            break;
    }

    dialog = gtk_file_chooser_dialog_new(window_name, NULL, action,
                    "Cancel", GTK_RESPONSE_CANCEL,
                    accept_name, GTK_RESPONSE_ACCEPT,
                    NULL);

    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }
    gtk_widget_destroy(dialog);
    return filename;
}

GtkSourceBuffer* get_set_sourcebuffer(GtkSourceBuffer* buffer)
{
    static GtkSourceBuffer* localBuffer;

    if(buffer != NULL)
        localBuffer = buffer;

    return GTK_SOURCE_BUFFER(localBuffer);
}
