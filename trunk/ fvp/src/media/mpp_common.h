/*
 * File: mpp_common.h
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
 * but WI_HOUT ANY WARRANTY; without even the implied warranty of
 * MER_HANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *_History:
 * ================================================================
 * Fri Apr 15 15:39:17 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */




#ifndef MPP_COMMON_H
#define MPP_COMMON_H


typedef enum hiVO_DEV_E
{
    VO_DEV_HD  = 0,                 /* high definition device */
    VO_DEV_AD  = 1,                 /* assistant device */
    VO_DEV_SD  = 2,                 /* spot device */
    VO_DEV_BUTT
} VO_DEV_E;

#define VO_BKGRD_RED      0xFF0000    /* red back groud color */
#define VO_BKGRD_GREEN    0x00FF00    /* green back groud color */
#define VO_BKGRD_BLUE     0x0000FF    /* blue back groud color */
#define VO_BKGRD_BLACK    0x000000    /* black back groud color */




#endif /*MPP_COMMON*/



