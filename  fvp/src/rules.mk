INCLUDES= -Wall -g -I$(top_srcdir)/lib/mpp/include \
		  -I$(top_srcdir)/lib/ffmpeg/include \
		  -I$(top_srcdir)/src/misc \
		  -I$(top_srcdir)/src/common \
		  -I$(top_srcdir)/src/access \
		   -I$(top_srcdir)/src/decoder \
		   -I$(top_srcdir)/src\
		  -I$(top_srcdir)/src/video_windows 

INCLUDES+=-I$(top_srcdir)/lib/mpp/include 
MYLDFLAGS= $(top_srcdir)/lib/mpp/lib_amr_fipop.a \
					 $(top_srcdir)/lib/mpp/libmpi.a \
					 $(top_srcdir)/lib/mpp/lib_aacdec.a \
					 $(top_srcdir)/lib/mpp/lib_aacenc.a \
					 $(top_srcdir)/lib/mpp/lib_aec.a \
					 $(top_srcdir)/lib/mpp/lib_amr_fipop.a \
					 $(top_srcdir)/lib/mpp/lib_VoiceEngine.a \
					 $(top_srcdir)/lib/mpp/libloadbmp.a \
					 $(top_srcdir)/lib/mpp/libresampler.a \
					 $(top_srcdir)/lib/mpp/libtde.a 

INCLUDES+=-I$(top_srcdir)/lib/ffmpeg/include
MYLDFLAGS+=$(top_srcdir)/lib/ffmpeg/libavformat.a \
			  $(top_srcdir)/lib/ffmpeg/libavcodec.a \
			$(top_srcdir)/lib/ffmpeg/libavutil.a



