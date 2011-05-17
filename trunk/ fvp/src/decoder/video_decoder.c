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


#include "video_decoder.h"
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
	VDEC_ATTR_JPEG_S stJpegAttr;

	switch(enType)
	{
		case PT_H264:
		{
			stH264Attr.u32Priority = 0;
			stH264Attr.u32PicWidth = thiz->max_pic_width;
			stH264Attr.u32PicHeight = thiz->max_pic_height;
			stH264Attr.u32RefFrameNum = 2;	
			stH264Attr.enMode = H264D_MODE_FRAME;
//			stH264Attr.enMode = H264D_MODE_STREAM;
			stAttr.enType = PT_H264;
			stAttr.u32BufSize = (((stH264Attr.u32PicWidth) * (stH264Attr.u32PicHeight)) << 1);
			stAttr.pValue = (void*)&stH264Attr;
			break;
		}
        case PT_JPEG:
        {
            stJpegAttr.u32Priority  = 0;
			stJpegAttr.u32PicWidth = thiz->max_pic_width;
			stJpegAttr.u32PicHeight = thiz->max_pic_height;
            stAttr.enType = PT_JPEG;
            stAttr.u32BufSize = ((stJpegAttr.u32PicWidth * stJpegAttr.u32PicHeight) << 1);
            stAttr.pValue = (void*)&stJpegAttr;
            break;
        }
		default:
		{
			msg_dbg("PAYLOAD_TYPE_E error type \n");
			return -1;	  
		}
	}
	s32ret = HI_MPI_VDEC_CreateChn(thiz->vde_chn_id, &stAttr, NULL);
	if (HI_SUCCESS != s32ret)
	{
		msg_dbg("HI_MPI_VDEC_CreateChn failed errno 0x%x \n", s32ret);
	}

    s32ret = HI_MPI_VDEC_StartRecvStream(thiz->vde_chn_id);
    if (s32ret != HI_SUCCESS)
    {
        msg_dbg("CreateVdecChannel HI_MPI_VDEC_StartRecvStream err 0x%x,chn %d\n", s32ret,thiz->vde_chn_id);
    }
	
	return s32ret != HI_SUCCESS? 0:-1;	
}

static int vdec_chn_bind_output_chn(Decoder *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	return 0;
}


Decoder *video_decoder_create(int vdec_chn, int max_pic_width, int max_pic_height)
{
	Decoder *thiz = NULL;

	msg_dbg("fun[%s] vdec_chn(%d), width(%d), height(%d)\n", __func__, vdec_chn, max_pic_width, max_pic_height);

	thiz = (Decoder *)COMM_ZALLOC(sizeof(Decoder));

	thiz->vde_chn_id = vdec_chn;
	thiz->max_pic_width = max_pic_width;
	thiz->max_pic_height = max_pic_height;
	
	create_vdec_chn(thiz, PT_H264);

	return thiz;
}

unsigned char g_buffer[124] = {1};

int video_decoder_decode_data(Decoder *thiz, Block *block)
{
	HI_S32 s32ret;
	
	VDEC_STREAM_S stStream;
	stStream.pu8Addr = block->p_buffer;
	stStream.u32Len = block->buffer_len;
	stStream.u64PTS = 0;	
	
	s32ret = HI_MPI_VDEC_SendStream(thiz->vde_chn_id, &stStream, HI_IO_NOBLOCK);
	if (HI_SUCCESS != s32ret)
	{
		msg_dbg("HI_MPI_VDEC_SendStream [%02d], errno 0x%x \n", thiz->vde_chn_id, s32ret);
	}
	
	return (s32ret == HI_SUCCESS)?0:-1;
}

bool video_decoder_able_to_decode_next_data(Decoder *thiz)
{
	if(thiz)
	{
		VDEC_CHN_STAT_S stStat;
		HI_S32 s32ret;
		
		s32ret = HI_MPI_VDEC_Query(thiz->vde_chn_id, &stStat);
		if(s32ret != HI_SUCCESS)
		{
			msg_dbg("HI_MPI_VDEC_Query errno 0x%x\n", s32ret);
			return true;
		}
		
		if(stStat.u32LeftStreamFrames < MDEC_DATUM_LINE || stStat.u32LeftStreamFrames > 0xff)
		{
//			msg_dbg("HI_MPI_VDEC_Query stStat.u32LeftStreamFrames(%d)\n", stStat.u32LeftStreamFrames);
			return true;
		}
	}
	
	return false;
}



int video_decoder_control(Decoder *thiz, int i_query, va_list args)
{
	return_val_if_failed(thiz != NULL, -1);
	
	msg_dbg("fun[%s]\n", __func__);

	switch(i_query)
	{
		case QUERY_DECODER_PAUSE:
			break;
		case QUERY_DECODER_RESUME:
		
			break;
		default:
			break;
	}
	
	return 0;
}

void video_decoder_destroy(Decoder *thiz)
{
	if(thiz)
	{
		
		HI_MPI_VDEC_StopRecvStream(thiz->vde_chn_id);
		HI_MPI_VDEC_DestroyChn(thiz->vde_chn_id);	
		
	}
	
	return;
}

