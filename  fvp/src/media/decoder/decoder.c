/*
 * File: decoder.c
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
 * Fri Apr  8 14:03:05 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */


#include "decoder.h"
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

struct _Decoder
{
	int vde_chn_id;	
	int max_pic_width;
	int max_pic_height;

};

static int create_vdec_chn(Decoder *thiz, PAYLOAD_TYPE_E enType)
{	
	return_val_if_failed(thiz != NULL, -1);
	
	VDEC_CHN_ATTR_S 	stAttr;
	HI_S32 s32ret;
	VDEC_ATTR_H264_S stH264Attr;

	switch(enType)
	{
		case PT_H264:
		{
			stH264Attr.u32Priority = 0;
			stH264Attr.u32PicWidth = thiz->max_pic_width;
			stH264Attr.u32PicHeight = thiz->max_pic_height;
			stH264Attr.u32RefFrameNum = 2;	
			stH264Attr.enMode = H264D_MODE_FRAME;

			stAttr.enType = PT_H264;
			stAttr.u32BufSize = (((stH264Attr.u32PicWidth) * (stH264Attr.u32PicHeight))*1.5);
			stAttr.pValue = (void*)&stH264Attr;
			break;
		}
		default:
		{
			msg_dbg("PAYLOAD_TYPE_E error type \n");
			return -1;	  
		}
	}
//	s32ret = HI_MPI_VDEC_CreateChn(thiz->vde_chn_id, &stAttr, NULL);
	if (HI_SUCCESS != s32ret)
	{
		msg_dbg("HI_MPI_VDEC_CreateChn failed errno 0x%x \n", s32ret);
	}
	
	return s32ret != HI_SUCCESS? 0:-1;	
}

static int vdec_chn_bind_output_chn(Decoder *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	return 0;
}


Decoder *decoder_create(int vdec_chn, int max_pic_width, int max_pic_height)
{
	Decoder *thiz = NULL;

	thiz = (Decoder *)COMM_ZALLOC(sizeof(Decoder));
	
	thiz->vde_chn_id = vdec_chn;
	thiz->max_pic_width = max_pic_width;
	thiz->max_pic_height = max_pic_height;

	create_vdec_chn(thiz, PT_H264);

#if 0
    /*bind vdec to vo*/
    if (HI_SUCCESS != HI_MPI_VDEC_BindOutput(VdChn, VoDev, VoChn))
    {
        printf("HI_MPI_VDEC_BindOutput err\n");
        return HI_FAILURE;
#endif

	
	
	return thiz;
}

int decoder_decode_data(Decoder *thiz, Block *block)
{
	return_val_if_failed(thiz != NULL && block != NULL, -1);

	HI_S32 s32ret;
	
	VDEC_STREAM_S stStream;
	stStream.pu8Addr = NULL;
//	stStream.u32Len = size;
	stStream.u64PTS = 0;	
	
//	s32ret = HI_MPI_VDEC_SendStream(thiz->vde_chn_id, &stStream, HI_IO_NOBLOCK);
	if (HI_SUCCESS != s32ret)
	{
		msg_dbg("HI_MPI_VDEC_SendStream [%02d], errno 0x%x \n", thiz->vde_chn_id, s32ret);
	}

	
	return (s32ret == HI_SUCCESS)?0:-1;
}

int decoder_control(Decoder *thiz, int i_query, va_list args)
{
	return_val_if_failed(thiz != NULL, -1);
	
	msg_dbg("fun[%s]\n", __func__);
	
	return 0;
}


void decoder_destroy(Decoder *thiz)
{
	if(thiz)
	{
		msg_dbg("fun[%s]\n", __func__);
	}
	
	return;
}

