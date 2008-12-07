noinst_PROGRAMS=\
	client \
	service \
	$(NULL)

BUILT_SOURCES=\
	uba-service-binding.h \
	uba-service-glue.h \
	$(NULL)

service_SOURCES=\
	$(BUILT_SOURCES) \
	service.c \
	uba-service.c \
	uba-service.h \
	$(NULL)

uba-service-glue.h: UbaService.xml Makefile
	dbus-binding-tool --mode=glib-server --prefix=uba_service $< > $@

uba-service-binding.h: UbaService.xml Makefile
	dbus-binding-tool --mode=glib-client $< > $@

AM_CPPFLAGS=\
	$(UBA_CFLAGS) \
	-I$(top_srcdir)/uba
	$(NULL)
LDADD=\
	$(UBA_LIBS) \
	../uba/libuba.la \
	$(NULL)
