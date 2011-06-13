/*
 * File: access.h
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
 * 2011-04-07 zhoumin <dcdcmin@gmail.com> created
 *
 */
#ifndef ACCESS_H
#define ACCESS_H

#include"fvp_typedef.h"
#include"fvp_common.h"
#include"block.h"
#include"fvp_msg.h"
#include<stdarg.h>

#ifdef __cplusplus
extern "C"{
#endif 

struct _Access;
typedef struct _Access Access;

typedef void (*AccessSeek)(Access *thiz,  unsigned long pos);
typedef int (*AccessRead)(Access *thiz, uint8_t *buffer, size_t len);
typedef Block*(*AccessBlock)(Access *thiz);
typedef void (*AccessControl)(Access *thiz, int query, va_list args);
typedef void (*AccessDestroy)(Access *thiz);


struct _Access
{
	AccessSeek seek;
    AccessBlock block;
    AccessRead read;
	AccessControl control;
    AccessDestroy destroy;
    struct
    {
        int file_size; /*Video file size*/
		int i_pos;	  

       	int total_seconds; /*file time length*/
       	int cur_seconds;   /*current play file time*/	

       	bool b_eof;
    } info;
    char priv[0];
};

/*
 * read a data from the access
 */
static inline int access_read(Access *thiz, uint8_t *buffer, size_t len)
{	
	if(thiz != NULL && thiz->read != NULL )
	{
		return thiz->read(thiz, buffer, len);
	}
	
	return -1;	
}

/*
 * seek 
 */
static inline void access_seek(Access *thiz, unsigned long pos)
{
	return_if_failed(thiz != NULL);
	
    return thiz->seek(thiz,  pos);
}

/*
 * control
 */
static inline void access_control(Access *thiz, int query, va_list args)
{	
	return_if_failed(thiz != NULL);

    return thiz->control(thiz, query, args);
}
 
/*
 * read a block and return the block
 */
static inline Block *access_block(Access *thiz)
{	
    return_val_if_failed(thiz != NULL && thiz->block != NULL, NULL);

    return thiz->block(thiz);
}


/*
 * destroy the access
 */
static inline void access_destroy(Access *thiz)
{
    if(thiz && thiz->destroy)
    {
        thiz->destroy(thiz);
    }
    
	return;
}





#ifdef __cplusplus
}
#endif 

#endif /*ACCESS_H*/


