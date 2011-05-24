/*
 * File: ad_codec.c
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

#include"ad_codec.h"
#include"tw2865.h"
#include"tw2865_def.h" 


struct _ADCodec
{
    int ad_fd;
    
};

#define DEFAULT_AD_DEV_FILENAME "/dev/tw2865dev"

ADCodec *ad_codec_create(void)
{   
    ADCodec *thiz = NULL;
    int fd = -1;

    fd = open(DEFAULT_AD_DEV_FILENAME, O_RDWR);
    if(fd < 0)
    {
        msg_dbg("Fun[%s] error :open ad file failed!\n", __func__);
        return NULL;
    }

    thiz = (ADCodec *)COMM_ALLOC(sizeof(ADCodec));
    thiz->ad_fd = fd;
    
    return thiz;   
}

int ad_codec_config_audio_rate(ADCodec *thiz, AUDIO_SAMPLE_RATE_E audio_sample_rate)
{
    return_val_if_failed(thiz != NULL && thiz->ad_fd >= 0, -1);
	
    tw2865_audio_samplerate samplerate;

    switch(audio_sample_rate)
    {
        case AUDIO_SAMPLE_RATE_8000:
            samplerate = TW2865_SAMPLE_RATE_8000;
            break;
         case AUDIO_SAMPLE_RATE_16000:
            samplerate = TW2865_SAMPLE_RATE_16000;
            break;
         case AUDIO_SAMPLE_RATE_32000:
            samplerate = TW2865_SAMPLE_RATE_32000;
            break;
         case AUDIO_SAMPLE_RATE_44100:
            samplerate = TW2865_SAMPLE_RATE_44100;
            break;
         case TW2865_SAMPLE_RATE_48000:
            samplerate = TW2865_SAMPLE_RATE_48000;
            break;
         default:
            msg_dbg("Error : Not support enSample:%d\n",audio_sample_rate);
            return -1;
            break;
    }

    if (ioctl(thiz->ad_fd, TW2865_SET_SAMPLE_RATE, &samplerate))
    {
        msg_dbg("ioctl TW2865_SET_SAMPLE_RATE err !!! \n");
        close(thiz->ad_fd);
        return -1;
    }
 
    return 0;    
}

void ad_codec_destroy(ADCodec *thiz)
{
    if(thiz)
    {
        if(thiz->ad_fd > 0)
        {
            close(thiz->ad_fd);
            thiz->ad_fd = -1;
        }
        COMM_ZFREE(thiz, sizeof(ADCodec));
    }

    return;
}



