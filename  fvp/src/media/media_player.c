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
#include"demuxer.h"
#include"access_file.h"
#include"decoder.h"
#include"fvp_lock.h"
#include"fvp_msg.h"
#include"fvp_function.h"

struct _MediaPlayer
{	
	Access *access;
	Decoder *decoder;
	fvp_mutex_t lock;
	MedaPlayerState state;
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


static void *media_play_thread(void *para)
{	
	msg_dbg("fun[%s] create a thread\n", __func__);

	MediaPlayer *thiz = (MediaPlayer *)para;
	
	Block *block = NULL;

	/*main loop*/
	while(1)
	{		
		/*read a frame block from the access*/
		block = access_block(thiz->access);
		
		/*handle the  block*/
		decoder_decode_data(thiz->decoder, block);
		
		sleep(1);
	}
	
	return NULL;
}

MediaPlayer *media_player_create()
{
	MediaPlayer *thiz = (MediaPlayer *)COMM_ALLOC(sizeof(MediaPlayer));
	if(thiz == NULL)
	{
		msg_dbg("Fun[%s] not enough memory!\n", __func__);
		return NULL;
	}

	thiz->access = access_file_create("test.txt");
	return_val_if_failed(thiz->access != NULL, NULL);
	
//	thiz->decoder = decoder_create();
	return_val_if_failed(thiz->decoder != NULL, NULL);
	thiz->state = MEDIA_NOT_START;
	fvp_mutex_init(&thiz->lock);
	
	return thiz;		
}

void media_player_destroy(MediaPlayer *thiz)
{
	if(thiz)
	{
		msg_dbg("Fun[%s]\n", __func__);
		
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

	
	fvp_mutex_unlock(&thiz->lock);
	return 0;
}

int media_player_stop(MediaPlayer *thiz)
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

