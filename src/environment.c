#include "environment.h"

Environment* environment;

Environment* environment_init()
{
    Environment* environment = g_new0(Environment,1);
    return environment;
}
