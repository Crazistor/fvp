/*
 * File: fvp_screen.c
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
 * 2011-02-28 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"fvp_screen.h"

struct _FvpScreen
{	
	VideoResolution resolution;
	int screen_width;
	int screen_height;
};


static int fvp_screen_calc_width_height(FvpScreen *fvp_screen, VideoResolution resolution)
{
	return_val_if_failed(fvp_screen != NULL && resolution < VR_BUTT, RET_INVALID_PARAMETER);

	switch(resolution)
	{	
		case VR_PAL:
			fvp_screen->screen_width = 720;
			fvp_screen->screen_height = 576;
			break;
		case VR_NTSC:
			fvp_screen->screen_width = 720;
			fvp_screen->screen_height = 480;
			break;
		case VR_800x600:
			fvp_screen->screen_width = 720;
			fvp_screen->screen_height = 480;
			break;
		case VR_1024x768:
			fvp_screen->screen_width = 1024;
			fvp_screen->screen_height = 768;
			break;
		case VR_1366x768:
			fvp_screen->screen_width = 1366;
			fvp_screen->screen_height = 768;
			break;
		case VR_1440x900:
			fvp_screen->screen_width = 1440;
			fvp_screen->screen_height = 900;
			break;
		case VR_1440x990:
			fvp_screen->screen_width = 1440;
			fvp_screen->screen_height = 990;
			break;
		case VR_720P:
			fvp_screen->screen_width = 1280;
			fvp_screen->screen_height = 720;
			break;
		case VR_1080P:
			fvp_screen->screen_width = 1920;
			fvp_screen->screen_height = 1080;
			break;
		default:
			break;
	}

	return RET_OK;
}

FvpScreen *fvp_screen_create(VideoResolution resolution)
{
	return_val_if_failed(resolution < VR_BUTT, NULL);
	
	FvpScreen *thiz = NULL;	
	thiz  = (FvpScreen *)COMM_ZALLOC(sizeof(FvpScreen));

	fvp_screen_calc_width_height(thiz, resolution);

	return thiz;
}

int fvp_screen_chanege_resolution(FvpScreen *thiz, VideoResolution resolution)
{
	return fvp_screen_calc_width_height(thiz, resolution);
}

int fvp_screen_get_width(FvpScreen *thiz)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	return thiz->screen_width;
}


int fvp_screen_get_height(FvpScreen *thiz)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	return thiz->screen_height;
}


void fvp_screen_destroy(FvpScreen *thiz)
{
	if(thiz)
	{
		COMM_FREE(thiz);	
	}

	return;
}

