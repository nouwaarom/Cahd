#include "editor.h"

G_MODULE_EXPORT
void on_open_button_clicked(GtkWidget* widget, void* user)
{
    gchar* filename = ask_filename(GTK_FILE_CHOOSER_ACTION_OPEN);
    environment->filename = filename;
    environment->dirname = g_path_get_dirname(filename); 
    editorgui_open_file(filename);
    return;
}

G_MODULE_EXPORT
void on_save_button_clicked(GtkWidget* widget, void* user)
{
    if(environment->filename == NULL) {
        gchar* filename = ask_filename(GTK_FILE_CHOOSER_ACTION_SAVE);
        environment->filename = filename;
        environment->dirname = g_path_get_dirname(filename);
    }
    editorgui_save_file(environment->filename);
    return;
}

static void source_load_callback(GObject* source, GAsyncResult* res, gpointer data)
{
    add_log(EDITOR, INFORMATION, "Done");

    gtk_source_file_loader_load_finish(GTK_SOURCE_FILE_LOADER(source), res, NULL);
    return;
}

static void source_save_callback(GObject* source, GAsyncResult* res, gpointer data)
{
    add_log(EDITOR, INFORMATION, "Done");

    gtk_source_file_saver_save_finish(GTK_SOURCE_FILE_SAVER(source), res, NULL);
    return;
}

void editorgui_save_file(gchar* filename)
{
    add_log(EDITOR, INFORMATION, "Saving file ...");

    GtkSourceBuffer* buffer = get_set_sourcebuffer(NULL);
    GFile* file = g_file_new_for_path(filename);
    GtkSourceFile* sourceFile = gtk_source_file_new();
    gtk_source_file_set_location(sourceFile, file);

    GtkSourceFileSaver* saver = gtk_source_file_saver_new(buffer, sourceFile);

    gtk_source_file_saver_save_async(saver, G_PRIORITY_DEFAULT, NULL, NULL, NULL, NULL, source_save_callback, NULL);
    return;
}

void editorgui_open_file(gchar* filename)
{
    add_log(EDITOR, INFORMATION, g_strdup_printf("Opening file: %s", filename));

    GtkSourceBuffer* buffer = get_set_sourcebuffer(NULL);
    GFile* file = g_file_new_for_path(filename);
    GtkSourceFile* sourceFile = gtk_source_file_new();
    gtk_source_file_set_location(sourceFile, file);

    GtkSourceFileLoader* loader = gtk_source_file_loader_new(buffer, sourceFile);

    gtk_source_file_loader_load_async(loader, G_PRIORITY_DEFAULT,  NULL, NULL, NULL, NULL, source_load_callback, NULL);
    return;
}
