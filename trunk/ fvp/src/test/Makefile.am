include $(abs_top_srcdir)/src/rules.mk

noinst_PROGRAMS=mpp_media_test video_windows_test access_avi_test  access_file_test 

mpp_media_test_SOURCES=mpp_media_test.c
mpp_media_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)

video_windows_test_SOURCES=video_windows_test.c
video_windows_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)

access_avi_test_SOURCES=access_avi_test.c
access_avi_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)

access_file_test_SOURCES=access_avi_test.c
access_file_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)







