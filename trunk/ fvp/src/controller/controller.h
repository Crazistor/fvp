/*
 * File: controller.h
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
 * 2011-02-17 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<stdio.h>
#include<stdlib.h>
#include"controller.h"
#include"cores.h"
#include"search_device_client.h"

struct _Controller;
typedef struct _Controller Controller;

Controller *controller_create();

int controller_bind_cores(Controller *thiz, Cores *cores);
int controller_save_parameter(Controller *thiz, SetupParameter *setup_para);

int controller_bind_search_device_client(Controller *thiz, SearchDeviceClient *search_device_client);
int controller_search_device(Controller *thiz, void *ui_this);

void controller_destroy(Controller *thiz);

#endif /*CONTROLLER_H*/
