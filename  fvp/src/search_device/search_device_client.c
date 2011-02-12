/*
 * File: search_device_client.c
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

#include<netinet/in.h>
#include<stdbool.h>

#include"array_list.h"
#include"search_device_client.h"
#include"fvp_common.h"
#include"search_device_data.h"

struct _SearchDeviceClient
{
	ArrayList *array_list_device;
};

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

static int search_device_reset_device_list(SearchDeviceClient *thiz)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);
	
	if(thiz->array_list_device != NULL)
	{
		array_list_destroy(thiz->array_list_device);
	}
	thiz->array_list_device = array_list_create();
	return (thiz->array_list_device != NULL)?RET_OK:RET_FAILED;
}

static int search_device_add_device_to_list(SearchDeviceClient *thiz, DeviceSearchRespMsg_S *device)
{
	return_val_if_failed(thiz != NULL && device != NULL, RET_INVALID_PARAMETER);

	if(thiz->array_list_device != NULL)
	{
		return array_list_add(thiz->array_list_device, (void *)device);
	}

	return RET_FAILED;
}

static int search_device_get_remote_device_information(SearchDeviceClient *thiz, int socket_fd)
{
	return_val_if_failed(thiz != NULL && socket_fd >= 0, RET_INVALID_PARAMETER);

	NetMsgPacket_S netMsgPacket = {0};

	struct sockaddr_in addrfrom;
	addrfrom.sin_family=AF_INET;
	addrfrom.sin_addr.s_addr=INADDR_BROADCAST;
	addrfrom.sin_port=htons(SEARCH_PORT);
	int fromlength=sizeof(addrfrom);
	int recvLen = 0;
	
	if ((recvLen = recvfrom(socket_fd, (char *)&netMsgPacket,sizeof(netMsgPacket),
		0, (struct sockaddr *)&addrfrom, (socklen_t *)&fromlength)) == sizeof(netMsgPacket))
	{
		int msgType = ntohl(netMsgPacket.header.msgType);
		printf("DeviceSearch thread recvfrom msg[%d].\n", msgType);
		switch(msgType)
		{
			/*设备搜索响应消息*/
			case NET_COMM_MSG_DEVICE_SEARCH_RSP:
				{
					printf("recvfrom NET_COMM_MSG_DEVICE_SEARCH_RSP msg.\n");
					unsigned long ipaddr = 0;
					char ip_str[32] = {0};
					DeviceSearchRespMsg_S *pDeviceSearchMsg;
					pDeviceSearchMsg = (DeviceSearchRespMsg_S *)netMsgPacket.msgData;
					ipaddr = ntohl(pDeviceSearchMsg->ipaddr);	
					ipaddr_to_ipstr(ipaddr, ip_str);
					printf("the remote dvr device ip addr is(%s)\n", ip_str);
					printf("web port(%d)\n", pDeviceSearchMsg->Port);

					DeviceSearchRespMsg_S *device_data = (DeviceSearchRespMsg_S *)COMM_ZALLOC(sizeof(DeviceSearchRespMsg_S));

					memcpy(device_data, pDeviceSearchMsg, sizeof(DeviceSearchRespMsg_S));
					search_device_add_device_to_list(thiz, device_data);
				}
				break;
			default:
				printf("DeviceSearch thread recvfrom Unknown Message Type[%d]", msgType);
				break;
		}
	}
	else
	{
		return RET_FAILED;
	}
	
	return RET_OK;
}

static void *search_device_thread(void *para)
{
	printf("============search_device_thread start============\n");
	SearchDeviceClient *search_device_client = (SearchDeviceClient *)para;

	int socket_fd = -1;
	
	/*创建搜索套接字*/
	if((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)		
	{
		printf("Create Search Socket Failed.Error:%d\n",socket_fd);
		goto OUT;
	}
	
	/*然后赋值给地址，用来从网络上的广播地址接收消息；*/
	struct sockaddr_in addrto;
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = INADDR_BROADCAST;
	addrto.sin_port = htons(SEARCH_PORT);
	int opt=true;
	  
	/*设置该套接字为广播类型*/
	setsockopt(socket_fd,SOL_SOCKET,SO_BROADCAST,&opt,sizeof(opt));

	/*从广播地址发送消息*/
	NetMsgPacket_S netMsgPacket;
	memset(&netMsgPacket, 0x0, sizeof(netMsgPacket));
	netMsgPacket.header.msgType = htonl(NET_COMM_MSG_DEVICE_SEARCH_REQ);
	if (sendto(socket_fd, (char*)(&netMsgPacket), sizeof(netMsgPacket), 
		0, (struct sockaddr *)&addrto, sizeof(addrto)) == -1)
	{
		goto OUT;
	}

	struct timeval	select_timeout;
	fd_set rset;
	int ret = 0;
	int recvLen = 0;


	/*clean the device list*/
	search_device_reset_device_list(search_device_client);

	//线程运行循环	
	while(1) 
	{
		FD_ZERO(&rset);
		FD_SET(socket_fd, &rset);
		select_timeout.tv_sec = 5;
		select_timeout.tv_usec = 0;
		
		if((ret = select(socket_fd + 1, &rset, NULL, NULL, &select_timeout)) <= 0)
		{
			if (ret == 0)
			{
				printf("Socket Select Timeout.\n");
				break; 
			}
			else	
			{
				break;
			}
		}

		if(search_device_get_remote_device_information(search_device_client, socket_fd) != RET_OK)
		{
			printf("search_device_get_remote_device_information failed!\n");
			goto OUT;
		}

	}
	
OUT:
	
	printf("============search_device_thread over============\n");
	if(socket_fd >= 0)
	{
		close(socket_fd);
		socket_fd = -1;
	}
	return NULL;
}

SearchDeviceClient *search_device_client_create()
{
	SearchDeviceClient *thiz = NULL;

	thiz = (SearchDeviceClient *)COMM_ZALLOC(sizeof(SearchDeviceClient));
	thiz->array_list_device = array_list_create();
	return thiz;
}

int search_device_client_search_device(SearchDeviceClient* thiz, void *search_result)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);
		
	create_normal_thread(search_device_thread, (void *)thiz, NULL);

	return RET_OK;
	
}

int search_device_client_get_device_numbers(SearchDeviceClient *thiz)
{
	return_val_if_failed(thiz != NULL && thiz->array_list_device != NULL,  -1);
	
	return array_list_get_size(thiz->array_list_device);

}


/*
 * device_id  device_id must > 0
 */
int search_device_client_get_remote_device_by_id(SearchDeviceClient *thiz, int device_id, RemoteDeviceInfomation *remote_device)
{
	return_val_if_failed(thiz != NULL && device_id >= 0 && remote_device != NULL, RET_INVALID_PARAMETER);

	DeviceSearchRespMsg_S *temp_device_inforamtion = NULL;

	return_val_if_failed(thiz->array_list_device, RET_FAILED);
	temp_device_inforamtion = (DeviceSearchRespMsg_S *)array_list_get_data_by_id(thiz->array_list_device, device_id - 1);

	if(temp_device_inforamtion != NULL)
	{
		remote_device->ipaddr = temp_device_inforamtion->ipaddr;
		remote_device->Port = temp_device_inforamtion->Port;
		remote_device->subModuleNum = temp_device_inforamtion->subModuleNum;
		memcpy(remote_device->UserPwd, temp_device_inforamtion->UserPwd, 8);
		remote_device->DeviceID = temp_device_inforamtion->DeviceID;
		return RET_OK;
	}
	
	return RET_FAILED;
}

void search_device_client_destory(SearchDeviceClient *thiz)
{
	if(thiz)
	{
		if(thiz->array_list_device)
		{
			array_list_destroy(thiz->array_list_device);	
		}

		COMM_FREE(thiz);
	}
	
	return;
}

