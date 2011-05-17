/*
 * File: video_decoder.h
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
 * Fri Apr  8 14:02:59 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

 
#include"fvp_typedef.h"
#include"fvp_common.h"
#include"block.h"
#include<stdarg.h>

#ifndef VIDEO_DECODER_H
#define VIDEO_DECODER_H


#ifdef __cplusplus
extern "C"{
#endif 

enum _DecoderQuery
{
    QUERY_DECODER_PAUSE,     /*pause decode*/   
    QUERY_DECODER_RESUME,    /*resume decode*/

	QUERY_DECODER_INVALID,
};


struct _VideoDecoder;
typedef struct _VideoDecoder VideoDecoder;

/*
 *video  decoder create
 */
VideoDecoder *video_decoder_create(int vdec_chn, int max_pic_width, int max_pic_height);

/*
 *  input parameter: block  video 
 */
int video_decoder_decode_data(VideoDecoder *thiz, Block *block);

/*
  * return  true  --video decoder can read next frame
 		 false -- video decoder can't read next frame
 */
bool video_decoder_able_to_decode_next_data(VideoDecoder *thiz);

/*
  * controld the video decoder
  */
int video_decoder_control(VideoDecoder *thiz, int i_query, va_list args);

/*
 * destroy the video decoder 
 */
void video_decoder_destroy(VideoDecoder *thiz);


#ifdef  __cplusplus
}
#endif 


#endif /*VIDEO_DECODER_H*/



