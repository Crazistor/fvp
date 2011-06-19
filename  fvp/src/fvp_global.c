/*
 * File: fvp_global.c
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

#include"fvp_global.h"
 
struct _FvpGlobals
{
    VideoWindows *hd_windows;		
    VideoWindows *ad_windows;		
    VideoWindows *sd_windows;
    
    AudioOutputDevice *audio_output_device;
    
    ADCodec *ad_codec;
    
}g_globals;



VideoWindows *fvp_default_hd_windows(void)
{
    return g_globals.hd_windows;
}

VideoWindows *fvp_default_ad_windows(void)
{
    return g_globals.ad_windows;
}

VideoWindows *fvp_default_sd_windows(void)
{
    return g_globals.sd_windows;
}

AudioOutputDevice *fvp_default_audio_output_device(void)
{
    return g_globals.audio_output_device;
}

ADCodec *fvp_default_ad_codec(void)
{
    return g_globals.ad_codec;
}


void fvp_set_hd_windows(VideoWindows *hd_windows)
{
    g_globals.hd_windows = hd_windows;

    return;
}

void fvp_set_ad_windows(VideoWindows *ad_windows)
{
    g_globals.ad_windows = ad_windows;

    return;
}

void fvp_set_sd_windows(VideoWindows *sd_windows)
{
    g_globals.sd_windows = sd_windows;

    return;
}

void fvp_set_audio_output_device(AudioOutputDevice *audio_output_device)
{
    g_globals.audio_output_device = audio_output_device;
    
    return;
}

void fvp_set_ad_codec(ADCodec *ad_codec)
{
    g_globals.ad_codec = ad_codec;

    return;
}

