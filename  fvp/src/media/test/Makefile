CROSS_COMPILE = arm-hismall-linux-
CC = $(CROSS_COMPILE)gcc

CFLAGS = -lpthread

SOURCE = ../access/access_file.c ../input/demuxer.c ../decoder/decoder.c ../../misc/block.c ../../misc/fvp_msg.c ../../misc/fvp_mutex.c  ../../misc/fvp_function.c

MPP_DIR=../../../lib/mpp

STATIC_LIB_LIST+=$(MPP_DIR)/libmpi.a \
				$(MPP_DIR)/lib_VoiceEngine.a \
				$(MPP_DIR)/lib_amr_spc.a \
				$(MPP_DIR)/lib_amr_fipop.a \
				$(MPP_DIR)/lib_aec.a \
				$(MPP_DIR)/libloadbmp.a \
				$(MPP_DIR)/libtde.a \
				$(MPP_DIR)/lib_aacdec.a \
				$(MPP_DIR)/lib_aacenc.a \
				$(MPP_DIR)/libresampler.a

CFLAGS += $(STATIC_LIB_LIST)

ACCESS_FILE_SOURCE = access_file_test.c $(SOURCE)
DEMUXER_SOURCE = demuxer_test.c $(SOURCE)
MEDIA_PLAYER_SOURCE = media_player_test.c $(SOURCE) ../media_player.c
MPP_SYSTEM_SOURCE = mpp_system_test.c ../mpp_system.c  $(SOURCE) 

INCLUDE_PATH =  -I../access  -I../input -I../decoder  -I../../misc -I../../common  -I../../media -I$(MPP_DIR)/include

all:
		$(CC) -o access_file_test $(ACCESS_FILE_SOURCE) $(INCLUDE_PATH) $(CFLAGS)
		$(CC) -o demuxer_test $(DEMUXER_SOURCE) $(INCLUDE_PATH) $(CFLAGS)
		$(CC) -o media_player_test $(MEDIA_PLAYER_SOURCE) $(INCLUDE_PATH) $(CFLAGS)
		$(CC) -o mpp_system_test $(MPP_SYSTEM_SOURCE) $(INCLUDE_PATH) $(CFLAGS)
		#@./media_player_test
clean:
		rm -f access_file_test
		rm -f demuxer_test
		rm -f media_player_test
