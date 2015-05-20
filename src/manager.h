#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "gui/gui-manager.h"
#include "environment.h"

void
set_current_dir(char* dir);

void
create_makefile(void);

void
set_toplevel_module(char* module);

void
add_to_makefile(char* file);

#endif
