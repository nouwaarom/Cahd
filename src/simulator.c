/*
Copyright 2013, 2014 Elbert van de Put

TODO:
add support for module calls
*/
#include "simulator.h"

G_MODULE_EXPORT
void on_simulate_button_clicked(GtkWidget* widget, void* user)
{
    if( simulate(environment->dirname) )
        start_gtkwave(environment->dirname, "waveout");

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


int simulate(gchar* path)
{
    gchar* argv[] = {"make", "simulate", NULL};
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

int start_gtkwave(gchar* path, gchar* file)
{
    gchar* argv[] = {"gtkwave", "waveout", NULL};
    GPid pid;

    g_spawn_async(path, argv, NULL, G_SPAWN_SEARCH_PATH,
                  NULL, NULL, &pid, NULL); 

    return 1;
}
