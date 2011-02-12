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



#define BACKLOG 			5					//允许连接的客户的最大个数
#define VERSION_LEN 		24					//系统版本字符个数
#define PORT 				8100				//开放的端口
#define SEARCH_PORT 		8200				//搜索端口号
#define DATA_BUF_SIZE 		1024				//数据缓冲区大小
#define MAX_BLOCK_SIZE 		128*1024			//FLASH的Block最大长度
#define FILE_NAME_LEN		128					//文件名数据长度
#define UPDATE_FILE_NAME	"/home/hi_3515"				//"/dev/mtdblock4"	//升级文件的文件名

//1.1设备内部消息错误代码
typedef enum 
{
	DEVICE_MSG_ERROR_CODE_SUCC 	 	= 0,	//操作成功
	DEVICE_MSG_ERROR_CODE_FAIL	 	= 1,	//操作失败
}DeviceErrorCode_E;

//1.2设备内部消息头
typedef struct 
{
	unsigned int  length;					//消息总长度
	unsigned int  msgType;					//消息类型
}DeviceMsgHeader_S;

//1.3关闭相关应用请求消息
typedef struct 
{
	DeviceMsgHeader_S header;				//消息头
}ShutAppReqMsg_S;
	
//1.4关闭相关应用响应消息
typedef struct 
{
	DeviceMsgHeader_S header;				//消息头
	DeviceErrorCode_E errorCode;			//错误代码
}ShutAppRespMsg_S;

/*---------------------------------外部网络消息-----------------------------------*/

//2.1 网络通用消息类型
typedef enum 
{
	NET_COMM_MSG_DEVICE_SEARCH_REQ   	= 2000,   //客户端设备搜索请求消息
	NET_COMM_MSG_DEVICE_SEARCH_RSP    	= 2001,   //设备端设备搜索响应消息
}NetCommMsgType_E;

//2.2 网络通知消息类型
typedef enum 
{
	NET_NOTIFY_MSG_CLIENT_SHUT_DOWN	 	 = 3001,  //客户端关闭应用通知消息
}NetNotifyMsgType_E;

//2.3网络消息错误代码
typedef enum 
{
	NET_MSG_ERROR_CODE_SUCC 	 			= 0,	//操作成功
	NET_MSG_ERROR_ALLOC_MEMORY_FAIL 		= 1,	//分配内存失败
	NET_MSG_ERROR_OPEN_FLASH_FAIL			= 2,	//打开FLASH失败
	NET_MSG_ERROR_FILE_TRANFER_FAIL 		= 3,	//文件传送失败
	NET_MSG_ERROR_WRITE_FLASH_FAIL 			= 4,	//写入FLASH失败
	NET_MSG_ERROR_CLIENT_CONNECTED 			= 5,	//已有客户端连接
	NET_MSG_ERROR_NET_IS_UPGRADING			= 6,	//客户端正在升级	
	NET_MSG_ERROR_GUI_IS_UPGRADING			= 7,	//设备端正在升级
	NET_MSG_ERROR_FILE_NAME_ERROR			= 8,	//升级文件名错误
	NET_MSG_ERROR_IS_NEWEST_VERSION			= 9,	//当前软件已是最新版本
	NET_MSG_ERROR_UPGRADE_OTHER_ERROR		= 10,	//升级过程中的其它错误
	
}NetErrorCode_E;

//2.4网络消息头
typedef struct 
{
	unsigned int  msgType;						//消息类型
}NetMsgHeader_S;

//2.5网络消息包
typedef struct 
{
	NetMsgHeader_S header;					//消息头
	int msgLen;								//消息体长度
	char msgData[DATA_BUF_SIZE];			//消息体
}NetMsgPacket_S;

//2.6系统升级请求消息
typedef struct 
{
	int fileSize;							//文件大小
    char fileName[FILE_NAME_LEN];			//文件名称
}SystemUpdateReqMsg_S;

//2.7系统升级响应消息
typedef struct 
{
	NetErrorCode_E errorCode;				//错误代码
}SystemUpdateRespMsg_S;

//2.8文件传送结果通知消息
typedef struct 
{
	NetErrorCode_E errorCode;				//错误代码
}UpdateResultNotifyMsg_S;

//2.9 设备搜索响应消息
typedef struct 
{
	unsigned long ipaddr;					
	int subModuleNum;                   //子模块数:  5, 表示3515；8, 表示3520
	char UserPwd[8];					/*用户密码*/
	unsigned int Port;					//媒体流端口
 	unsigned int  DeviceID; 			/*本机编号*/
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
