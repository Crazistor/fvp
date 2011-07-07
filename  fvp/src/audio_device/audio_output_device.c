/*
 * File: audio_output_device.c
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


#include"audio_output_device.h"


struct _AudioOutputDevice
{	
    AUDIO_DEV ao_dev_id;
    int ao_channel;
    
    PAYLOAD_TYPE_E playload_type;

    AudioBindType bind_type;
    int bind_audio_dec_chn;
    AUDIO_DEV ai_dev_id;
    int bind_audio_input_chn;
};

static int get_ao_dev_attr(PAYLOAD_TYPE_E playload_type, AIO_ATTR_S *aio_aattr)
{
	return_val_if_fail(aio_aattr != NULL, -1);

    aio_aattr->enWorkmode = AIO_MODE_I2S_SLAVE;
    aio_aattr->u32ChnCnt = 2;
    aio_aattr->enBitwidth = AUDIO_BIT_WIDTH_16;
    aio_aattr->enSamplerate = (playload_type!=PT_AAC) ? AUDIO_SAMPLE_RATE_8000 : AUDIO_SAMPLE_RATE_16000;
    aio_aattr->enSoundmode = AUDIO_SOUND_MODE_MOMO;
    aio_aattr->u32EXFlag = 1;
    aio_aattr->u32FrmNum = 30;
    aio_aattr->u32PtNumPerFrm = 320;
    aio_aattr->u32ClkSel = 0;

    if (PT_AAC == playload_type)/* AACLC encoder must be 1024 point */
    {
        aio_aattr->u32PtNumPerFrm = 1024;
    }
    else if (PT_AMR == playload_type)/* AMR encoder must be 160 point */
    {
        aio_aattr->u32PtNumPerFrm = 160;
    }

    return 0;
}

AudioOutputDevice *audio_output_device_create(AUDIO_DEV ao_dev_id, int ao_channel)
{
    AudioOutputDevice *thiz = NULL;

    thiz = (AudioOutputDevice *)COMM_ZALLOC(sizeof(AudioOutputDevice));
    if(thiz == NULL)
    {
        msg_dbg("Fun[%s] error : not enough memory!\n", __func__);
        return NULL;
    }

    thiz->ao_dev_id = ao_dev_id;
    thiz->ao_channel = ao_channel;
    
    thiz->bind_type = BIND_AUDIO_INVALID;
    thiz->bind_audio_dec_chn = -1;
    thiz->ai_dev_id = -1;
    thiz->bind_audio_input_chn = -1;
    
    return thiz;    
}


int  audio_output_device_init(AudioOutputDevice*thiz,  PAYLOAD_TYPE_E playload_type)
{
    return_val_if_fail(thiz != NULL,  -1);

    AIO_ATTR_S aio_aattr;
    HI_S32 s32ret;

    thiz->playload_type = playload_type;
    get_ao_dev_attr(playload_type, &aio_aattr);
    
    s32ret = HI_MPI_AO_SetPubAttr(thiz->ao_dev_id, &aio_aattr);
    if(HI_SUCCESS != s32ret)
    {
        msg_dbg("set ao %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
        return -1;
    }
    s32ret = HI_MPI_AO_Enable(thiz->ao_dev_id);
    if(HI_SUCCESS != s32ret)
    {
        msg_dbg("enable ao dev %d err:0x%x\n", thiz->ao_dev_id, s32ret);
        return -1;
    }
    s32ret = HI_MPI_AO_EnableChn(thiz->ao_dev_id, thiz->ao_channel);
    if(HI_SUCCESS != s32ret)
    {
        msg_dbg("enable ao chn %d err:0x%x\n", thiz->ao_channel, s32ret);
        return -1;
    }

    return 0;
}

int audio_output_device_bind_decode_chn(AudioOutputDevice *thiz,  int audio_decode_chn)
{
    return_val_if_fail(thiz != NULL, -1);

    HI_S32 s32ret;

    if(thiz->bind_type == BIND_AUDIO_DECODE)
    {
		s32ret = HI_MPI_AO_UnBindAdec(thiz->ao_dev_id, thiz->ao_channel, thiz->bind_audio_dec_chn);
		if (s32ret != HI_SUCCESS)
		{
			msg_dbg("HI_MPI_AO_BindAdec %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
			return -1;
		}	 
    }
    else if(thiz->bind_type == BIND_AUDIO_INPUT)
    {
		s32ret = HI_MPI_AO_UnBindAi(thiz->ao_dev_id, thiz->ao_channel, thiz->ai_dev_id, thiz->bind_audio_input_chn);
		if (s32ret != HI_SUCCESS)
		{
			msg_dbg("HI_MPI_AO_BindAdec %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
			return -1;
		}
    }

    s32ret = HI_MPI_AO_BindAdec(thiz->ao_dev_id, thiz->ao_channel, audio_decode_chn);
    if (s32ret != HI_SUCCESS)
    {
        msg_dbg("HI_MPI_AO_BindAdec %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
        return -1;
    }    

    thiz->bind_type = BIND_AUDIO_DECODE;
    thiz->bind_audio_dec_chn = audio_decode_chn;    

    return 0;
}

int audio_output_device_bind_input_chn(AudioOutputDevice *thiz, AUDIO_DEV ai_dev_id,  int audio_input_chn)
{
    return_val_if_fail(thiz != NULL, -1);
    HI_S32 s32ret;

    if(thiz->bind_type == BIND_AUDIO_DECODE)
    {
		s32ret = HI_MPI_AO_UnBindAdec(thiz->ao_dev_id, thiz->ao_channel, thiz->bind_audio_dec_chn);
		if (s32ret != HI_SUCCESS)
		{
			msg_dbg("HI_MPI_AO_BindAdec %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
			return -1;
		}	 
    }
    else if(thiz->bind_type == BIND_AUDIO_INPUT)
    {
		s32ret = HI_MPI_AO_UnBindAi(thiz->ao_dev_id, thiz->ao_channel, thiz->ai_dev_id, thiz->bind_audio_input_chn);
		if (s32ret != HI_SUCCESS)
		{
			msg_dbg("HI_MPI_AO_BindAdec %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
			return -1;
		}
    }

    s32ret = HI_MPI_AO_UnBindAi(thiz->ao_dev_id, thiz->ao_channel, ai_dev_id, audio_input_chn);
    if (s32ret != HI_SUCCESS)
    {
        msg_dbg("HI_MPI_AO_BindAdec %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
        return -1;
    }    

    thiz->bind_type = BIND_AUDIO_INVALID;
    thiz->ai_dev_id = -1;
    thiz->bind_audio_input_chn = -1;
    
    return 0;
}    


int audio_output_device_unbind_decode_chn(AudioOutputDevice *thiz,  int audio_decode_chn)
{
    return_val_if_fail(thiz != NULL, -1);

	if(thiz->bind_type != BIND_AUDIO_DECODE || thiz->bind_audio_dec_chn != audio_decode_chn)
	{
        msg_dbg("Fun[%s] failed :thiz->bind_type(%d) thiz->bind_audio_dec_chn(%d) audio_decode_chn(%d)\n", 
        								__func__,thiz->bind_type, thiz->bind_audio_dec_chn, audio_decode_chn);
		return -1;
	}
	
    HI_S32 s32ret;
    
	s32ret = HI_MPI_AO_UnBindAdec(thiz->ao_dev_id, thiz->ao_channel, audio_decode_chn);

	thiz->bind_type = BIND_AUDIO_INVALID;
	thiz->bind_audio_dec_chn = -1;
	
	return 0;
}

void audio_output_device_destroy(AudioOutputDevice *thiz)
{
    if(thiz)
    {   
        if(thiz->playload_type == BIND_AUDIO_DECODE)
        {
            HI_MPI_AO_UnBindAdec(thiz->ao_dev_id, thiz->ao_channel, thiz->bind_audio_dec_chn);
        }
        else if(thiz->playload_type == BIND_AUDIO_INPUT)
        {
            HI_MPI_AO_UnBindAi(thiz->ao_dev_id, thiz->ao_channel, thiz->ai_dev_id, thiz->bind_audio_input_chn);
        }
        
        HI_MPI_AO_DisableChn(thiz->ao_dev_id, thiz->ao_channel);
        HI_MPI_AO_Disable(thiz->ao_dev_id);

        COMM_ZFREE(thiz, sizeof(AudioOutputDevice));
        
    }
    
    return ;
}

 
