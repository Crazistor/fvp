/*
 * File: cores.c
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
 * 2011-01-05 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include"cores.h"
#include"parameter.h"

struct _Cores
{
	Parameter *parameter;
	SetupParameter *setup_para;
};

Cores *cores_create()
{
	Cores *thiz = NULL;
	thiz = (Cores *)COMM_ZALLOC(sizeof(Cores));	
	return_val_if_failed(thiz != NULL, NULL);	
	
	return thiz;
}

Ret cores_init(Cores *thiz)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);
	Parameter *parameter = NULL;

	parameter = parameter_create();	
	return_val_if_failed(parameter != NULL, RET_FAILED);
	parameter_init(parameter);
	thiz->parameter = parameter;
	
	thiz->setup_para = parameter_get_para(thiz->parameter);
	
	return RET_OK;
}


SetupParameter *cores_get_parameter(Cores *thiz)
{
	return_val_if_failed(thiz != NULL, NULL);

	return thiz->setup_para;
}

int cores_save_parameter(Cores *thiz, SetupParameter *para)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	parameter_set_para(thiz->parameter, para);
	return parameter_save_para(thiz->parameter);	
}

void cores_destroy(Cores *thiz)
{
	if(thiz != NULL)
	{
		if(thiz->parameter)
		{
			parameter_destroy(thiz->parameter);
		}
		
		COMM_FREE(thiz);
	}
	return;
}


