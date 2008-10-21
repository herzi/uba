noinst_LTLIBRARIES=\
	libmock-objects.la

libmock_objects_la_SOURCES=\
	mock-dbus-session.c \
	mock-dbus-session.h

noinst_PROGRAMS=\
	e-mock-dbus-session \
	e-uba-container

e_mock_dbus_session_SOURCES=\
	e-mock-dbus-session.c

AM_CPPFLAGS=\
	-I$(top_srcdir) \
	$(UBA_CFLAGS)
LDADD=\
	$(top_builddir)/uba/libuba.la \
	libmock-objects.la \
	$(UBA_LIBS)

if HAVE_CHECK
noinst_PROGRAMS+=\
	m-mock-objects \
	m-uba

m_uba_SOURCES=\
	m-uba.c \
	s-uba-container.c \
	s-uba-container.h \
	t-uba-container-scrollable.c

m_mock_objects_SOURCES=\
	m-mock-objects.c \
	s-mock-dbus-session.c \
	s-mock-dbus-session.h

AM_CPPFLAGS+=\
	$(CHECK_CFLAGS)
LDADD+=\
	$(CHECK_LIBS)
endif

TESTS=$(noinst_PROGRAMS)

check-valgrind: all-am
	TESTS_ENVIRONMENT="valgrind --leak-check=full" $(MAKE) $(AM_MAKEFLAGS) check-TESTS

