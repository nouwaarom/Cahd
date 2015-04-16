#include "gui/gui-logger.h"

LoggerGui* loggergui_init(GtkBuilder* builder)
{
    LoggerGui* loggergui = g_new0(LoggerGui, 1);
    loggergui->textview = GTK_WIDGET(gtk_builder_get_object(builder, "log_textview"));

    return loggergui;
}

