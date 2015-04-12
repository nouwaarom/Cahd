/*
Copyright 2013 Elbert van de Put
*/
#ifndef LOGS_H
#define LOGS_H
//includes:
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

//defines:
#define LOGS_TYPE                  (logs_get_type ())
#define LOGS(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), LOGS_TYPE, Logs))
#define IS_LOGS(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LOGS_TYPE))
#define LOGS_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass),  LOGS_TYPE, LogsClass))
#define IS_LOGS_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass),  LOGS_TYPE))
#define LOGS_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj),  LOGS_TYPE, LogsClass))

typedef struct _Logs        Logs;
typedef struct _LogsClass   LogsClass;
typedef struct _LogsPrivate LogsPrivate;

/* object */
struct _Logs
{
    /* Parent instance structure */
    GObject parent_instance;

    /* public */

    /* private */
    LogsPrivate *priv;
};

/* class */
struct _LogsClass
{
    /* Parent class structure */
    GObjectClass parent_class;

    /* class members */

    /* virtual public methods */
};

GType logs_get_type (void);

/* non-virtual public methods */
void logs_build_set_widget(Logs *self, GtkWidget *buildWidget);

void logs_build_update_status(Logs *self, gchar *status);

/* instances */
Logs *logHandle;

#endif
