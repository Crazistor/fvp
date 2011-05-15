/*
 * File: access_avi.c
 * Author:  zhoumin  <dcdcmin@gmail.com>
 * Brief:   
 *
 * Copyright (c) 2010 - 2013  zhoumin <dcdcmin@gmail.com>>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WI_HOUT ANY WARRANTY; without even the implied warranty of
 * MER_HANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *_History:
 * ================================================================
 * 2011-4-28 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"access_avi.h"
#include"libavcodec/avcodec.h"
#include"libavformat/avformat.h"


typedef struct _PrivInfo
{
	char *file_path;	/*file path*/
	AVFormatContext *format_ctx;
	int video_stream_index;
	int audio_stream_index;
	Block *block;
}PrivInfo;


#define ACCESS_KEY_WORKD "file"

static int avi_parse_path(char *access_path, char *file_name, size_t file_name_len)
{
	 return_val_if_failed(access_path != NULL && file_name != NULL, -1);

	 if(strstr(access_path, ACCESS_KEY_WORKD) == 0)
	 {
		 printf("not math the key workd(%s)\n", ACCESS_KEY_WORKD);
		 return -1;
	 }

	 char *p = NULL;
	 p = strchr(access_path, ':');
	 if(p != NULL)
	 {
		strncpy(file_name, p + 1, file_name_len);
		return 0;
	 }

	 return -1;
}


static Block *access_avi_block(Access *thiz)
{
	return_val_if_failed(thiz != NULL, NULL);

	DECL_PRIV(thiz, priv);
	
	AVPacket packet;
	
	if(av_read_frame(priv->format_ctx, &packet)>=0) 
	{
		if(packet.stream_index == priv->video_stream_index) 
		{
			memcpy(priv->block->p_buffer, packet.data, packet.size);
			priv->block->buffer_len = packet.size;
			priv->block->frame_flag = VIDEO_FRAME_FLAG;
			av_free_packet(&packet);
			return priv->block;
		}	
		else if(packet.stream_index == priv->audio_stream_index)
		{
			memcpy(priv->block->p_buffer, packet.data, packet.size);
			priv->block->buffer_len = packet.size;
			priv->block->frame_flag = AUDIO_FRAME_FLAG;
			av_free_packet(&packet);
			return priv->block;
		}
		else
		{
			printf("not define this stream!\n");
		}
	}		

	msg_dbg("access_avi_block error:return null !\n");
	return NULL;
}

	
static void access_avi_destroy(Access *thiz)
{
	if(thiz)
	{
		DECL_PRIV(thiz, priv);
		
		block_destroy(priv->block);
		COMM_FREE(priv->file_path);
		av_close_input_file(priv->format_ctx);
		
		COMM_ZFREE(thiz, sizeof(*thiz) + sizeof(PrivInfo));
	}
	return;
}

static int access_init_ffmpeg(Access *thiz, char *file_path)
{	
	av_register_all();
	
	AVFormatContext *pFormatCtx;

	if(av_open_input_file(&pFormatCtx, file_path, NULL, 0, NULL)!=0)
	{
		printf("Open the file faield!\n");
		return -1; 
	}
	
	if(av_find_stream_info(pFormatCtx)<0)
	{
		printf("av_find_stream_info failed!\n");
		return -1; 
    }
    
	dump_format(pFormatCtx, 0, file_path, 0);

	int i;
	AVCodecContext *pCodecCtx;
	int videoStream=-1;
	int audioStream = -1;

	for(i=0; i<pFormatCtx->nb_streams; i++)
	{
		if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO) 
		{
			videoStream=i;
			break;
		}
	}
	
	if(videoStream==-1)
	{
		return -1; // Didn't find a video stream
	}

	for(i=0; i<pFormatCtx->nb_streams; i++)
	{
		if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO) 
		{
			audioStream=i;
			break;
		}
	}
	if(audioStream==-1)
	{
		return -1; // Didn't find a audio stream
	}

	DECL_PRIV(thiz, priv);

	priv->format_ctx = pFormatCtx;
	priv->video_stream_index = videoStream;
	priv->audio_stream_index = audioStream;

	msg_dbg("video stream index(%d) audioStream index(%d)\n", videoStream, audioStream);
	
	return 0;
}


Access *access_avi_create(char *access_path)
{
	return_val_if_failed(access_path, NULL);
		
	int fd = -1;
	char file_path[64] = {0};

	if(avi_parse_path(access_path, file_path, 64) != 0)
	{
		msg_dbg("Fun(%s) error parse the access_path(%s) failed!\n", __func__, access_path);
		return NULL;
	}

	Access *thiz = (Access *)COMM_ZALLOC(sizeof(Access) + sizeof(PrivInfo));
	return_val_if_failed(thiz != NULL, NULL);

	/*open the file */
	fd = open(file_path, O_RDONLY);
	if(fd <= 0)
	{
		msg_dbg("error:open the file failed! file path(%s)\n", file_path);
		return NULL;
	}

	thiz->seek = NULL;
	thiz->read = NULL;
	thiz->block = access_avi_block;
	thiz->control = NULL;
	thiz->destroy = access_avi_destroy;

	DECL_PRIV(thiz, priv);

	priv->file_path = COMM_STRDUP(file_path);
	priv->block = block_create(MAX_H264_PACKET_LEN);
	
	access_init_ffmpeg(thiz, file_path);
	
	return thiz;
}


