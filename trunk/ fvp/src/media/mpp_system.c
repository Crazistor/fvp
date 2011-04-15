/*
 * File: mpp_system.c
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
 * Thu Apr 14 11:22:50 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */
 

#include"mpp_system.h"


int mpp_system_init()
{
	HI_S32 s32Ret;
	MPP_SYS_CONF_S stSysConf = {0};
	VB_CONF_S stVbConf ={0};
	
	static int mpp_inited = 0;

	if(mpp_inited == 1)
	{
		msg_dbg("Mpp system have inited!\n");
		return 0;
	}

	HI_MPI_SYS_Exit();
	HI_MPI_VB_Exit();
	stVbConf.u32MaxPoolCnt = 32;
	s32Ret = HI_MPI_VB_SetConf(&stVbConf);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MPI_VB_SetConf failed 0x%x!\n",s32Ret);
		return -1;
	}

	s32Ret = HI_MPI_VB_Init();
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MPI_VB_Init failed 0x%x!\n",s32Ret);
		return -1;
	}

	stSysConf.u32AlignWidth = 64;

	s32Ret = HI_MPI_SYS_SetConf(&stSysConf);
	if (HI_SUCCESS != s32Ret)
	{
		HI_MPI_VB_Exit();
		printf("conf : system config failed 0x%x!\n",s32Ret);
		return -1;
	}

	s32Ret = HI_MPI_SYS_Init();
	if(HI_SUCCESS != s32Ret)
	{
		HI_MPI_VB_Exit();
		printf("HI_MPI_SYS_Init err 0x%x\n",s32Ret);
		return -1;
	}

	mpp_inited = 1;
	
	return 0;
}


int mpp_system_deinit()
{
    if (HI_MPI_SYS_Exit())
    {
        printf("sys exit fail\n");
        return -1;
    }

    if (HI_MPI_VB_Exit())
    {
        printf("vb exit fail\n");
        return -1;
    }

    return 0;
}


