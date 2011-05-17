/*
 * File: media_play.c
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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * Tue Apr 12 16:01:11 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */


#include"media_player.h"
#include"access_file.h"
#include"video_decoder.h"
#include"fvp_lock.h"
#include"fvp_msg.h"
#include"fvp_function.h"
#include"access_factory.h"

struct _MediaPlayer
{	
	Access *access;
	Decoder *decoder;
	VideoWindows *windows;
	int vochn;		
	fvp_mutex_t lock;
	MedaPlayerState state;
	InputState input_control_state;
	MediaPlayerEventManager *event_manager;
};

static int media_player_internal_control(MediaPlayer *thiz, int query, va_list args)
{
	return_val_if_failed(thiz != NULL && query < QUERY_INVALID, -1);

    double *postion;
    
	switch(query)
	{
		case QUERY_GET_POSITON:
            postion = (double*)va_arg( args, double *);
            msg_dbg("QUERY_GET_POSITON\n");
			return 0;
		case QUERY_SET_POSITION:
		
			return 0;
		case QUERY_GET_TIME:

			return 0;
		case QUERY_SET_TIME:

		
			return 0;
		default:
			msg_dbg("fun[%s] unknow query \n");
			return -1;
	}
}

static int decoder_wait(MediaPlayer *thiz)
{
	while(1)
	{
		if(video_decoder_able_to_decode_next_data(thiz->decoder))
		{
			break;
		}	
	}
	return 0;
}

static void *media_play_thread(void *para)
{	
	msg_dbg("fun[%s] create a thread\n", __func__);

	MediaPlayer *thiz = (MediaPlayer *)para;
	
	Block *block = NULL;
	bool b_paused = false;

	PROFILE_START();
	while(1)
	{		
		b_paused = (thiz->input_control_state == PAUSE_S);
		if(!b_paused)
		{
			/*read a frame block from the access*/
			block = access_block(thiz->access);

			if(block != NULL)
			{
				if(block->frame_flag == VIDEO_FRAME_FLAG)
				{
					/*handle the  video frame data*/
					video_decoder_decode_data(thiz->decoder, block);
					decoder_wait(thiz);
				}
				else if(block->frame_flag == AUDIO_FRAME_FLAG)
				{
					
				}	
			}
			else
			{
				/*read file over or error*/
				msg_dbg("read file over or get a error!\n");
				break;
			}
		}
	}
	PROFILE_END("Decode video Over or get a error!\n");
	/*read file over or get a error 
		set the play state is stoped*/
	media_player_event_manager_send_event(thiz->event_manager, MEDIA_PLAYER_STOPED);
	
	/* destroy the media player*/
	media_player_destroy(thiz);
	
	return NULL;
}


MediaPlayer *media_player_create(int vdec_chn, 
									RECT_S out_rect, 
									char *access_path,
									VideoWindows *windows,
									int vochn)
{
	MediaPlayer *thiz = (MediaPlayer *)COMM_ALLOC(sizeof(MediaPlayer));
	if(thiz == NULL)
	{
		msg_dbg("Fun[%s] not enough memory!\n", __func__);
		return NULL;
	}

	thiz->access = accesser_factory_create_a_accesser(access_path);
	
	return_val_if_failed(thiz->access != NULL, NULL);
	
	thiz->decoder = video_decoder_create(vdec_chn, out_rect.u32Width, out_rect.u32Height);
	return_val_if_failed(thiz->decoder != NULL, NULL);
	thiz->windows = windows;
	if(thiz->windows != NULL)
	{
		video_windows_ref(thiz->windows);
	}
	thiz->vochn = vochn;
	thiz->state = MEDIA_NOT_START;
	thiz->input_control_state = INIT_S;
	fvp_mutex_init(&thiz->lock);
	
	thiz->event_manager = media_player_event_manager_create();
	
	return thiz;		
}

void media_player_destroy(MediaPlayer *thiz)
{
	if(thiz)
	{
		msg_dbg("Fun[%s]\n", __func__);

		access_destroy(thiz->access);
		video_decoder_destroy(thiz->decoder);
		
		if(thiz->windows != NULL)
		{
		
			video_windows_unref(thiz->windows);
		}
		
		if(thiz->event_manager)
		{
			media_player_event_manager_destroy(thiz->event_manager);
		}

		COMM_ZFREE(thiz, sizeof(*thiz));
	}
	
	return;	
}

int media_player_play(MediaPlayer *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	fvp_mutex_lock(&thiz->lock);
	
	msg_dbg("Fun[%s]\n", __func__);

	/*if not start play the record or stream, start to replay it*/
	if(thiz->state == MEDIA_NOT_START)
	{
		/*create a thread */
		create_normal_thread(media_play_thread, (void *)thiz, NULL);
		thiz->state = MEDIA_PLAYING;
	}
	else
	{
		/*change the play state*/
		if(thiz->state == MEDIA_PAUSED)
		{			
			video_windows_resume_vo_channel(thiz->windows, thiz->vochn);
			thiz->state = MEDIA_PLAYING;
		}
	}

	/*if the state is pause, then change to play status*/
	fvp_mutex_unlock(&thiz->lock);
	
	return 0;
}

int media_player_pause(MediaPlayer *thiz)
{
	return_val_if_failed(thiz != NULL, -1);
	
	fvp_mutex_lock(&thiz->lock);

	msg_dbg("Fun[%s]\n", __func__);

	if(thiz->state == MEDIA_PLAYING)
	{
		msg_dbg("Fun[%s] PAUSE_SPAUSE_SPAUSE_S\n", __func__);
		thiz->state = MEDIA_PAUSED;
		video_windows_pause_vo_channel(thiz->windows, thiz->vochn);
	}
	
	fvp_mutex_unlock(&thiz->lock);
	return 0;
}

int media_player_stop(MediaPlayer *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	media_player_event_manager_send_event(thiz->event_manager, MEDIA_PLAYER_STOPED);

	/* destroy the media player*/
	media_player_destroy(thiz);
	
	return 0;
}

int media_player_frame_play(MediaPlayer *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	fvp_mutex_lock(&thiz->lock);

	msg_dbg("Fun[%s]\n", __func__);

	video_windows_step_vo_channel(thiz->windows, thiz->vochn);	
	
	fvp_mutex_unlock(&thiz->lock);
	
	return 0;
}

int media_player_fast_play(MediaPlayer *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	msg_dbg("Fun[%s]\n", __func__);
	
	return 0;
}


int media_player_slow_play(MediaPlayer *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	msg_dbg("Fun[%s]\n", __func__);
	
	return 0;
}


int media_player_control(MediaPlayer *thiz, int query, ...)
{
	return_val_if_failed(thiz != NULL && query < QUERY_INVALID, -1);
	
    va_list args;
    int     res;

    va_start(args, query);
    res = media_player_internal_control(thiz, query, args);
    va_end( args );

    return res;
}


MediaPlayerEventManager *media_player_get_event_manager(MediaPlayer *thiz)
{
	return_val_if_failed(thiz != NULL, NULL);

	return thiz->event_manager;
}




