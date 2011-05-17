/*
 * File: fvp_typedef.h
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
 * 2011-5-17 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef FVP_TYPEDEF_H
#define FVP_TYPEDEF_H

#ifdef __cplusplus
extern "C"{
#endif 

#define MAX_H264_PACKET_LEN	1048576


#define MAX_ACCESSERS 			6


typedef enum hiVO_DEV_E
{
    VO_DEV_HD  = 0,                 /* high definition device */
    VO_DEV_AD  = 1,                 /* assistant device */
    VO_DEV_SD  = 2,                 /* spot device */
    VO_DEV_BUTT
}VO_DEV_E;

#define VO_BKGRD_RED      0xFF0000    /* red back groud color */
#define VO_BKGRD_GREEN    0x00FF00    /* green back groud color */
#define VO_BKGRD_BLUE     0x0000FF    /* blue back groud color */
#define VO_BKGRD_BLACK    0x000000    /* black back groud color */


#define MDEC_DATUM_LINE		8   /*·¶Î§(4-12)£¬½âÂë»º´æÖ¡Êý*/

								   	


typedef enum _Ret{
	RET_OK,
	RET_FAILED, 
	RET_INVALID_PARAMETER, 
	RET_MALLOC_FAILED,
}Ret;


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



#ifdef __cplusplus
}
#endif

#endif /*FVP_TYPEDEF_H*/

