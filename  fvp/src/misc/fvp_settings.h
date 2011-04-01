/*
 * File: fvp_settings.h
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

#ifndef FVP_SETTINGS_H
#define FVP_SETTINGS_H

#include<stdio.h>
#include<stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif 


#define  SETTINGS_GET_INT(a, b, c)  to_int(fvp_settings_get_value(a, b, c))


struct _FvpSettings;
typedef struct _FvpSettings FvpSettings;

FvpSettings *fvp_settings_create(char *settings_file);
char *fvp_settings_get_value(FvpSettings *thiz, char *group_and_key, char *default_value);
int fvp_settings_sync(FvpSettings *thiz);
void fvp_settings_destroy(FvpSettings *thiz);

static inline int to_int(char *string)
{
	if(string)
	{			
		return atol(string);	
	}
	return -1;
}


#ifdef __cplusplus
}
#endif

#endif
