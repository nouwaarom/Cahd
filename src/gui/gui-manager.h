#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

#include <gtk/gtk.h>
#include "manager.h"
#include "environment.h"
#include "logger.h"

typedef struct _ManagerGui ManagerGui;

struct _ManagerGui {
    GtkWidget* treeview;
    gchar* path;
};

Environment* environment;

void
row_activated_callback(GtkTreeView* tree_view, GtkTreePath* path, GtkTreeViewColumn* column, gpointer* user_data);

void
row_expanded_callback(GtkTreeView* tree_view, GtkTreeIter* iter, GtkTreePath* path, ManagerGui* user_data);

ManagerGui*
managergui_init(GtkBuilder* builder);

void
init_view_and_model(GtkWidget* widget);

void
set_model_dir(gchar* path);

void
recursive_dir_crawl(gchar* path, GtkTreeStore* treestore, GtkTreeIter* iter);

//geter and setter
GtkWidget*
get_set_treeview(GtkWidget* widget);
#endif
