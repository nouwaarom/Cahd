#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

#include <gtk/gtk.h>

typedef struct _ManagerGui ManagerGui;

struct _ManagerGui{
    GtkWidget* treeview;
};

ManagerGui*
managergui_init(GtkBuilder* builder);

void
init_view_and_model(GtkWidget* widget);
#endif
