lib_LTLIBRARIES=\
	libuba.la

BUILT_SOURCES=\
	uba-creator-introspection.h \
	$(NULL)

libuba_la_SOURCES=\
	$(BUILT_SOURCES) \
	uba-container.c \
	uba-container.h

CLEANFILES=\
	$(BUILT_SOURCES) \
	$(NULL)

EXTRA_DIST=\
	UbaCreator.xml \
	$(NULL)

AM_CPPFLAGS=\
	$(UBA_CFLAGS)

uba-creator-introspection.h: UbaCreator.xml Makefile
	dbus-binding-tool --mode=glib-client $< > $@
