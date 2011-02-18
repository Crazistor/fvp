/*
 * File: search_device_client_test.c
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
#include"search_device_client.h"
#include<stdio.h>
#include<stdlib.h>
#include"fvp_common.h"

static void ipaddr_to_ipstr(unsigned long ulipaddr, char* pcIpStr) 
{
   sprintf(pcIpStr, "%u.%u.%u.%u", 
   					(ulipaddr >> 0) & 0x00FF,
				    (ulipaddr >> 8)	& 0x00FF,
				    (ulipaddr >> 16) & 0x00FF,
					(ulipaddr >> 24) & 0x00FF 
					);
   return;
} 

int main(int argc, char *argv[])
{
	int result = 0;

	SearchDeviceClient *thiz = search_device_client_create();
	search_device_client_search_device(thiz, &result);

	int j;
	for(j = 0; j < 50; j++)
	{
		if(result == SEARCH_DEVICE_START)
		{
			printf("search device is doing!\n");
		}
		else  
		{
			printf("search device is OVER !\n");
			break;
		}
		usleep(1000000);
	}
	
	int numbers = 0;
	int device_i = 0;
	RemoteDeviceInformation remote_device_infor = {0};
	int i;
	numbers = search_device_client_get_device_numbers(thiz);
	printf("The device numbers is (%d)\n", numbers);

	char ip_str[32] = {0};
	for(device_i = 1; device_i <= numbers; device_i++)
	{
		search_device_client_get_remote_device_by_id(thiz, device_i, &remote_device_info);
		printf("remote_device_info port(%d) subModuleNum(%d), DeviceID(%d)\n", 
				remote_device_info.Port, remote_device_info.subModuleNum, remote_device_info.DeviceID);
		printf("password:");
		for(i = 0; i < 8; i++)
		{
			printf("%d", remote_device_info.UserPwd[i]);
		}
		ipaddr_to_ipstr(remote_device_info.ipaddr, ip_str);
		printf("ip address(%s)\n", ip_str);
	}

	search_device_client_destory(thiz);
	return 0;
}
