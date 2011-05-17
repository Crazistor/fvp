/*
 * File: alarm_list.h
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
#include"fvp_common.h"
#include"fvp_typedef.h"

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H


#ifdef __cplusplus
extern "C"{
#endif

struct _ArrayList;
typedef struct _ArrayList ArrayList;


ArrayList *array_list_create();

Ret array_list_add(ArrayList *thiz, void *data);
Ret array_list_remove(ArrayList *thiz, void *data, int data_size);
int array_list_get_id_by_data(ArrayList *thiz, void *data, int data_size);
void *array_list_get_data_by_id(ArrayList *thiz, int id);
int array_list_get_size(ArrayList *thiz);

void array_list_destroy(ArrayList *thiz);

#ifdef __cplusplus
}
#endif


#endif /*__ARRAY_LIST_H__*/
