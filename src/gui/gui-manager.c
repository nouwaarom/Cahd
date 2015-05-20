#include "gui/gui-manager.h"

enum {
    NAME_COL = 0,
    TYPE_COL,
    NUM_COLS
};

ManagerGui* managergui_init(GtkBuilder* builder)
{
    ManagerGui* managergui = g_new0(ManagerGui, 1);
    managergui->treeview = GTK_WIDGET(gtk_builder_get_object(builder, "treeview1")); 

    init_view_and_model(managergui->treeview);
    get_set_treeview(managergui->treeview);
    set_model_dir("/home/elbert/Documents/");

    return managergui;
}

void init_view_and_model(GtkWidget* widget)
{
    GtkTreeViewColumn* name_col, *type_col;
    GtkCellRenderer* renderer;

    name_col = gtk_tree_view_column_new();
    type_col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(name_col, "Name");
    gtk_tree_view_column_set_title(type_col, "Type");
    gtk_tree_view_append_column(GTK_TREE_VIEW(widget), name_col);
    gtk_tree_view_append_column(GTK_TREE_VIEW(widget), type_col);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(name_col, renderer, TRUE);
    gtk_tree_view_column_pack_start(type_col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(name_col, renderer,
        "text", NAME_COL);
    gtk_tree_view_column_add_attribute(type_col, renderer,
        "text", TYPE_COL);
    
    return;
}

void set_model_dir(gchar* path)
{
    GtkTreeStore* treestore;
    
    treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);

    recursive_dir_crawl(path, treestore, NULL);

    //set model
    GtkWidget* view = get_set_treeview(NULL);
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(treestore));
}

void recursive_dir_crawl(gchar* path, GtkTreeStore* treestore, GtkTreeIter* iter)
{
    GDir* dir = g_dir_open(path, 0, NULL);
    
    GtkTreeIter child;
    gchar* name;

    while( name = g_dir_read_name(dir) )
    {
        gchar* file = g_strdup_printf("%s%s", path, name);
        gboolean isDir = g_file_test(file, G_FILE_TEST_IS_DIR);

        gtk_tree_store_append(treestore, &child, iter);
        gtk_tree_store_set(treestore, &child,
                            NAME_COL, name, TYPE_COL, isDir?"dir":"file", -1);

        if(isDir)
            recursive_dir_crawl(file, treestore, &child);
    }
}


GtkWidget* get_set_treeview(GtkWidget* widget)
{
    static GtkWidget* localWidget = NULL;
    if(widget != NULL) {
        localWidget = widget;
    }

    return localWidget;
}
