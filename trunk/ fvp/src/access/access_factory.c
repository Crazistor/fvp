/*
 * File: access_factory.c
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
 * Tue Apr 19 10:31:14 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"access_factory.h"
#include"access_file.h"
#include"access_avi.h"


static Access *accesser_file_create_a_accesser(char *access_path)
{
	if(access_path)
	{
		if(strstr(access_path, "avi"))
		{
			return access_avi_create(access_path);
		}
		else
		{
			return access_file_create(access_path);
		}
	}

	return NULL;
}


Access *accesser_factory_create_a_accesser(char *access_path)
{
	Access *thiz = NULL;
	
	if(access_path)
	{
		if(strstr(access_path, "file"))
		{
			return accesser_file_create_a_accesser(access_path);
		}
		else
		{	
			msg_dbg("Fun(%s)error not define \n", __func__);
		}
	}
	
	return thiz;	
}




