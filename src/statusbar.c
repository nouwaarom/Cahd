/*
Copyright 2013 Elbert van de Put
*/
#include "statusbar.h"

G_DEFINE_TYPE (StatusBar, status_bar, G_TYPE_OBJECT);

#define STATUS_BAR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), STATUS_TYPE_BAR, StatusBarPrivate))

struct _StatusBarPrivate
{
    GtkWidget *widget;
    gchar *status;
};


static void status_bar_class_init (StatusBarClass *klass)
{
    g_type_class_add_private (klass, sizeof (StatusBarPrivate));
}


static void status_bar_init (StatusBar *self)
{
    StatusBarPrivate *priv;
    self->priv = priv = STATUS_BAR_GET_PRIVATE(self);

    priv->widget = NULL;
    priv->status = NULL;
}

void status_bar_set_widget(StatusBar *self, GtkWidget *statusWidget)
{
    g_return_if_fail( STATUS_IS_BAR(self));

    self->priv->widget = statusWidget;

    return;
}

//update the status
void status_bar_set_status(StatusBar *self, char *status)
{
    g_return_if_fail( STATUS_IS_BAR(self));

    //update the status
    gtk_statusbar_push(GTK_STATUSBAR(self->priv->widget), gtk_statusbar_get_context_id(GTK_STATUSBAR(self->priv->widget), "system"), status);

    return;
}
