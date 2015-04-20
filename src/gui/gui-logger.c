#include "gui/gui-logger.h"

LoggerGui* loggergui_init(GtkBuilder* builder)
{
    LoggerGui* loggergui = g_new0(LoggerGui, 1);

    loggergui->statusbar = GTK_STATUSBAR(gtk_builder_get_object(builder, "statusbar"));
    loggergui->textview = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "log_textview"));

    loggergui->buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(loggergui->textview, loggergui->buffer);

    gui_log_append("Gui Logger Initialized", loggergui->buffer);
    gui_log_set_statusbar("Statusbar Initialized", "EDITOR", loggergui->statusbar);

    return loggergui;
}

void gui_log_append(gchar* markup, GtkTextBuffer* buffer)
{
    static GtkTextBuffer* localBuffer = NULL;
    GtkTextIter end;

    if(buffer != NULL)
        localBuffer = buffer;

    if(localBuffer != NULL){
        gtk_text_buffer_get_end_iter(localBuffer, &end);
        //insert_markup only works with version 3.16 or higher
        gtk_text_buffer_insert(localBuffer, &end, markup, -1);    
    }
    else{
        g_print("[ERROR](GUILogger):Could not write log. No textbuffer.");
    }
}

void gui_log_set_statusbar(gchar* message, gchar* context, GtkStatusbar* statusbar)
{
    static GtkStatusbar* localStatusbar = NULL;

    if(statusbar != NULL){
        localStatusbar = statusbar;
    }

    guint contextId = gtk_statusbar_get_context_id(localStatusbar, context);
    gtk_statusbar_push(localStatusbar, contextId, message);
}
