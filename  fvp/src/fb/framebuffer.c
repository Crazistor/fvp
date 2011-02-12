/*
 * File: framebuffer.c
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
 * 2011-01-20 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/types.h>
#include <string.h>
#include <unistd.h>
#include"framebuffer.h"
#include"fvp_common.h"
#include"hifb.h"

struct _FrameBuffer
{
	char *framebuffer_name;
	int framebuffer_fd;
	int framebuffer_w;
	int framebuffer_h;
	unsigned char *screen_mmap_buf;
	int color_key;
	int applah_value;
};


static struct fb_bitfield g_r16 = {10, 5, 0};
static struct fb_bitfield g_g16 = {5, 5, 0};
static struct fb_bitfield g_b16 = {0, 5, 0};
static struct fb_bitfield g_a16 = {15, 1, 0};

#define COLOR_VALUE(a, r, g, b) (((a > 0)?0x8000:0) | (((r >> 3) & 0x1f) << 10) | (((g >> 3) & 0x1f) << 5) | ((b >> 3) & 0x1f))

#define FB_NOT_DISPLAY_COLOR COLOR_VALUE(0, 0xff, 0, 0)
#define DEFAULT_ALPHA_VALUE 0xcf

static int framebuffer_fd_set_alpha(int fd, unsigned char alpha)
{
	return_val_if_failed(fd >= 0, RET_INVALID_PARAMETER);
	
    HIFB_ALPHA_S stAlpha;
	int ret = RET_OK;
    
    stAlpha.bAlphaEnable = HI_TRUE;
    stAlpha.bAlphaChannel = HI_FALSE;
    stAlpha.u8Alpha0 = alpha;  /*0xff为不透明，0x00为透明*/
    stAlpha.u8Alpha1 = 0xff;
    stAlpha.u8GlobalAlpha = 0xff;
    if (ioctl(fd, FBIOPUT_ALPHA_HIFB, &stAlpha) < 0)
    {
		ret = RET_FAILED;
    }
    
    return ret;	

}

static int framebuffer_set_not_display_color(int fd, color_t not_display_color)
{
	return_val_if_failed(fd >= 0, RET_INVALID_PARAMETER);	

	HIFB_COLORKEY_S color_key;
	
	color_key.bKeyEnable = HI_TRUE;
	color_key.u32Key = not_display_color;
	color_key.bMaskEnable = HI_FALSE;
	color_key.u8BlueMask = 255;
	color_key.u8RedMask = 255;
	color_key.u8GreenMask = 255;
	if (ioctl(fd, FBIOPUT_COLORKEY_HIFB, &color_key) < 0)
	{
		return RET_FAILED;
	}
	
	return RET_OK;

}

FrameBuffer *framebuffer_create(char *fb_name)
{
	return_val_if_failed(fb_name != NULL, NULL);
	FrameBuffer *thiz = NULL;		

	thiz=(FrameBuffer *)COMM_ZALLOC(sizeof(FrameBuffer));
	thiz->framebuffer_name = COMM_ZALLOC(strlen(fb_name) + 1);
	memcpy(thiz->framebuffer_name, fb_name, strlen(fb_name));
	
	return thiz;
}

int framebuffer_init(FrameBuffer *thiz, int fb_w, int fb_h)
{
	return_val_if_failed(thiz != NULL && fb_w > 0 && fb_h > 0, RET_INVALID_PARAMETER);

	int ret = RET_FAILED;
	/*get framebuffer w and h */
	thiz->framebuffer_w = fb_w;
	thiz->framebuffer_h = fb_h;

	/*open the  framebuffer fd*/
	int fd = -1;
	
	fd = open(thiz->framebuffer_name, O_RDWR, 0);
	if(fd < 0)
	{
		printf("fun(%s):Open the framebuffer(%s) failed\n", __func__, thiz->framebuffer_name);
		goto OUT;
	}

    struct fb_var_screeninfo default_vinfo= {0};
    if (ioctl(fd, FBIOGET_VSCREENINFO, &default_vinfo) < 0)
    {
		printf("fun(%s):Get variable screen info failed\n", __func__);
		goto OUT;
    }
    
    default_vinfo.bits_per_pixel = sizeof(color_t) * 8;

    default_vinfo.transp= g_a16;
    default_vinfo.red = g_r16;
    default_vinfo.green = g_g16;
    default_vinfo.blue = g_b16;
    default_vinfo.bits_per_pixel = sizeof(color_t) * 8;
    default_vinfo.activate = FB_ACTIVATE_FORCE;
    default_vinfo.xres = thiz->framebuffer_w;
    default_vinfo.yres = thiz->framebuffer_h;

    default_vinfo.xres_virtual = thiz->framebuffer_w;
    default_vinfo.yres_virtual = 768;

	printf("default_vinfo xres_virtual(%d) yres_virtual(%d)\n", default_vinfo.xres_virtual, default_vinfo.yres_virtual);
	/*set the fb FBIOPUT_VSCREENINFO*/
    if (ioctl(fd, FBIOPUT_VSCREENINFO, &default_vinfo) < 0)
    {
        printf("InitOsd FBIOPUT_VSCREENINFO failed\n");
        goto OUT;
    }
    
    struct fb_fix_screeninfo fix;
    if (ioctl(fd, FBIOGET_FSCREENINFO, &fix) < 0 )
    {
        printf("InitOsd FBIOPUT_VSCREENINFO failed\n");
        goto OUT;
    }
	unsigned int u32FixScreenStride = 0;
	u32FixScreenStride = fix.line_length;

    /* map the physical video memory for user use */
    thiz->screen_mmap_buf = mmap(NULL, fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(NULL == thiz->screen_mmap_buf)
    {
   	    printf("mmap framebuffer failed!\n");
        goto OUT;
    }
    
	/*set alpha value*/
	framebuffer_fd_set_alpha(fd, DEFAULT_ALPHA_VALUE);
	
	/*set the color key*/
	framebuffer_set_not_display_color(fd, FB_NOT_DISPLAY_COLOR);

	ret = RET_OK;
OUT:
	thiz->framebuffer_fd = fd;
	
	return ret;
}

/*
 * set the osd alpha value.0x00 max alpha value, 0xff min alpha value
 */
int framebuffer_set_alpha(FrameBuffer *thiz, unsigned char alpha)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);


	return framebuffer_fd_set_alpha(thiz->framebuffer_fd, alpha);
}


void framebuffer_destroy(FrameBuffer *thiz)
{
	if(thiz)
	{
		if(thiz->framebuffer_fd >= 0)
		{
			close(thiz->framebuffer_fd);
			thiz->framebuffer_fd = -1;
		}
	}
	return;
}

