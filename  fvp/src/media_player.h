/*
 * File: media_play.h
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
 * Tue Apr 12 15:58:29 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef MEDIA_PLAY_H
#define MEDIA_PLAY_H

#include"fvp_typedef.h"
#include"fvp_common.h"
#include"video_windows.h"
#include"media_player_event_manager.h"

#ifdef __cplusplus
extern "C"{
#endif 


struct _MediaPlayer;
typedef struct _MediaPlayer MediaPlayer;

typedef enum _MediaPlayerState
{
	MEDIA_NOT_START,
	MEDIA_PLAYING,
	MEDIA_FRAME_PLAY,
	MEDIA_PAUSED,
	MEDIA_STOPPED,
	MEDIA_INVALID
}MedaPlayerState;

typedef enum _InputState
{
    INIT_S = 0,
    OPENING_S,
    PLAYING_S,
    PAUSE_S,
    END_S,
    ERROR_S,
} InputState;

enum _MediaPlayerQuery
{
    QUERY_GET_POSITON,     /*get the file of replay postion*/   
    QUERY_SET_POSITION,    /*set the file of replay postion*/

	QUERY_GET_LENGTH,	  /*get the file length*/
	
    QUERY_GET_TIME,  	  /*get the file of replay current  time*/
    QUERY_SET_TIME,  	  /*set the time that the file to replay*/
						
    QUERY_INVALID,		 
};

typedef enum  _PlaySpeed
{
	SPEED_2X,
	SPEED_4X,
	SPEED_8X,
}PlaySpeed;

/*create a  media player*/
MediaPlayer *media_player_create(int vdec_chn, 
									RECT_S out_rect, 
									char *access_path,
									VideoWindows *windows,
									int vochn);

/*
 *set the media player voice status
 *@parameter is_voice_enable true -- disable the voice  false -- enable the voice
 *@return 0 -- success  
*/
int media_player_is_voice_enable(MediaPlayer *thiz, bool is_voice_enable);

/*
 * set the media player volume
 * @volume (0-100) 100 -- max volume value 0 -- min volume value
 * @return 0 set volume success , -1 set volume failed.
 */
int media_player_set_volume(MediaPlayer *thiz, unsigned int volume);

int media_player_play(MediaPlayer *thiz);

int media_player_pause(MediaPlayer *thiz);

int media_player_frame_play(MediaPlayer *thiz);

int media_player_fast_play(MediaPlayer *thiz, PlaySpeed speed);

int media_player_slow_play(MediaPlayer *thiz, PlaySpeed speed);

int media_player_get_file_size(MediaPlayer *thiz);

int media_player_get_position(MediaPlayer *thiz);

int media_player_set_position(MediaPlayer *thiz, int position);

int media_player_get_total_time(MediaPlayer *thiz);

int media_player_get_cur_time(MediaPlayer *thiz);

int media_player_seek_time(MediaPlayer *thiz, int time);

bool media_player_is_playing(MediaPlayer *thiz);

/**
 * Control function for media player.
 * @param thiz input handle
 * @param query query type
 * @return 0 if ok
 */
int media_player_control(MediaPlayer *thiz, int query, ...);

/*stop the media play*/
int media_player_stop(MediaPlayer *thiz);


MediaPlayerEventManager *media_player_get_event_manager(MediaPlayer *thiz);


/*
 * @return  the audio decode playload type 
 */
PAYLOAD_TYPE_E media_player_get_audio_playload_type(MediaPlayer *thiz);

												
/*destroy a media player*/
void media_player_destroy(MediaPlayer *thiz);


#ifdef __cplusplus
}
#endif 

#endif /*MEDIA_PLAY_H*/


