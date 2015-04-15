## Process with automake to generate Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS = -g

bin_PROGRAMS = cahd 
cahd_SOURCES = gui/gui-main.c gui/gui-main.h \
			   main.c

## Add Gtk+ to the gui-program
cahd_CPPFLAGS = @GUI_CFLAGS@
cahd_LDADD = @GUI_LIBS@

CLEANFILES = *~

