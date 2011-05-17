/*
 * File: audio_decoder.c
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


#include"audio_decoder.h"

struct  _AudioDecoder
{
	int audio_decode_channel;
	
};

AudioDecoder *audio_decoder_create(int audio_dec_channel)
{
	AudioDecoder *thiz = NULL;

	thiz = (AudioDecoder *)COMM_ALLOC(sizeof(AudioDecoder));	
	if(thiz == NULL)
	{
		msg_dbg("Not enough memory!\n");
	}

	thiz->audio_decode_channel = audio_dec_channel;
	
	return  thiz;
}

int audio_decoder_decode_data(AudioDecoder *thiz, Block *block)
{
	return_val_if_failed(thiz != NULL, -1);

    AUDIO_STREAM_S stAudioStream;    
	HI_S32 s32ret;
	
	stAudioStream.pStream = block->p_buffer;
	stAudioStream.u32Len = block->buffer_len;
	s32ret = HI_MPI_ADEC_SendStream(thiz->audio_decode_channel, &stAudioStream, HI_IO_BLOCK);
	if(s32ret != HI_SUCCESS)
	{
		msg_dbg("send audio stream err s32Ret(0x%x)\n", s32ret);
		return -1;
	}
	
	return 0;
}

void audio_decoder_destroy(AudioDecoder *thiz)
{
	if(thiz)
	{
		HI_S32 s32ret;
		s32ret = HI_MPI_ADEC_DestroyChn(thiz->audio_decode_channel);
		if(s32ret != HI_SUCCESS)
		{	
			msg_dbg("HI_MPI_ADEC_DestroyChn fail 0x%08x.\n", s32ret);
		}
	}
	
	return;
}



