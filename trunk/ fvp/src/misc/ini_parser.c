/*
 * File: ini_parser.c
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


#include"ini_parser.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

struct _IniParser
{	
	char *a;
	IniBuilder *builder;
};


static int ini_parser_handle_group(IniParser *thiz, char *group)
{
	return_val_if_failed(thiz && thiz->builder && group,  -1);

	ini_builder_on_group(thiz->builder, group);

	return 0;
}

static int ini_parser_handle_key_value(IniParser *thiz, char *key, char *value)
{
	return_val_if_failed(thiz && thiz->builder && key, -1);
	
	ini_builder_on_key_value(thiz->builder, key, value);

	return 0;
}

static int ini_parser_handle_comment(IniParser *thiz, char *comment)
{
	return_val_if_failed(thiz && thiz->builder && comment, -1);

	ini_builder_on_comment(thiz->builder, comment);

	return 0;
}

IniParser *ini_parser_create()
{
	IniParser *thiz = NULL;

	thiz = (IniParser *)COMM_ZALLOC(sizeof(IniParser));

	return thiz;
}

void ini_parser_set_builder(IniParser *thiz, IniBuilder *builder)
{	
	return_if_failed(thiz != NULL );

	thiz->builder = builder;

	return;
}

#define MAX_BUF_SIZE 128

void ini_parser_parse(IniParser *thiz, char *ini, char *comment_char)
{
	return_if_failed(thiz != NULL && ini != NULL );

	char *group_start = NULL;
	char *comment_start = NULL;
	char *key_start = NULL;
	char *value_start = NULL;
	char *p = NULL;
	
	if(comment_char == NULL)
	{
		*comment_char = '=';
	}
	
	enum _IniState
	{
		STATE_NONE,
		STATE_GROUP,
		STATE_KEY,
		STATE_VALUE,
		STATE_COMMENT,
	}state = STATE_NONE;

	for(p =  ini; *p != '\0'; p++)
	{
		switch(state)
		{
			case STATE_NONE:
			{	
				if(*p == '[')
				{
					state = STATE_GROUP;
					group_start = p + 1;
				}
				else if(*p == *comment_char)
				{
					state = STATE_COMMENT;
					comment_start = p + 1;
				}
				else if(!isspace(*p))
				{
					state = STATE_KEY;
					key_start = p;
				}
				break;
			}
			case STATE_GROUP:
			{
				if(*p == ']')
				{
					state = STATE_NONE;
					*p = '\0';

					ini_parser_handle_group(thiz, group_start);	
				}
				break;
			}
			case STATE_KEY:
			{
				if(*p == '=')
				{
					state = STATE_VALUE;
					value_start = p + 1;
					*p = '\0';
				}
				break;
			}
			case STATE_VALUE:
			{
				if(*p == '\r' || *p == '\n')
				{
					*p = '\0';
					state = STATE_NONE;
					ini_parser_handle_key_value(thiz, key_start, value_start);
				}
				break;
			}
			
			case STATE_COMMENT:
			{
				if(*p == '\n' || *p == '\r')
				{
					*p = '\0';
					state = STATE_NONE;
					ini_parser_handle_comment(thiz, comment_start);
				}
				break;
			}
			default:
				break;
		}
	}

	return;
}

void ini_parser_destory(IniParser *thiz)
{
	if(thiz)
	{
		COMM_ZFREE(thiz,sizeof(IniParser));
	}

	return;
}

