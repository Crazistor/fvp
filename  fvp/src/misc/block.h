/*
 * File: block.h
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
 * Thu Apr  7 10:33:30 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */
#ifndef BLOCK_H
#define BLOCK_H

#include"fvp_common.h"


#ifdef __cplusplus
extern "C"{
#endif 

struct _Block;
typedef struct _Block Block;


#define VIDEO_FRAME_FLAG 1
#define AUDIO_FRAME_FLAG 2 

struct _Block
{
	Block *next;
	int flags;
	int alloc_size;
	size_t buffer_len;
	int frame_flag;
	unsigned char  *p_buffer;
};

/*
 * creatre a block , alloc size memory to store data
 */
Block *block_create(size_t size);


/*
 * 
 */
Block *block_realloc(Block *thiz, ssize_t prebody, int len);


/*
 * destroy the block  
 */
void block_destroy(Block *thiz);


#ifdef __cplusplus
}
#endif 

#endif /*BLOCK_H*/



