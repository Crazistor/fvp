/*
 * File: video_widnows.h
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
 * but WI_HOUT ANY WARRANTY; without even the implied warranty of
 * MER_HANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *_History:
 * ================================================================
 * Thu Apr 14 17:12:09 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */




#ifndef VIDEO_WINDOWS_H
#define VIDEO_WINDOWS_H

#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "hi_comm_vo.h"
#include "hi_comm_vi.h"
#include "hi_comm_vpp.h"
#include "hi_comm_venc.h"
#include "hi_comm_vdec.h"
#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_vi.h"
#include "mpi_vo.h"
#include "mpi_vpp.h"
#include "mpi_venc.h"
#include "mpi_vdec.h"
#include "fvp_msg.h"
#include "mpp_common.h"


#ifdef __cplusplus
extern "C"{
#endif

typedef enum _VideoPictureMode
{
	ONE_PIC,
	FOUR_PIC,
	NINE_PIC,
	SIXTEEN_PIC,
}VideoPictureMode;


struct _VideoWindows;
typedef struct _VideoWinodws VideoWindows;

/*creat a video windows 
 *input para video_dev    --- [VO_DEV_HD ; VO_DEV_AD; VO_DEV_SD]
*/
VideoWindows *video_windows_create(VO_DEV video_dev, VO_INTF_SYNC_E vo_system_sync);


void video_windows_set_display_mode(VideoWindows *thiz, VideoPictrureMode picture_mode);

/*
 *destroy the video windows
 */
void video_windows_destroy(VideoWindows *thiz);


#ifdef __cplusplus
}
#endif

#endif /*VIDEO_WINDOWS_H*/



