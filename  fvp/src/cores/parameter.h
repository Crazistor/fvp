/*
 * File: parameter.h
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

#ifndef PARAMETER_H
#define PARAMETER_H

#include"fvp_common.h"
#include"parameter_define.h"


#ifdef __cplusplus
extern "C"{
#endif

typedef struct  _ParameterInfo  ParameterInfo;

struct _Parameter
{
	SetupParameter *setup_para;
	ParameterInfo *priv;
};

typedef struct _Parameter Parameter;




Parameter *parameter_create();
Ret parameter_init(Parameter *thiz);
SetupParameter *parameter_get_para(Parameter *thiz);
Ret parameter_set_para(Parameter *thiz, SetupParameter *setup_para);
Ret parameter_save_para(Parameter *thiz);
void parameter_destroy(Parameter *thiz);


#ifdef __cplusplus
}
#endif


#endif /*PARAMETER_H*/
