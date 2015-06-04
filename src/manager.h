#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "gui/gui-manager.h"
#include "environment.h"
#include <glib.h>

void
set_current_dir(char* dir);

//creates a makefile in the current working directory
void
create_makefile(void);

gchar*
scan_file_entities(gchar* file);

void
set_toplevel_module(char* module);

void
add_to_makefile(char* file);

#endif
