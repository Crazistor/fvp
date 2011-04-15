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



#inlcude"video_windows.h"



struct _VideoWindows
{
	int windows_width;
	int windows_height;
	int display_rate;
	VO_DEV video_device;
	VO_INTF_SYNC_E vo_system_sync;
	
};
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

static int get_display_rate(VO_DEV video_device, VO_INTF_SYNC_E vo_system_sync)
{
	return_val_if_failed(video_device <VO_DEV_BUTT && vo_system_sync < VO_OUTPUT_BUTT, -1);

	int display_rate = -1;

	switch(video_device)
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


static void get_video_output_dev_attr(VO_DEV video_device, VO_PUB_ATTR_S *stVoDevAttr)
{
	if(stVoDevAttr)
	{
	    switch (video_device)
	    {
	        case VO_DEV_HD:
	            stVoDevAttr.enIntfType = VO_INTF_VGA;
	            stVoDevAttr.enIntfSync = VO_OUTPUT_800x600_60;
	            stVoDevAttr.u32BgColor = VO_BKGRD_BLACK;
	            break;
	        case VO_DEV_AD:
	            stVoDevAttr.enIntfType = VO_INTF_VGA;
	            stVoDevAttr.enIntfSync = VO_OUTPUT_800x600_60;
	            stVoDevAttr.u32BgColor = VO_BKGRD_BLACK;
	            break;
	        case VO_DEV_SD:
	            stVoDevAttr.enIntfType = VO_INTF_CVBS;
	            stVoDevAttr.enIntfSync = VO_OUTPUT_PAL;
	            stVoDevAttr.u32BgColor = VO_BKGRD_BLACK;
	            break;
	        default:
	            return HI_FAILURE;
	    }

	}
	
	return;
}



static void get_video_output_layer_attr(VO_VIDEO_LAYER_ATTR_S *VideoLayerAttr, int width, int height, int diplay_rate)
{
    if(VideoLayerAttr)
    {
	    VideoLayerAttr.stDispRect.s32X = 0;
	    VideoLayerAttr.stDispRect.s32Y = 0;
	    VideoLayerAttr.stDispRect.u32Width   = width;
	    VideoLayerAttr.stDispRect.u32Height  = height;
	    VideoLayerAttr.stImageSize.u32Width  = width;
	    VideoLayerAttr.stImageSize.u32Height = height;
	    VideoLayerAttr.u32DispFrmRt = diplay_rate;
	    VideoLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	    VideoLayerAttr.s32PiPChn = VO_DEFAULT_CHN;	    
    }
    
    return;
}

static int init_video_output_device(VideoWindows *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

    HI_S32 ret;
    VO_PUB_ATTR_S stVoDevAttr;
    
	ret = HI_MPI_VO_Disable(thiz->video_device);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("HI_MPI_VO_Disable fail 0x%08x.\n", ret);
        return -1;
    }

	get_video_output_dev_attr(&stVoDevAttr);
	
    ret = HI_MPI_VO_SetPubAttr(thiz->video_device, &stVoDevAttr);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("HI_MPI_VO_SetPubAttr fail 0x%08x.\n", ret);
        return -1;
    }

    
    ret = HI_MPI_VO_Enable(thiz->video_device);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("HI_MPI_VO_Enable fail 0x%08x.\n", ret);
        return -1;
    }

	return 0;
}

static int init_video_output_layer(VideoWindows *thiz)
{
	return_val_if_failed(thiz != NULL, -1);
	
    HI_S32 ret;
	VO_VIDEO_LAYER_ATTR_S videolayer_attr;

	get_video_output_layer_attr(&videolayer_attr, thiz->windows_width, thiz->windows_height, thiz->display_rate);
    /* set public attr of VO*/
    ret = HI_MPI_VO_SetVideoLayerAttr(thiz->video_device, &videolayer_attr);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("set video layer of dev %u failed %#x!\n", thiz->video_device, ret);
        return -1;
    }

    /* enable VO device*/
    ret = HI_MPI_VO_EnableVideoLayer(thiz->video_device);
    if (HI_SUCCESS != ret)
    {
        msg_dbg("enable video layer of dev %d failed with %#x !\n", thiz->video_device, ret);
        return -1;
    }

    return 0;

}

VideoWindows *video_windows_create(VO_DEV video_dev, VO_INTF_SYNC_E vo_system_sync)
{	
	VideoWindows *thiz = (VideoWindows *)(COMM_ALLOC(sizeof(VideoWindows)));
	
	if(thiz == NULL)
	{
		msg_dbg("fun(%s)  not enough memory!\n", __func__);
		return NULL;
	}
	
	thiz->vo_system_sync = vo_system_sync;


	get_width_height_by_resolution(vo_system_sync, &thiz->windows_width, &thiz->windows_height, &thiz->display_rate);
	
	init_video_output_device(thiz);

	return thiz;
}


void video_windows_set_display_mode(VideoWindows *thiz, VideoPictrureMode picture_mode)
{
	return_val_if_failed(thiz != NULL , -1);
	


	return 0;
}


void video_windows_destroy(VideoWindows *thiz)
{
	

		
}



