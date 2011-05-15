/*
 * File: mpp_media_test.c
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
 * Thu Apr 21 16:40:25 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */




#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include"fvp.h"


FvpConfigPara g_config_para = {.video_channel_nums = 4, 
							.hd_dev_resolution = VO_OUTPUT_PAL,
							.ad_dev_resolution = VO_OUTPUT_PAL,
							.sd_dev_resolution = VO_OUTPUT_PAL,
		};



void usage()
{
	printf("usage: ./mpp_media_test   filename(h.264 avi)\n");
}

int main(int argc, char *argv[])
{
	if(argc < 2 )
	{
		usage();
		return -1;
	}

	
	fvp_init(&g_config_para);
	
//	VideoWindows *windows = video_windows_create(VO_DEV_SD, VO_OUTPUT_PAL, 1);

	int vdec_chn= 0;
	RECT_S out_rect = {	.s32X = 0,
						.s32Y = 0,
						.u32Width = 720,
						.u32Height = 576
					  };
	MediaPlayer *player = NULL;
	char access_path[128] = {0};
	
	sprintf(access_path, "file:%s", argv[1]);
	player = media_player_create(vdec_chn, out_rect, access_path, fvp_default_sd_windows(), 0);
	video_windows_picture_bind_decode_chn(fvp_default_sd_windows(), 0, vdec_chn);

//	video_windows_picture_bind_decode_chn(windows, 1, vdec_chn);
//	video_windows_picture_bind_decode_chn(windows, 2, vdec_chn);
	
	media_player_play(player);

	char p;
	while(1)
	{
		printf("q ------- quit\n"
			   "a ------- play\n"
		       "p ------- pause\n");

		p = getchar();
		
		if(p == 'q')
		{
			break;
		}
		else if(p == 'p')
		{
			media_player_pause(player);
		}
		else if(p == 'a')
		{
			media_player_play(player);
		}
	}

	media_player_destroy(player);
	fvp_deinit();

	return 0;
}


