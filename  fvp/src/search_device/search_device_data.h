/*
 * File: search_device_data.h
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
#ifndef SEARCH_DEVICE_DATA_H
#define SEARCH_DEVICE_DATA_H



#define BACKLOG 			5					//�������ӵĿͻ���������
#define VERSION_LEN 		24					//ϵͳ�汾�ַ�����
#define PORT 				8100				//���ŵĶ˿�
#define SEARCH_PORT 		8200				//�����˿ں�
#define DATA_BUF_SIZE 		1024				//���ݻ�������С
#define MAX_BLOCK_SIZE 		128*1024			//FLASH��Block��󳤶�
#define FILE_NAME_LEN		128					//�ļ������ݳ���
#define UPDATE_FILE_NAME	"/home/hi_3515"				//"/dev/mtdblock4"	//�����ļ����ļ���

//1.1�豸�ڲ���Ϣ�������
typedef enum 
{
	DEVICE_MSG_ERROR_CODE_SUCC 	 	= 0,	//�����ɹ�
	DEVICE_MSG_ERROR_CODE_FAIL	 	= 1,	//����ʧ��
}DeviceErrorCode_E;

//1.2�豸�ڲ���Ϣͷ
typedef struct 
{
	unsigned int  length;					//��Ϣ�ܳ���
	unsigned int  msgType;					//��Ϣ����
}DeviceMsgHeader_S;

//1.3�ر����Ӧ��������Ϣ
typedef struct 
{
	DeviceMsgHeader_S header;				//��Ϣͷ
}ShutAppReqMsg_S;
	
//1.4�ر����Ӧ����Ӧ��Ϣ
typedef struct 
{
	DeviceMsgHeader_S header;				//��Ϣͷ
	DeviceErrorCode_E errorCode;			//�������
}ShutAppRespMsg_S;

/*---------------------------------�ⲿ������Ϣ-----------------------------------*/

//2.1 ����ͨ����Ϣ����
typedef enum 
{
	NET_COMM_MSG_DEVICE_SEARCH_REQ   	= 2000,   //�ͻ����豸����������Ϣ
	NET_COMM_MSG_DEVICE_SEARCH_RSP    	= 2001,   //�豸���豸������Ӧ��Ϣ
}NetCommMsgType_E;

//2.2 ����֪ͨ��Ϣ����
typedef enum 
{
	NET_NOTIFY_MSG_CLIENT_SHUT_DOWN	 	 = 3001,  //�ͻ��˹ر�Ӧ��֪ͨ��Ϣ
}NetNotifyMsgType_E;

//2.3������Ϣ�������
typedef enum 
{
	NET_MSG_ERROR_CODE_SUCC 	 			= 0,	//�����ɹ�
	NET_MSG_ERROR_ALLOC_MEMORY_FAIL 		= 1,	//�����ڴ�ʧ��
	NET_MSG_ERROR_OPEN_FLASH_FAIL			= 2,	//��FLASHʧ��
	NET_MSG_ERROR_FILE_TRANFER_FAIL 		= 3,	//�ļ�����ʧ��
	NET_MSG_ERROR_WRITE_FLASH_FAIL 			= 4,	//д��FLASHʧ��
	NET_MSG_ERROR_CLIENT_CONNECTED 			= 5,	//���пͻ�������
	NET_MSG_ERROR_NET_IS_UPGRADING			= 6,	//�ͻ�����������	
	NET_MSG_ERROR_GUI_IS_UPGRADING			= 7,	//�豸����������
	NET_MSG_ERROR_FILE_NAME_ERROR			= 8,	//�����ļ�������
	NET_MSG_ERROR_IS_NEWEST_VERSION			= 9,	//��ǰ����������°汾
	NET_MSG_ERROR_UPGRADE_OTHER_ERROR		= 10,	//���������е���������
	
}NetErrorCode_E;

//2.4������Ϣͷ
typedef struct 
{
	unsigned int  msgType;						//��Ϣ����
}NetMsgHeader_S;

//2.5������Ϣ��
typedef struct 
{
	NetMsgHeader_S header;					//��Ϣͷ
	int msgLen;								//��Ϣ�峤��
	char msgData[DATA_BUF_SIZE];			//��Ϣ��
}NetMsgPacket_S;

//2.6ϵͳ����������Ϣ
typedef struct 
{
	int fileSize;							//�ļ���С
    char fileName[FILE_NAME_LEN];			//�ļ�����
}SystemUpdateReqMsg_S;

//2.7ϵͳ������Ӧ��Ϣ
typedef struct 
{
	NetErrorCode_E errorCode;				//�������
}SystemUpdateRespMsg_S;

//2.8�ļ����ͽ��֪ͨ��Ϣ
typedef struct 
{
	NetErrorCode_E errorCode;				//�������
}UpdateResultNotifyMsg_S;

//2.9 �豸������Ӧ��Ϣ
typedef struct 
{
	unsigned long ipaddr;					
	int subModuleNum;                   //��ģ����:  5, ��ʾ3515��8, ��ʾ3520
	char UserPwd[8];					/*�û�����*/
	unsigned int Port;					//ý�����˿�
 	unsigned int  DeviceID; 			/*�������*/
	char appVer[VERSION_LEN];
	char ubootVer[VERSION_LEN];
	char kernelVer[VERSION_LEN];
	char rootfsVer[VERSION_LEN];
	char logo[VERSION_LEN];
	char slaveUbootVer[VERSION_LEN];
	char slaveKernelVer[VERSION_LEN];
	char SlaveRootfsVer[VERSION_LEN];
}DeviceSearchRespMsg_S;


#endif /*SEARCH_DEVICE_DATA_H*/
