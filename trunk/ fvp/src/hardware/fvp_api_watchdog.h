/*
 * File: fvp_api_watchdog.h
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
 * 2011-06-16 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef FVP_API_WATCHDOG_H
#define FVP_API_WATCHDOG_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> 
#include <linux/watchdog.h>
#include <stdbool.h>
#include "fvp_msg.h"
#include "fvp_common.h"

#ifdef __cplusplus
extern "C"{
#endif 

int fvp_api_wdt_open(void);
int fvp_api_wdt_close(void);
int fvp_api_wdt_reboot(void);
int fvp_api_wdt_settimeout( unsigned int msec);
int fvp_api_wdt_feed_wdt(void);
int fvp_api_wdt_enble(void);
int fvp_api_wdt_disable(void);


#ifdef __cplusplus
}
#endif

#endif	/*FVP_API_WATCHDOG_H*/

