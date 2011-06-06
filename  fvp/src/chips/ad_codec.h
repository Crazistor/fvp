/*
 * File: ad_codec.h
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
 * 2011-05-19 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef AD_CODEC_H
#define AD_CODEC_H

#include"fvp_common.h"
#include"fvp_typedef.h"
#include"fvp_msg.h"

#ifdef __cplusplus
extern "C"{
#endif

struct _ADCodec;
typedef struct _ADCodec ADCodec;

/*create*/
ADCodec *ad_codec_create(void);

/*audio  config rate
 *@audio_sample_rate the audio_sample_rate */
int ad_codec_config_audio_rate(ADCodec *thiz, AUDIO_SAMPLE_RATE_E audio_sample_rate);

/*destroy */
void ad_codec_destroy(ADCodec *thiz);


#ifdef __cplusplus
}
#endif 

#endif /*AD_CODEC_H*/

