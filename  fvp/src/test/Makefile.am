include $(abs_top_srcdir)/src/rules.mk

noinst_PROGRAMS=video_windows_test access_avi_test  access_file_test  ad_codec_test media_play_test

media_play_test_SOURCES=media_play_test.c
media_play_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)

video_windows_test_SOURCES=video_windows_test.c
video_windows_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)

access_avi_test_SOURCES=access_avi_test.c
access_avi_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)

access_file_test_SOURCES=access_avi_test.c
access_file_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)

ad_codec_test = ad_codec_test.c
ad_codec_test_LDFLAGS=-lm -lpthread $(top_srcdir)/src/.libs/libmedia.a $(MYLDFLAGS)




