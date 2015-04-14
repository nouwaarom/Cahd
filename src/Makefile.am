## Process with automake to generate Makefile.in
bin_PROGRAMS = cahd 
cahd_SOURCES = main.c

## Add Gtk+ to the gui-program
cahd_CPPFLAGS = @GUI_CFLAGS@
cahd_LDADD = @GUI_LIBS@

CLEANFILES = *~

