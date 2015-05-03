#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <glib.h>

typedef struct _Environment Environment;

struct _Environment {
    gchar* filename;
    gchar* dirname;
};

extern Environment* environment;

Environment*
environment_init();
#endif
