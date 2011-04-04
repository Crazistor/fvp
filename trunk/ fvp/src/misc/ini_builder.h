/*
 * File: ini_builder.h
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
 * 2011-3-22 zhoumin <dcdcmin@gmail.com> created
 *
 */
#ifndef INI_BUILDER_H
#define INI_BUILDER_H

#include<stdio.h>
#include<stdlib.h>


#ifdef __cplusplus
extern "C"{
#endif

struct _IniBuilder;
typedef struct _IniBuilder IniBuilder;


typedef void (*IniBuilderOnGroup)(IniBuilder *thiz, char *group);
typedef void (*IniBuilderOnKeyValue)(IniBuilder *thiz, char *key, char *value);
typedef void (*IniBuilderOnComment)(IniBuilder *thiz, char *comment);
typedef void (*IniBuilderDestroyFunc)(IniBuilder *thiz);

struct _IniBuilder
{
	IniBuilderOnGroup on_group;
	IniBuilderOnKeyValue on_key_value;
	IniBuilderOnComment on_comment;
	IniBuilderDestroyFunc destroy;
    unsigned char ref_count;
	char priv[0];
};



static inline void ini_builder_on_group(IniBuilder *thiz, char *group)
{
	if(thiz != NULL && thiz->on_group != NULL)
	{
		thiz->on_group(thiz, group);
	}
	return;
}

static inline void ini_builder_on_comment(IniBuilder *thiz, char *comment)
{
	if(thiz && comment)
	{
		thiz->on_comment(thiz,  comment);
	}

	return;
}

static inline void ini_builder_on_key_value(IniBuilder *thiz, char *key, char *value)
{
	if(thiz	!= NULL && key != NULL)
	{	
		thiz->on_key_value(thiz, key, value);
	}

	return;
}

static inline void ini_builder_destroy(IniBuilder *thiz)
{
	if(thiz != NULL  && thiz->destroy != NULL)
	{
		thiz->destroy(thiz);
	}

	return;
}

#ifdef  __cplusplus
}
#endif 

#endif /*end of INI_BUILDER_H*/
