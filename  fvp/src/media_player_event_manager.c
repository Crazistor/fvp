/*
 * File: media_player_event_manager.c
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
 * 2011-5-16 zhoumin <dcdcmin@gmail.com> created
 *
 */
#include"media_player_event_manager.h"


struct _MediaPlayerEventManager
{
	int i_count;
	ArrayList *array;	
};

typedef struct _MediaPlayerEventListener
{
	MediaPlayerEventType type;
	void *user_data;
	player_callback callback_func;
	int remove_enable;	/*1 -- remove the listener after do th calllback_func */
}MediaPlayerEventListener;

MediaPlayerEventManager *media_player_event_manager_create(void)
{
	MediaPlayerEventManager *thiz = NULL;
	
	thiz = (MediaPlayerEventManager *)COMM_ZALLOC(sizeof(MediaPlayerEventManager));
	if(thiz == NULL)
	{
		msg_dbg("Not enough memory!\n");
		return NULL;
	}

	thiz->i_count = 0;
	thiz->array = array_list_create();

	return thiz;
}

int media_player_event_manager_register_listener(MediaPlayerEventManager *thiz,
															MediaPlayerEventType event_type,
															player_callback callback,
															void *user_data,
															int remove_enable)
{
	return_val_if_failed(thiz != NULL, -1);

	MediaPlayerEventListener *listener = (MediaPlayerEventListener *)COMM_ALLOC(sizeof(MediaPlayerEventListener));

	listener->type = event_type;
	listener->callback_func = callback;
	listener->user_data = user_data;
	listener->remove_enable = remove_enable;

	array_list_add(thiz->array, (void *)listener);
	thiz->i_count ++;

	return 0;
}


int media_player_event_manager_send_event(MediaPlayerEventManager *thiz, MediaPlayerEventType event_type)
{
//	msg_dbg("media_player_event_manager_send_event\n");
	return_val_if_failed(thiz != NULL, -1);

	int i = 0;
	MediaPlayerEventListener *listener = NULL;
		
	for(i = 0; i < thiz->i_count; i++)
	{
		listener = (MediaPlayerEventListener *)array_list_get_data_by_id(thiz->array, i);
		if(listener->type == event_type)
		{
			listener->callback_func(thiz, listener->user_data);
			if(listener->remove_enable)
			{
				array_list_remove(thiz->array, listener, sizeof(MediaPlayerEventListener));
				COMM_FREE(listener);
			}	
		}			
	}

	return 0;
}


void media_player_event_manager_destroy(MediaPlayerEventManager *thiz)
{
	if(thiz != NULL)
	{

		if(thiz->array)
		{
			array_list_destroy(thiz->array);
		}

		COMM_ZFREE(thiz, sizeof(thiz));
	}

	return;
}



