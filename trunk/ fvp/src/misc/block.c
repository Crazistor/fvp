/*
 * File: block.c
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
 * Fri Apr  8 11:09:57 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */


#include"block.h"


#define BLOCK_ALIGN 16
#define ALIGN(x) (((x) + BLOCK_ALIGN - 1) & ~(BLOCK_ALIGN - 1))

Block *block_create(size_t size)
{
	Block *thiz = NULL;

	thiz = (Block *)COMM_ALLOC(sizeof(Block));
	
	/*alloc a buffer */
	uint8_t *buf = NULL;
	buf = COMM_ALLOC(ALIGN(size));
	if(buf == NULL)
	{
		msg_dbg("error: not enough memory!\n");
		return NULL;
	}
		
	/*init  the block */
	thiz->next = NULL;
	thiz->flags = 0;
	thiz->p_buffer = buf;
	thiz->buffer_len = 0;
	thiz->alloc_size = size;
	
	return thiz;
}


Block *block_realloc(Block *thiz, ssize_t prebody, int len)
{
	return_val_if_failed(thiz != NULL, NULL);

	Block *new_block = NULL;

	
	return new_block;
}


void block_destroy(Block *thiz)
{
	if(thiz)
	{
		if(thiz->p_buffer)
		{
			COMM_FREE(thiz->p_buffer);
		}
		COMM_FREE(thiz);
	}
	
	return;
}

