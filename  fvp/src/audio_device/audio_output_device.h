/*
 * File: audio_output_device.h
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
 * 2011-5-17 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef AUDIO_OUTPUT_DEVICE_H
#define AUDIO_OUTPUT_DEVICE_H

#include"fvp_common.h"
#include"fvp_typedef.h"


#ifdef __cplusplus
extern "C"
#endif 


struct _AudioOutputDevice;
typedef struct _AudioOutputDevice AudioOutputDevice;

typedef enum _AudioBindType
{
	BIND_AUDIO_DECODE,
	BIND_AUDIO_INPUT,
	BIND_INVALID,
}AudioBindType;

AudioOutputDevice *audio_output_device_create(AUDIO_DEV ao_dev_id, int ao_channel,);

int  audio_output_device_init(AudioOutputDevice*thiz,  PAYLOAD_TYPE_E playload_type);

int audio_output_device_bind_decode_chn(AudioOutputDevice *thiz,  int audio_decode_chn);

int audio_output_device_bind_input_chn(AudioOutputDevice *thiz, int audio_input_chn);

void audio_output_device_destroy(AudioOutputDevice *thiz);




#ifdef __cplusplus
extern "C"
#endif 



#endif /*AUDIO_OUTPUT_DEVICE_H*/
 
