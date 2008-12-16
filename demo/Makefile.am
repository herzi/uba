SUBDIRS=services

noinst_PROGRAMS=\
	client \
	uba-demo \
	uba-example \
	$(NULL)

BUILT_SOURCES=\
	uba-creator-glue.h \
	uba-marshallers.c \
	uba-marshallers.h \
	$(NULL)

uba_demo_SOURCES=\
	$(BUILT_SOURCES) \
	uba-demo.c \
	uba-creator.c \
	uba-creator.h \
	$(NULL)

uba_example_SOURCES=\
	$(BUILT_SOURCES) \
	uba-example.c \
	uba-creator.c \
	uba-creator.h \
	$(NULL)

uba-creator-glue.h: $(top_srcdir)/uba/UbaCreator.xml Makefile
	dbus-binding-tool --mode=glib-server --prefix=uba_creator $< > $@

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
	$(NULL)
