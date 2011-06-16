include $(abs_top_srcdir)/src/rules.mk

noinst_PROGRAMS=watchdog_test 

watchdog_test_SOURCES=fvp_api_watchdog_test.c
watchdog_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)


