/*
Copyright 2013 Elbert van de Put
*/
#ifndef STATUSBAR_H
#define STATUSBAR_H
//includes:
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

//defines:
#define STATUS_TYPE_BAR                  (status_bar_get_type ())
#define STATUS_BAR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), STATUS_TYPE_BAR, StatusBar))
#define STATUS_IS_BAR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), STATUS_TYPE_BAR))
#define STATUS_BAR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), STATUS_TYPE_BAR, StatusBarClass))
#define STATUS_IS_BAR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), STATUS_TYPE_BAR))
#define STATUS_BAR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), STATUS_TYPE_BAR, StatusBarClass))

typedef struct _StatusBar        StatusBar;
typedef struct _StatusBarClass   StatusBarClass;
typedef struct _StatusBarPrivate StatusBarPrivate;

/* object */
struct _StatusBar
{
    /* Parent instance structure */
    GObject parent_instance;

    /* public */

    /* private */
    StatusBarPrivate *priv;
};

/* class */
struct _StatusBarClass
{
    /* Parent class structure */
    GObjectClass parent_class;

    /* class members */

    /* virtual public methods */
};

GType status_bar_get_type (void);

/* non-virtual public methods */
void status_bar_set_widget(StatusBar *self, GtkWidget *statusWidget);

void status_bar_set_status(StatusBar *self, char *status);

/* instances */
StatusBar *barHandle;

#endif
