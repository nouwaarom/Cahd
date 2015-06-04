#include "manager.h"

void set_current_dir(gchar* path)
{
    environment->dirname = g_strdup(path);
    set_model_dir(path);
}

void create_makefile(void)
{
    GDir* dir = g_dir_open(environment->dirname, 0, NULL);
    gchar* filename;

    gchar* sources = "";

    // Add all vhdl files as sources
    while( filename = g_dir_read_name(dir) )
    {
        if(g_strstr_len(filename, -1, ".vhd"))
           sources = g_strdup_printf("%s %s", filename, sources); 
    }

    gchar* template;
    g_file_get_contents("/home/elbert/Dropbox/Programming/Cahd/data/misc/Makefile-Template",
                         &template, NULL, NULL);

    gchar* makefile = g_strdup_printf(template, sources, environment->top_entity);
    
    filename = g_strdup_printf("%s/Makefile", environment->dirname);
    g_file_set_contents(filename, makefile, -1, NULL);

    return;
}

gchar* scan_file_entities(gchar* file)
{
    gchar** entity_name;
    gchar* content, *location;
    if(g_file_get_contents(file, &content, NULL, NULL))
    {
        location = g_strstr_len(content, -1, "entity");
        entity_name = g_strsplit(location, " ", 3);

        g_free(content);
    }

    return entity_name[1];
}

void set_toplevel_module(char* module)
{
}

void add_to_makefile(char* file)
{
}
