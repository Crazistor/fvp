/*
 * File: demuxer.c
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
 * Thu Apr  7 17:43:55 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"demuxer.h"
#include"decoder.h"
#include"access_file.h"

struct _Demuxer
{
	Access *access;
	Decoder *decoder;
};


#define FILE_NAME "./test.txt"


Demuxer *demuxer_create()
{
	Demuxer *thiz = NULL;
	char *file_name = "test.txt";
	
	thiz = (Demuxer *)COMM_ZALLOC(sizeof(Demuxer));
	return_val_if_failed(thiz != NULL, NULL);

	/*create a access and decoder*/
	thiz->access = access_file_create(file_name);
	if(thiz->access == NULL)
	{
		msg_dbg("Error : not enough memory!\n");
		goto OUT_ERROR;
	}
	
	thiz->decoder = decoder_create(0, 720, 576);
	if(thiz->decoder == NULL)
	{
		msg_dbg("Error: alloc thiz->decoder not enough memory!\n");
		goto OUT_ERROR;
	}
	
	return thiz;
	
OUT_ERROR:
	
	if(thiz->access)
	{
		access_destroy(thiz->access);
	}
	
	return NULL;
}


int demuxer_demux(Demuxer *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	Block *block = NULL;
	
	/*get a  block from the access*/
	block = access_block(thiz->access);
	if(!block)
	{
		msg_dbg("read b block failed!\n");
		return 1;
	}

	/*send the block to the decoder */
	decoder_decode_data(thiz->decoder, block);

	return 0;
}


void demuxer_destroy(Demuxer *thiz)
{
	if(thiz)
	{

		msg_dbg("demuxer_destroy!\n");
	
	}
	
	return;
}

