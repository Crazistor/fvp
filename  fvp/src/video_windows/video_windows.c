/*
 * File: video_widnows.c
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
 * Thu Apr 14 17:12:15 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */


#include<math.h>


#include"fvp_common.h"
#include"video_windows.h"


typedef struct _WindowsPictureInfo
{
	int x;
	int y;
	int pic_width;
	int pic_height;

	VoPictureBindType vo_bind_type;
	int bind_dec_channel_id;
	
	int video_input_dev;
	int video_input_dev_channel;

	
}WindowsPictureInfo;


struct _VideoWindows
{
	int windows_width;
	int windows_height;
	int display_rate;
	
	VO_DEV vo_dev;
	VO_INTF_SYNC_E vo_system_sync;

	int ref;

	int cur_pic_numbers;					/*current display picture numbers*/
	WindowsPictureInfo pictures[VO_MAX_CHN_NUM];		
};



static void video_windows_destroy(VideoWindows *thiz)
{
	if(thiz)
	{	
		msg_dbg("fun[%s]\n", __func__);

		VO_CHN vo_channel= 0;
		HI_S32 ret = 0;
		for(vo_channel; vo_channel < thiz->cur_pic_numbers;vo_channel++)
		{
			ret = HI_MPI_VO_DisableChn(thiz->vo_dev, vo_channel);
			if (HI_SUCCESS != ret)
			{
				msg_dbg("HI_MPI_VO_DisableChn(%d, %d) fail, err code: 0x%08x.\n",
					thiz->vo_dev, vo_channel, ret);
				return;
			}
		}
		ret = HI_MPI_VO_DisableVideoLayer(thiz->vo_dev);
		if (HI_SUCCESS != ret)
		{
			msg_dbg("HI_MPI_VO_DisableVideoLayer(%d) fail, err code: 0x%08x.\n",
				thiz->vo_dev, ret);
			return;
		}
		ret = HI_MPI_VO_Disable(thiz->vo_dev);
		if(HI_SUCCESS != ret)
		{
			msg_dbg("HI_MPI_VO_DisableVideoLayer(%d) fail, err code: 0x%08x.\n",
				thiz->vo_dev, ret);
			return;
		}
		
	}

	return;		
}




static int get_width_height_by_resolution(VO_INTF_SYNC_E vo_system_sync, int *width, int *height,int *rate)
{
	return_val_if_failed(vo_system_sync < VO_OUTPUT_BUTT, -1);

	switch(vo_system_sync)
	{	
		case VO_OUTPUT_PAL:
			*width = 720;
			*height = 576;
			*rate = 25;
			break;
		case VO_OUTPUT_NTSC:
			*width = 720;
			*height = 480;
			*rate = 30;
			break;
		case VO_OUTPUT_720P60:
			*width = 1280;
			*height = 720;
			*rate = 60;
			break;
		case VO_OUTPUT_1080I50:
			*width = 1920;
			*height = 1080;
			*rate = 50;
			break;
		case VO_OUTPUT_1080I60:
			*width = 1920;
			*height = 1080;
			*rate = 60;
			break;
		case VO_OUTPUT_1080P25:
			*width = 1920;
			*height = 1080;
			*rate = 25;
			break;
		case VO_OUTPUT_1080P30:
			*width = 1920;
			*height = 1080;
			*rate = 30;
			break;
		case VO_OUTPUT_800x600_60:
			*width = 800;
			*height = 600;
			*rate = 60;
			break;
		case VO_OUTPUT_1024x768_60:
			*width = 1024;
			*height = 768;
			*rate = 60;
			break;
		case VO_OUTPUT_1280x1024_60:
			*width = 1280;
			*height = 1024;
			*rate = 60;
			break;
		case VO_OUTPUT_1366x768_60:
			*width = 1366;
			*height = 768;
			*rate = 60;
			break;
		case VO_OUTPUT_1440x900_60:
			*width = 1440;
			*height = 900;
			break;
		case VO_OUTPUT_800x600_75:
			*width = 800;
			*height = 600;
			*rate = 75;
			break;
		case VO_OUTPUT_1024x768_75:
			*width = 1024;
			*height = 768;
			*rate = 75;
			break;
		default:
			msg_dbg("Not support this vo_system_sync\n");
			break;
	}

	return 0;
}

static int get_display_rate(VO_DEV vo_dev, VO_INTF_SYNC_E vo_system_sync)
{
	return_val_if_failed(vo_dev <VO_DEV_BUTT && vo_system_sync < VO_OUTPUT_BUTT, -1);

	int display_rate = -1;

	switch(vo_dev)
	{
        case VO_DEV_HD:
        case VO_DEV_AD:
			display_rate = 60;
		case VO_DEV_SD:
			display_rate = (vo_system_sync == VO_OUTPUT_PAL)?25:30;
	        break;
	}

	return display_rate;
}


static void get_video_output_dev_attr(VO_DEV vo_dev, VO_PUB_ATTR_S *stVoDevAttr)
{
	if(stVoDevAttr)
	{
	    switch (vo_dev)
	    {
	        case VO_DEV_HD:
	            stVoDevAttr->enIntfType = VO_INTF_VGA;
	            stVoDevAttr->enIntfSync = VO_OUTPUT_800x600_60;
	            stVoDevAttr->u32BgColor = VO_BKGRD_BLACK;
	            break;
	        case VO_DEV_AD:
	            stVoDevAttr->enIntfType = VO_INTF_VGA;
	            stVoDevAttr->enIntfSync = VO_OUTPUT_800x600_60;
	            stVoDevAttr->u32BgColor = VO_BKGRD_BLACK;
	            break;
	        case VO_DEV_SD:
	            stVoDevAttr->enIntfType = VO_INTF_CVBS;
	            stVoDevAttr->enIntfSync = VO_OUTPUT_PAL;
	            stVoDevAttr->u32BgColor = VO_BKGRD_BLACK;
	            break;
	        default:
	            return;
	    }

	}
	
	return;
}



static void get_video_output_layer_attr(VO_VIDEO_LAYER_ATTR_S *VideoLayerAttr, int width, int height, int diplay_rate)
{
    if(VideoLayerAttr)
    {
	    VideoLayerAttr->stDispRect.s32X = 0;
	    VideoLayerAttr->stDispRect.s32Y = 0;
	    VideoLayerAttr->stDispRect.u32Width   = width;
	    VideoLayerAttr->stDispRect.u32Height  = height;
	    VideoLayerAttr->stImageSize.u32Width  = width;
	    VideoLayerAttr->stImageSize.u32Height = height;
	    VideoLayerAttr->u32DispFrmRt = diplay_rate;
	    VideoLayerAttr->enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	    VideoLayerAttr->s32PiPChn = VO_DEFAULT_CHN;	    
    }
    
    return;
}

static int init_video_output_videolayer(VideoWindows *thiz)
{
	return_val_if_failed(thiz != NULL, -1);
	
    HI_S32 ret;
	VO_VIDEO_LAYER_ATTR_S videolayer_attr;

    ret = HI_MPI_VO_GetVideoLayerAttr(thiz->vo_dev,&videolayer_attr);
    if(ret != HI_SUCCESS)
    {
        msg_dbg("HI_MPI_VO_GetVideoLayerAttr err %d\n",ret);
        return ret;
    }

	get_video_output_layer_attr(&videolayer_attr, thiz->windows_width, thiz->windows_height, thiz->display_rate);

    /* set public attr of VO*/
    ret = HI_MPI_VO_SetVideoLayerAttr(thiz->vo_dev, &videolayer_attr);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("set video layer of dev %u failed %#x!\n", thiz->vo_dev, ret);
        return -1;
    }

    /* enable VO device*/
    ret = HI_MPI_VO_EnableVideoLayer(thiz->vo_dev);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("enable video layer of dev %d failed with %#x !\n", thiz->vo_dev, ret);
        return -1;
    }

    return 0;

}

static int init_video_output_device(VideoWindows *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

    HI_S32 ret;
    VO_PUB_ATTR_S stVoDevAttr;
    VO_DEV vo_dev = thiz->vo_dev;
    
	ret = HI_MPI_VO_Disable(vo_dev);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("HI_MPI_VO_Disable fail 0x%08x.\n", ret);
        return -1;
    }

	get_video_output_dev_attr(vo_dev, &stVoDevAttr);
	
    ret = HI_MPI_VO_SetPubAttr(vo_dev, &stVoDevAttr);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("HI_MPI_VO_SetPubAttr fail 0x%08x.\n", ret);
        return -1;
    }
    
    ret = HI_MPI_VO_Enable(vo_dev);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("HI_MPI_VO_Enable fail 0x%08x.\n", ret);
        return -1;
    }
	
	return 0;
}



static HI_S32 SAMPLE_SetVoChnMScreen(VO_DEV VoDev, HI_U32 u32ChnCnt, HI_U32 u32Width, HI_U32 u32Height)
{
    HI_U32 i, div, w, h, ret;
    VO_CHN_ATTR_S stChnAttr;

    /* If display 32 vo channels, should use 36-screen split. */
    u32ChnCnt = (u32ChnCnt == VO_MAX_CHN_NUM) ? 36 : u32ChnCnt;

    div = sqrt(u32ChnCnt);
    w = (u32Width / div);
    h = (u32Height / div);

    for (i = 0; i < u32ChnCnt; i++)
    {
        if (i >= VO_MAX_CHN_NUM)
        {
            break;
        }

        stChnAttr.u32Priority = 0;
        stChnAttr.bZoomEnable = HI_TRUE;
        stChnAttr.bDeflicker  = (((1==u32ChnCnt) || (VoDev == 0)) ? HI_FALSE : HI_TRUE);
        stChnAttr.stRect.s32X = w * (i % div);
        stChnAttr.stRect.s32Y = h * (i / div);
        stChnAttr.stRect.u32Width  = w;
        stChnAttr.stRect.u32Height = h;

        if (stChnAttr.stRect.s32X % 2 != 0)
        {
            stChnAttr.stRect.s32X++;
        }

        if (stChnAttr.stRect.s32Y % 2 != 0)
        {
            stChnAttr.stRect.s32Y++;
        }

        if (stChnAttr.stRect.u32Width % 2 != 0)
        {
            stChnAttr.stRect.u32Width++;
        }

        if (stChnAttr.stRect.u32Height % 2 != 0)
        {
            stChnAttr.stRect.u32Height++;
        }

        ret = HI_MPI_VO_SetChnAttr(VoDev, i, &stChnAttr);
        if (ret != HI_SUCCESS)
        {
            printf("In %s set channel %d attr failed with %#x!\n", __FUNCTION__, i, ret);
            return ret;
        }
    }

    return HI_SUCCESS;
}


static int enable_vo_channel(VO_DEV vo_dev, int vo_channel_numbers)
{
	int vo_chn = 0;
	HI_U32 ret;

	for(vo_chn = 0; vo_chn < vo_channel_numbers; vo_chn++)
	{
		ret = HI_MPI_VO_EnableChn(vo_dev, vo_chn);
        if (HI_SUCCESS != ret)
        {
            printf("HI_MPI_VO_EnableChn(%d, %d) failed, err code:0x%08x\n\n", vo_dev, vo_channel_numbers, ret);
            return -1;
        }
	}
	
	return 0;
}



VideoWindows *video_windows_create(VO_DEV_E video_dev, VO_INTF_SYNC_E vo_system_sync, int max_chn_numbers)
{	
	VideoWindows *thiz = (VideoWindows *)(COMM_ZALLOC(sizeof(VideoWindows)));
	
	if(thiz == NULL)
	{
		msg_dbg("fun(%s)  not enough memory!\n", __func__);
		return NULL;
	}

	thiz->vo_dev = video_dev;
	thiz->vo_system_sync = vo_system_sync;
	thiz->cur_pic_numbers = max_chn_numbers;
	thiz->display_rate = 30;

	get_width_height_by_resolution(vo_system_sync, &thiz->windows_width, &thiz->windows_height, &thiz->display_rate);
	
	init_video_output_device(thiz);
	init_video_output_videolayer(thiz);
	
	SAMPLE_SetVoChnMScreen(video_dev, max_chn_numbers, thiz->windows_width, thiz->windows_height);
	
	enable_vo_channel(video_dev, max_chn_numbers);

	thiz->ref = 1;

	return thiz;
}



int video_windows_set_display_mode(VideoWindows *thiz, VideoPictureMode picture_mode)
{
	return_val_if_failed(thiz != NULL , -1);

	return 0;
}


int video_windows_picture_bind_decode_chn(VideoWindows *thiz, int vo_picture_id, int decode_chn_id)
{
	if(thiz == NULL)
	{
		printf("video_windows_picture_bind_decode_chn thiz == NULL\n");
	}
	return_val_if_failed(thiz != NULL && vo_picture_id < VO_MAX_CHN_NUM, -1);


	if(vo_picture_id > thiz->cur_pic_numbers)
	{
		msg_dbg("Fun(%s) : video windows just have (%d) pictures, not support bind this vo picture(%d)", \
			__func__, thiz->cur_pic_numbers, vo_picture_id);
		return -1;
	}

	int ret = HI_FAILURE;
	VO_DEV vo_dev = thiz->vo_dev;
	
	ret = HI_MPI_VDEC_BindOutput(decode_chn_id, vo_dev, vo_picture_id);
	if(ret != HI_SUCCESS)
	{
		msg_dbg("Bind the vdec output failed %#x\n", ret);
		return -1;
	}

	return 0;
}


int video_windows_picture_bind_video_input_chn(VideoWindows *thiz)
{

	return_val_if_failed(thiz != NULL , -1);

	msg_dbg("fun[%s]\n", __func__);

	return 0;
}



int video_windows_pause_vo_channel(VideoWindows *thiz, int vo_channel)
{
#if 1
	msg_dbg("video_windows_pause_vo_channel\n");
	return_val_if_failed(thiz != NULL, -1);

	if(vo_channel > thiz->cur_pic_numbers)
	{
		msg_dbg("fun(%s) error: vo_channel > thiz->cur_pic_numbers \n", __func__);
		return -1;
	}
	
	if(thiz->pictures[vo_channel].vo_bind_type != BIND_DECODER_CHANNEL)
	{
		msg_dbg("fun(%s) erro :thiz->pictures[vo_channel].vo_bind_type != BIND_DECODER_CHANNEL!\n", __func__);
		return -1;
	}
	
	HI_MPI_VO_ChnPause(thiz->vo_dev, vo_channel);
#endif 
	return 0;
}


int video_windows_resume_vo_channel(VideoWindows *thiz, int vo_channel)
{
#if 1
	msg_dbg("video_windows_resume_vo_channel\n");

	return_val_if_failed(thiz != NULL, -1);

	if(vo_channel > thiz->cur_pic_numbers)
	{
		msg_dbg("fun(%s) error: vo_channel > thiz->cur_pic_numbers \n", __func__);
		return -1;
	}
	
	if(thiz->pictures[vo_channel].vo_bind_type != BIND_DECODER_CHANNEL)
	{
		msg_dbg("fun(%s) erro :thiz->pictures[vo_channel].vo_bind_type != BIND_DECODER_CHANNEL!\n", __func__);
		return -1;
	}
	
	HI_MPI_VO_ChnResume(thiz->vo_dev, vo_channel);
#endif 
	
	return 0;
}



void video_windows_ref(VideoWindows *thiz)
{
	if(thiz != NULL)
	{
		thiz->ref++;
	}
	
	return;	
}


void video_windows_unref(VideoWindows *thiz)
{
	if(thiz)
	{
		thiz->ref--;
		if(thiz->ref == 0)
		{
			video_windows_destroy(thiz);
		}
	}
	
	return 0;
}

