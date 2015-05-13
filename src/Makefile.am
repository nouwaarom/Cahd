AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = cahd
AM_CFLAGS = $(GUI_CFLAGS) \
	        -Wall -O2

cahd_LDADD = $(GUI_LIBS)
cahd_LDFLAGS = -export-dynamic

cahd_SOURCES =  logger.c logger.h \
				editor.c editor.h \
				compiler.c compiler.h \
				simulator.c simulator.h \
				manager.c manager.h \
				environment.c environment.h \
				gui/gui-main.c gui/gui-main.h \
				gui/gui-editor.c gui/gui-editor.h \
				gui/gui-logger.c gui/gui-logger.h \
				gui/gui-manager.c gui/gui-manager.h \
				main.c
