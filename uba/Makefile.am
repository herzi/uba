lib_LTLIBRARIES=\
	libuba-client.la

AM_CPPFLAGS=-DG_LOG_DOMAIN=\""uba-client"\"

BUILT_SOURCES=\
	uba-creator-introspection.h \
	uba-service-introspection.h \
	$(NULL)

libuba_client_la_SOURCES=\
	$(BUILT_SOURCES) \
	uba-container.c \
	uba-container.h

CLEANFILES=\
	$(BUILT_SOURCES) \
	$(NULL)

EXTRA_DIST=\
	UbaCreator.xml \
	UbaService.xml \
	$(NULL)

AM_CPPFLAGS+=\
	$(UBA_CFLAGS)

uba-creator-introspection.h: UbaCreator.xml Makefile
	dbus-binding-tool --mode=glib-client $< > $@

uba-service-introspection.h: UbaService.xml Makefile
	dbus-binding-tool --mode=glib-client $< > $@
