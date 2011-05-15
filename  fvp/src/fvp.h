/*
 * File: fvp.h
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

#ifndef FVP_H
#define FVP_H


#ifdef __cplusplus
extern "C"{
#endif

#include"mpp_common.h"
#include"fvp_common.h"
#include"access.h"
#include"access_file.h"
#include"access_avi.h"
#include"access_factory.h"
#include"mpp_system.h"
#include"media_player.h"
#include"fvp_msg.h"
#include<stdbool.h>

	

typedef struct  _FvpInitPara
{
	int video_channel_nums;	/*0, 4, 8, 16, 32*/
	VO_INTF_SYNC_E hd_dev_resolution;	
	VO_INTF_SYNC_E ad_dev_resolution;
	VO_INTF_SYNC_E sd_dev_resolution;
	
}FvpConfigPara;

int fvp_init(FvpConfigPara *config_para);

void fvp_deinit(void);




#ifdef __cplusplus
}
#endif


#endif /*FVP_H*/

