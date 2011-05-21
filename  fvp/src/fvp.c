/*
 * File: fvp.c
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
 * 2011-5-13 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"fvp.h"


static int   fvp_ad_codec_init()
{   
    msg_dbg("Fun[%s]\n", __func__);

    ADCodec *ad_codec = ad_codec_create();
    fvp_set_ad_codec(ad_codec);
    
    return 0;
}

static int  fvp_audio_output_device_init(AUDIO_DEV ao_output_dev_id)
{    
    msg_dbg("Fun[%s]\n", __func__);
    
    AudioOutputDevice *audio_output_device = audio_output_device_create(ao_output_dev_id, 0);
    
    fvp_set_audio_output_device(audio_output_device);   

    return 0;
}

static int fvp_windows_init(FvpConfigPara *config_para)
{
	msg_dbg("fvp_windows_init\n");

//	VideoWindows *hd_windows = video_windows_create(VO_DEV_HD,	config_para->hd_dev_resolution, 1);
//	fvp_set_hd_windows(hd_windows);

//	VideoWindows *ad_windows = video_windows_create(VO_DEV_AD,	config_para->ad_dev_resolution, 1);	
//	fvp_set_ad_windows(ad_windows);
	
	VideoWindows *sd_windows = video_windows_create(VO_DEV_SD,	config_para->sd_dev_resolution, 1);	
	fvp_set_sd_windows(sd_windows);	

	return 0;
}

static int osd_layer_init()
{

	char str[32] = {0};
	int i = 0;
	int FrameBufferFd = -1;
	HI_BOOL bShow = HI_FALSE;
	
    for(i = 0; i < VO_DEV_BUTT; i++)
    {
            sprintf(str,"/dev/fb%d", i);    
        
		FrameBufferFd = open(str, O_RDWR, 0);
		if(FrameBufferFd < 0)
		{
			printf("open framebuffer device failed(%s)\n", str);
			return -1;
		}

		if (ioctl(FrameBufferFd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
		{
			printf("InitOsd FBIOPUT_VSCREENINFO failed\n");
			close(FrameBufferFd);
			return  -1;
		}
		close(FrameBufferFd);
		FrameBufferFd = -1;
    }

    return 0;	
}
 
int fvp_init(FvpConfigPara *config_para)
{
    osd_layer_init();

    mpp_system_init();
    
    fvp_windows_init(config_para);
    
    fvp_audio_output_device_init(config_para->audio_output_dev);
    
    fvp_ad_codec_init();
        
   
    return 0;
}



void fvp_deinit(void)
{
	
    if(fvp_default_hd_windows() != NULL)
    {
    	video_windows_unref(fvp_default_hd_windows());
    }

    if(fvp_default_ad_windows() != NULL)
    {
    	video_windows_unref(fvp_default_ad_windows());
    }

    if(fvp_default_sd_windows() != NULL)
    {
    	video_windows_unref(fvp_default_sd_windows());
    }

    if(fvp_default_audio_output_device() != NULL)
    {
        audio_output_device_destroy(fvp_default_audio_output_device());
    }

    if(fvp_default_ad_codec() != NULL)
    {
        ad_codec_destroy(fvp_default_ad_codec());
    }
    
    mpp_system_deinit();

    return;
}


