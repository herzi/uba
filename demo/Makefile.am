SUBDIRS=services

noinst_PROGRAMS=\
	client \
	uba-demo \
	uba-example \
	$(NULL)

BUILT_SOURCES=\
	uba-marshallers.c \
	uba-marshallers.h \
	uba-service-binding.h \
	uba-service-glue.h \
	$(NULL)

uba_demo_SOURCES=\
	$(BUILT_SOURCES) \
	uba-demo.c \
	uba-service.c \
	uba-service.h \
	$(NULL)

uba_example_SOURCES=\
	$(BUILT_SOURCES) \
	uba-example.c \
	uba-service.c \
	uba-service.h \
	$(NULL)

uba-service-glue.h: UbaService.xml Makefile
	dbus-binding-tool --mode=glib-server --prefix=uba_service $< > $@

uba-service-binding.h: UbaService.xml Makefile
	dbus-binding-tool --mode=glib-client $< > $@

uba-marshallers.h: $(MARSHALLERS) Makefile
	(cd $(srcdir) && \
	$(GLIB_GENMARSHAL) --prefix=uba_marshal $< --header) > xgen-$@ \
	&& (cmp -s xgen-$@ $@ || cp xgen-$@ $@) \
	&& rm -f xgen-$@ xgen-$@~

uba-marshallers.c: $(MARSHALLERS) Makefile
	(cd $(srcdir) && \
	echo "#include \"uba-marshallers.h\""; \
	$(GLIB_GENMARSHAL) --prefix=uba_marshal $< --body) > xgen-$@ \
	&& (cmp -s xgen-$@ $@ || cp xgen-$@ $@) \
	&& rm -f xgen-$@ xgen-$@~

AM_CPPFLAGS=\
	$(UBA_CFLAGS) \
	-I$(top_srcdir)/uba
	$(NULL)
LDADD=\
	$(UBA_LIBS) \
	../uba/libuba.la \
	$(NULL)

CLEANFILES=$(BUILT_SOURCES)

MARSHALLERS=uba-marshallers.list

EXTRA_DIST=\
	$(MARSHALLERS) \
	UbaService.xml \
	$(NULL)
