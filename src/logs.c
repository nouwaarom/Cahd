/*
Copyright 2013 Elbert van de Put
*/
#include "logs.h"

G_DEFINE_TYPE (Logs, logs, G_TYPE_OBJECT);

#define LOGS_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), LOGS_TYPE, LogsPrivate))

struct _LogsPrivate
{
    GtkWidget *buildLogWidget;
    gchar buildLog[128];
};


static void logs_class_init (LogsClass *klass)
{
    g_type_class_add_private (klass, sizeof (LogsPrivate));
}


static void logs_init (Logs *self)
{
    LogsPrivate *priv;
    self->priv = priv = LOGS_GET_PRIVATE(self);

    priv->buildLogWidget = NULL;
    priv->buildLog[0] = '\0';
}

void logs_build_set_widget(Logs *self, GtkWidget *buildWidget)
{
    g_return_if_fail( IS_LOGS(self));

    self->priv->buildLogWidget = buildWidget;

    return;
}

//update the status
void logs_build_update_status(Logs *self, gchar *status)
{
    g_return_if_fail( IS_LOGS(self));

    g_strlcat(self->priv->buildLog, status, sizeof(self->priv->buildLog));

    //update the status
    gtk_label_set_text(self->priv->buildLogWidget, self->priv->buildLog);

    return;
}
