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


#define AUDIO_ADPCM_TYPE ADPCM_TYPE_DVI4/* ADPCM_TYPE_IMA, ADPCM_TYPE_DVI4*/
#define AUDIO_AAC_TYPE AAC_TYPE_AACLC   /* AAC_TYPE_AACLC, AAC_TYPE_EAAC, AAC_TYPE_EAACPLUS*/
#define G726_BPS MEDIA_G726_16K         /* MEDIA_G726_16K, MEDIA_G726_24K ... */
#define AMR_FORMAT AMR_FORMAT_MMS       /* AMR_FORMAT_MMS, AMR_FORMAT_IF1, AMR_FORMAT_IF2*/
#define AMR_MODE AMR_MODE_MR74         /* AMR_MODE_MR122, AMR_MODE_MR102 ... */
#define AMR_DTX 0


struct  _AudioDecoder
{
	int audio_decode_channel;
	PAYLOAD_TYPE_E decode_payload_type;
};

static int create_audio_decode_chn(int audio_dec_channel, PAYLOAD_TYPE_E payload_type)
{
    HI_S32 ret;
    ADEC_CHN_ATTR_S attr;

    attr.enType = payload_type;
    attr.u32BufSize = 20;
    attr.enMode = ADEC_MODE_STREAM;/* propose use pack mode in your app */
        
    if (PT_ADPCMA == attr.enType)
    {
        ADEC_ATTR_ADPCM_S stAdpcm;
        attr.pValue = &stAdpcm;
        stAdpcm.enADPCMType = AUDIO_ADPCM_TYPE ;
    }
    
    else if (PT_G711A == attr.enType || PT_G711U == attr.enType)
    {
        ADEC_ATTR_G711_S stAdecG711;
        attr.pValue = &stAdecG711;
    }
    else if (PT_G726 == attr.enType)
    {
        ADEC_ATTR_G726_S stAdecG726;
        attr.pValue = &stAdecG726;
        stAdecG726.enG726bps = G726_BPS ;      
    }
    else if (PT_AMR == attr.enType)
    {
        ADEC_ATTR_AMR_S stAdecAmr;
        attr.pValue = &stAdecAmr;
        stAdecAmr.enFormat = AMR_FORMAT;
    }
    else if (PT_AAC == attr.enType)
    {
        ADEC_ATTR_AAC_S stAdecAac;
        attr.pValue = &stAdecAac;
        attr.enMode = ADEC_MODE_STREAM;/* aac now only support stream mode */
    }
    else if (PT_LPCM == attr.enType)
    {
        ADEC_ATTR_LPCM_S stAdecLpcm;
        attr.pValue = &stAdecLpcm;
        attr.enMode = ADEC_MODE_PACK;/* lpcm must use pack mode */
    }
    else
    {
        msg_dbg("invalid aenc payload type:%d\n", attr.enType);
        return -1;
    }         
    
    /* create audio decode chn*/
    ret = HI_MPI_ADEC_CreateChn(audio_dec_channel, &attr);
    if (ret)
    {
        msg_dbg("HI_MPI_ADEC_CreateChn create adec chn %d err:0x%x\n", audio_dec_channel, ret);
        return -1; 
    }
    
    return 0;
}

AudioDecoder *audio_decoder_create(int audio_dec_channel, PAYLOAD_TYPE_E payload_type)
{
    AudioDecoder *thiz = NULL;

    if(create_audio_decode_chn(audio_dec_channel, payload_type) != 0)
    {
        msg_dbg("Fun[%s] error : create audio decode chn failed!\n", __func__);
        return NULL;
    }
        
    thiz = (AudioDecoder *)COMM_ZALLOC(sizeof(AudioDecoder));	
    if(thiz == NULL)
    {
    	msg_dbg("Not enough memory!\n");
    	return NULL;
    }
    
    thiz->audio_decode_channel = audio_dec_channel;
    thiz->decode_payload_type = payload_type;
        
    return  thiz;
}

int audio_decoder_get_audio_decode_chn(AudioDecoder *thiz)
{
	return_val_if_failed(thiz != NULL, -1);
		
	return thiz->audio_decode_channel;
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

        COMM_ZFREE(thiz, sizeof(AudioDecoder));
        
    }
	
    return;
}



