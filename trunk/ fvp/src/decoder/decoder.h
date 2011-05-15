/*
 * File: decoder.h
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

#ifndef DECODER_H
#define DECODER_H

#include"mpp_common.h"
#include"fvp_common.h"
#include"block.h"
#include<stdarg.h>

#ifdef __cplusplus
extern "C"{
#endif 

enum _DecoderQuery
{
    QUERY_DECODER_PAUSE,     /*pause decode*/   
    QUERY_DECODER_RESUME,    /*resume decode*/

	QUERY_DECODER_INVALID,
};


struct _Decoder;
typedef struct _Decoder Decoder;

/*
 * decoder create
 */
Decoder *decoder_create(int vdec_chn, int max_pic_width, int max_pic_height);

/*
 *  input parameter: block  video or audio data
 */
int decoder_decode_data(Decoder *thiz, Block *block);

/*
  * return  true  -- decoder can read next frame
 		 false -- decoder can't read next frame
 */
bool decoder_able_to_decode_next_data(Decoder *thiz);


/*
  * controld the decoder
  */
int decoder_control(Decoder *thiz, int i_query, va_list args);

/*
 * destroy the decoder 
 */
void decoder_destroy(Decoder *thiz);


#ifdef  __cplusplus
}
#endif 


#endif /*DECODER_H*/



