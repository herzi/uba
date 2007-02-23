noinst_LTLIBRARIES=\
	libmock-objects.la

libmock_objects_la_SOURCES=\
	mock-dbus-session.c \
	mock-dbus-session.h

noinst_PROGRAMS=\
	e-test-session

e_test_session_SOURCES=\
	e-test-session.c

AM_CPPFLAGS=\
	$(UBA_CFLAGS)
LDADD=\
	libmock-objects.la \
	$(UBA_LIBS)

if HAVE_CHECK
noinst_PROGRAMS+=\
	m-uba-testsession

m_uba_testsession_SOURCES=\
	m-uba-testsession.c \
	s-test-session.c \
	s-test-session.h

AM_CPPFLAGS+=\
	$(CHECK_CFLAGS)
LDADD+=\
	$(CHECK_LIBS)
endif

TESTS=$(noinst_PROGRAMS)

check-valgrind: all-am
	TESTS_ENVIRONMENT="valgrind --leak-check=full" $(MAKE) $(AM_MAKEFLAGS) check-TESTS

