#include "editor.h"

Editor* editor_init()
{
    Editor* editor = g_new0(Editor,1);
    return editor;
}
