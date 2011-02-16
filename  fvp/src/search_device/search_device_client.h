/*
 * File: search_device_client.h
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
 * 2011-01-25 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef SEARCH_DEVICE_CLIENT_H
#define SEARCH_DEVICE_CLIENT_H

#include"search_device_data.h"

#ifdef __cplusplus
extern "C"{
#endif

struct _SearchDeviceClient;
typedef struct _SearchDeviceClient SearchDeviceClient;

typedef struct  _RemoteDeviceInfomation
{
	unsigned long ipaddr;					
	int subModuleNum;                   //��ģ����:  5, ��ʾ3515��8, ��ʾ3520
	char UserPwd[8];					/*�û�����*/
	unsigned int Port;					//ý�����˿�
 	unsigned int  DeviceID; 			/*�������*/
}RemoteDeviceInfomation;

SearchDeviceClient *search_device_client_create();

int search_device_client_search_device(SearchDeviceClient* thiz, int *search_result);
int search_device_client_get_device_numbers(SearchDeviceClient *thiz);
int search_device_client_get_remote_device_by_id(SearchDeviceClient *thiz, int device_id, RemoteDeviceInfomation *remote_device);

void search_device_client_destory(SearchDeviceClient *thiz);


#ifdef __cplusplus
}
#endif

#endif

