## Process with automake to generate Makefile.in

bin_PROGRAMS = gui-program backend-program
gui_program_SOURCES = main.c
backend_program_SOURCES = uploader.c

## Add Gtk+ to the gui-program
gui_program_CPPFLAGS = @GTK_CFLAGS@
gui_program_LDADD = @GTK_LIBS@

CLEANFILES = *~

