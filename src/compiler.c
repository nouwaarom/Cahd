#include "compiler.h"

G_MODULE_EXPORT
void on_compile_button_clicked(GtkWidget* widget, void* user)
{
    add_log(COMPILER, INFORMATION, "Compile button clicked");

    GDir* dir;
    gboolean has_make = FALSE;

    // check if we have an active working directory
    // and makefile
    if(environment->dirname)
    {
        dir = g_dir_open(environment->dirname, 0, NULL); 

        gchar* filename;

        while( filename = g_dir_read_name(dir) )
        {
            if(g_strcmp0(filename, "Makefile") == 0) {
                has_make = TRUE;
                break;
            }
        }
    }
 
    if(!has_make) {
        add_log(COMPILER, INFORMATION, "Creating makefile"); 
        create_makefile();
    }

    // Execute make 
    compile(environment->dirname);

    return;
}

static gboolean channel_out_callback(GIOChannel* channel, GIOCondition cond, void* user)
{
    gchar* string;
    gsize size;

    if(cond == G_IO_HUP){
        g_io_channel_unref(channel);
        return FALSE;
    }

    g_io_channel_read_line(channel, &string, &size, NULL, NULL);
    
    add_log(COMPILER, INFORMATION, string);
    g_free(string);
    return TRUE;
}

static gboolean channel_err_callback(GIOChannel* channel, GIOCondition cond, void* user)
{
    gchar* string;
    gsize size;

    if(cond == G_IO_HUP){
        g_io_channel_unref(channel);
        return FALSE;
    }

    g_io_channel_read_line(channel, &string, &size, NULL, NULL);
    
    add_log(COMPILER, ERROR, string);
    g_free(string);
    return TRUE;
}


int compile(gchar* path)
{
    gchar *argv[] = {"make", "compile", NULL};
    GPid pid;

    gint out, err;
    GIOChannel* out_ch;
    GIOChannel* err_ch;

    gboolean ret;

    //call make which does the compiling
    ret = g_spawn_async_with_pipes( path, argv, NULL, G_SPAWN_SEARCH_PATH,
                                    NULL, NULL, &pid, NULL, &out, &err, NULL );

    if(!ret) {
        g_error("Starting make failed");
        return -1;
    }

    out_ch = g_io_channel_unix_new(out);
    err_ch = g_io_channel_unix_new(err);

    g_io_add_watch( out_ch, G_IO_IN | G_IO_HUP, (GIOFunc)channel_out_callback, NULL);
    g_io_add_watch( err_ch, G_IO_IN | G_IO_HUP, (GIOFunc)channel_err_callback, NULL);

    return 1;
}
