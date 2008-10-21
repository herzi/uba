noinst_PROGRAMS=\
	client \
	service \
	$(NULL)

AM_CPPFLAGS=\
	$(UBA_CFLAGS) \
	-I$(top_srcdir)/uba
	$(NULL)
LDADD=\
	$(UBA_LIBS) \
	../uba/libuba.la \
	$(NULL)
