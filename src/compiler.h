#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <gtk/gtk.h>
#include <glib.h>

#include "logger.h"
#include "environment.h"
#include "manager.h"

Environment* environment;

int
compile(gchar* path);
#endif
