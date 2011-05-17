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
 
struct _AudioOutputDevice
{	
	AUDIO_DEV ao_dev_id;
	int ao_channel;
	PAYLOAD_TYPE_E playload_type;
}



static int get_ao_dev_attr(PAYLOAD_TYPE_E playload_type, AIO_ATTR_S *aio_aattr)
{
	return_val_if_failed(aio_aattr, -1);

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



AudioOutputDevice *audio_output_device_create(AUDIO_DEV ao_dev_id,
														int ao_channel, 
														PAYLOAD_TYPE_E playload_type)
{
	AudioOutputDevice *thiz = NULL;
	
	thiz = (AudioOutputDevice *)COMM_ALLOC(sizeof(AudioOutputDevice));
	if(thiz == NULL)
	{
		msg_dbg("Fun[%s] error : not enough memory!\n", __func__);
		return NULL;
	}


	thiz->ao_dev_id = ao_dev_id;
	thiz->ao_channel = ao_channel;
	thiz->playload_type = playload_type;

	AIO_ATTR_S aio_aattr;
	
	get_ao_dev_attr(playload_type, &aio_aattr);


	HI_S32 s32ret;
	
    s32ret = HI_MPI_AO_SetPubAttr(thiz->ao_dev_id, &aio_aattr);
    if(HI_SUCCESS != s32ret)
    {
        printf("set ao %d attr err:0x%x\n", thiz->ao_dev_id,s32ret);
        return NULL;
    }
	
    s32ret = HI_MPI_AO_Enable(thiz->ao_dev_id);
    if(HI_SUCCESS != s32ret)
    {
        printf("enable ao dev %d err:0x%x\n", thiz->ao_dev_id, s32ret);
        return NULL;
    }
    s32ret = HI_MPI_AO_EnableChn(thiz->ao_dev_id, thiz->ao_channel);
    if(HI_SUCCESS != s32ret)
    {
        printf("enable ao chn %d err:0x%x\n", thiz->ao_channel, s32ret);
        return NULL;
    }
	
	return thiz;
}


void audio_output_device_destroy(AudioOutputDevice *thiz)
{
	if(thiz)
	{

	}
	
	return ;
}




 
