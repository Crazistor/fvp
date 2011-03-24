/*
 * File: fvp_common.h
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

#ifndef FVP_COMMON_H
#define FVP_COMMON_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

#ifdef __cpluscplus
extern "C"{
#endif


typedef enum _Ret{
	RET_OK,
	RET_FAILED, 
	RET_INVALID_PARAMETER, 
	RET_MALLOC_FAILED,
}Ret;



#define return_val_if_failed(p, val) if(!(p))\
	{printf("%s:%d Warning: "#p" failed.\n",\
	__func__, __LINE__); return (val);}


#define return_if_failed(p) if(!(p))\
	{printf("%s:%d Warning: "#p" failed.\n", \
		__func__, __LINE__); return;}


#define color_t unsigned short


#define DECL_PRIV(thiz, priv) PrivInfo* priv = thiz != NULL ? (PrivInfo*)thiz->priv : NULL

#define DECL_PRIV0(thiz, priv) PrivInfo *priv = (thiz != NULL)?(PrivInfo *)thiz->priv_subclass[0]:NULL


#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif/*__cplusplus*/



#define COMM_ALLOC(s)       malloc(s)
#define COMM_REALLOC(p, s)  realloc(p, s)
#define COMM_ZALLOC(s)      calloc(1, s)
#define COMM_FREE(p)        if(p) {free(p); p = NULL;}
#define COMM_ZFREE(p, size) if(p) {memset((p), 0x00, (size)); free(p); p = NULL;}


static inline char *comm_strdup(char *s)
{
	char *buf = NULL;
	if(s)
	{
		int length = strlen(s) + 1;
		buf = (char *)COMM_ALLOC(length);
		memcpy(buf, s, length);
	}
	return buf;
}

#define COMM_STRDUP(s)		comm_strdup(s)

							

typedef  enum _Week{
    WK_SUNDAY,
    WK_MONDAY,
    WK_TUESDAY,
    WK_WEDNESDAY,
    WK_THURSDAY,
    WK_FRIDAY,
    WK_SATURDAY
}Week;

typedef struct _Datetime{
	int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    Week week;
}Datetime;

typedef enum _LogLevel
{
	LOG_LEVEL_V = 0,
	LOG_LEVEL_D = 1,
	LOG_LEVEL_E = 2,
	LOG_LEVEL_NR,
}LogLevel;

typedef enum _LogSaveMode
{
	LOG_MODE_PRINT = 0, 
	LOG_MODE_FILE = 1,
	LOG_MODE_NR,
}LogSaveMode;


typedef enum  _HddAlarm
{
	HDD_OK,
	HDD_ALARM_NO_HDD,
	HDD_ALARM_NO_SPACE,
	HDD_ALARM_NR,
}HddAlarm;


typedef enum _VideoResolution
{	
	VR_PAL,
	VR_NTSC,
	VR_720P,
	VR_1080P,
	VR_800x600,
	VR_1024x768,
	VR_1280x1024,
	VR_1366x768,
	VR_1440x900,
	VR_1440x990,
	VR_BUTT,
}VideoResolution;


#define SEARCH_DEVICE_START		0x2011
#define SEARCH_DEVICE_FAILED 	0x2012
#define SEARCH_DEVICE_SUCCESS 	0x2013


#ifdef __cpluspluc
}
#endif

#endif /*FVP_COMMON_H*/
