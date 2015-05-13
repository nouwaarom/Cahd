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

    return managergui;
}

void init_view_and_model(GtkWidget* widget)
{
    GtkTreeViewColumn* name_col, *type_col;
    GtkCellRenderer* renderer;
    GtkTreeModel* model;

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
    
    //init model function call
}
