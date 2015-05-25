#include "gui/gui-manager.h"

enum {
    NAME_COL = 0,
    TYPE_COL,
    NUM_COLS
};

ManagerGui* _managergui;


void row_expanded_callback(GtkTreeView* tree_view, GtkTreeIter* iter, GtkTreePath* tree_path, ManagerGui* managergui)
{
    GtkTreeModel* model = gtk_tree_view_get_model(tree_view);

    gchar* value;
    gchar* path = "";

    //retrieve the path
    GtkTreeIter iter_cpy = *iter;

    int i;
    int depth = gtk_tree_path_get_depth(tree_path);
    for(i = 0; i < depth; i++)
    {
        gtk_tree_model_get_iter(model, iter, tree_path);
        gtk_tree_model_get(model, iter, NAME_COL, &value, -1);

        gtk_tree_path_up(tree_path);

        g_printf("Value: %s\n", value);
        path = g_strdup_printf("%s/%s/", value, path);
    }

    path = g_strdup_printf("%s/%s/", managergui->path, path);

    iter = &iter_cpy;
    recursive_dir_crawl(path, GTK_TREE_STORE(model), iter);

    return;
}

ManagerGui* managergui_init(GtkBuilder* builder)
{
    ManagerGui* managergui = g_new0(ManagerGui, 1);
    _managergui = managergui;

    managergui->treeview = GTK_WIDGET(gtk_builder_get_object(builder, "treeview1")); 

    init_view_and_model(managergui->treeview);

    g_signal_connect(G_OBJECT(managergui->treeview), "row-expanded",
                        G_CALLBACK(row_expanded_callback), _managergui);

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
    _managergui->path = path;

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
        //do not include hidden files
        if(name[0] != '.')
        {
            gchar* file = g_strdup_printf("%s%s", path, name);
            gboolean isDir = g_file_test(file, G_FILE_TEST_IS_DIR);

            gtk_tree_store_append(treestore, &child, iter);
            gtk_tree_store_set(treestore, &child,
                                NAME_COL, name, TYPE_COL, isDir?"dir":"file", -1);

            if(isDir) {
                GtkTreeIter newChild;
                gtk_tree_store_append(treestore, &newChild, &child); 
            }
        }
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
