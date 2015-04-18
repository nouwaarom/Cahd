#include "compiler.h"

G_MODULE_EXPORT
void on_compile_button_clicked(GtkWidget* widget, void* user)
{
    add_log(COMPILER, INFORMATION, "Compile button clicked\n");
    g_print("Compile button clicked.\n");
    return;
}
