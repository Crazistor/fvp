/*
 * File: media_player_event_manager.h
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

#ifndef MEDIA_PLAYER_EVENT_MANAGER_H
#define MEDIA_PLAYER_EVENT_MANAGER_H

#ifdef __cplusplus
extern "C"{
#endif

#include"fvp_common.h"
#include"array_list.h"



struct _MediaPlayerEventManager;
typedef struct _MediaPlayerEventManager MediaPlayerEventManager;

typedef enum _MediaPlayerEventType
{
	MEDIA_PLAYER_OPENING = 0x123,
	MEDIA_PLAYER_PAUSEED,
	MEDIA_PLAYER_STOPED,
}MediaPlayerEventType;

typedef void (*player_callback)(MediaPlayerEventManager *thiz, void *user_data);


MediaPlayerEventManager *media_player_event_manager_create(void);


int media_player_event_manager_register_listener(MediaPlayerEventManager *thiz,
															MediaPlayerEventType event_type,
															player_callback callback,
															void *user_data,
															int remove_enable);

int media_player_event_manager_send_event(MediaPlayerEventManager *thiz, MediaPlayerEventType event_type);


void media_player_event_manager_destroy(MediaPlayerEventManager *thiz);


#ifdef __cplusplus
}
#endif


#endif /*MEDIA_PLAYER_EVENT_MANAGER_H*/

