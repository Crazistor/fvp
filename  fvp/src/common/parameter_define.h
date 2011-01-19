/*
 * File: parameter_define.h
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

#ifndef PARAMETER_DEFINE_H
#define PARAMETER_DEFINE_H
#include"fvp_common.h"
#include"fvp_config.h"

#define ASSIGN_FOUR_BYTES(number) (((number) + 3) / 4 * 4)

#define PARAMETER_MAGIC_NUMBER 0x20101230
typedef struct _RecordMode
{
	unsigned char is_chn_open[ASSIGN_FOUR_BYTES(MAX_CHANNEL_NUM)];/*1 open  0 close*/
	unsigned char chn_quality[ASSIGN_FOUR_BYTES(MAX_CHANNEL_NUM)];
	unsigned char record_mode;
	unsigned char packet_time;
	unsigned char chn_resolution[ASSIGN_FOUR_BYTES(MAX_CHANNEL_NUM)];
	unsigned char fps[ASSIGN_FOUR_BYTES(MAX_CHANNEL_NUM)];
	unsigned char audio;
	unsigned char reservel[8];
}RecordMode;


typedef struct _SetupParameter
{
	unsigned long magic;
	RecordMode record_mode;
}SetupParameter;









#endif /*PARAMETER_DEFINE_H*/
