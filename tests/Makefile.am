if HAVE_CHECK
noinst_LTLIBRARIES=\
	libuba-testsession.la

libuba_testsession_la_SOURCES=\
	uba-test-session.c \
	uba-test-session.h

noinst_PROGRAMS=\
	m-uba-testsession
TESTS=$(noinst_PROGRAMS)

m_uba_testsession_SOURCES=\
	m-uba-testsession.c

LDADD=\
	$(CHECK_LIBS)
endif
