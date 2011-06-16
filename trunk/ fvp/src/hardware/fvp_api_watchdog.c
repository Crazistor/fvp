/*
 * File: fvp_api_watchdog.c
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

#include "fvp_api_watchdog.h"


static int watchdog_fd = -1;
static bool is_watchdog_enable = false; 


#define WATCHDOG_DEV_FILE "/dev/watchdog"

int fvp_api_wdt_open(void)
{
	if(watchdog_fd < 0)
	{
        watchdog_fd = open(WATCHDOG_DEV_FILE, O_RDWR);
		if(watchdog_fd < 0)
		{
			msg_dbg("fun(%s) error: open the watchdog dev file(%s) failed!\n", __func__, WATCHDOG_DEV_FILE);
			return -1;
		}
	}

	fvp_api_wdt_enble();
	
    return 0;
}

int fvp_api_wdt_close(void)
{
	if(watchdog_fd < 0)
	{
		msg_dbg("Fun(%s) error : watch dog is not open!\n", __func__);
		return -1;
	}
	
	fvp_api_wdt_disable();

	close(watchdog_fd);
	watchdog_fd = -1;

	return 0;
}

int fvp_api_wdt_reboot(void)
{
	fvp_api_wdt_settimeout(1000);
	
	sleep(2);
	
    return 0;
}

int fvp_api_wdt_settimeout(unsigned int msec)
{
	if(watchdog_fd < 0 || is_watchdog_enable == false)
	{
		msg_dbg("Fun(%s) error : watch dog is not open or watch dog is disable!\n", __func__);
		return -1;
	}
	
	HI_S32 ret = 0;	
	HI_U32 second = msec/1000;

	ret = ioctl(watchdog_fd, WDIOC_SETTIMEOUT, &second);	
	if(ret)
	{
	    msg_dbg("fvp_api_wdt_settimeout failed!\n");
        return -1;
	}
	
    return 0;
}

int fvp_api_wdt_feed_wdt(void)
{
	if(watchdog_fd < 0 || is_watchdog_enable == false)
	{
		msg_dbg("Fun(%s) error : watch dog is not open or watch dog is disable!\n", __func__);
		return -1;
	}

	int ret = 0;
	
	ret = ioctl(watchdog_fd, WDIOC_KEEPALIVE, 0);    
	if(ret != 0)    
	{        
	    msg_dbg("fvp_api_wdt_feed_wdt Failed!\n");  
	    return -1;
	}
	
    return 0;
}

int fvp_api_wdt_enble(void)
{
	if(watchdog_fd < 0)
	{
		msg_dbg("Fun(%s) error : watch dog is not open!\n", __func__);
		return -1;
	}

	if(is_watchdog_enable == true)
	{
		return 0;
	}
	
	HI_U32 enable_flag = WDIOS_ENABLECARD;    
	HI_S32 ret = 0;    
	
	ret = ioctl(watchdog_fd, WDIOC_SETOPTIONS, enable_flag);    
	if(ret == 0)    
	{	    
		is_watchdog_enable = true;
	}    
	else    
	{	    
	    msg_dbg("watch dog disable Failed!\n");  	    
	    return -1;    
	} 

    return 0;
}

int fvp_api_wdt_disable(void)
{
	if(watchdog_fd < 0)
	{
		msg_dbg("Fun(%s) error : watch dog is not open!\n", __func__);
		return -1;
	}

	if(is_watchdog_enable == false)
	{
		return 0;
	}
	
	HI_U32 enable_flag = WDIOS_DISABLECARD;    
	HI_S32 ret = 0;    
	
	ret = ioctl(watchdog_fd, WDIOC_SETOPTIONS, enable_flag);    
	if(ret == 0)    
	{	    
		is_watchdog_enable = false;
	}    
	else    
	{	    
	    msg_dbg("watch dog disable Failed!\n");  	    
	    return -1;    
	} 

    return 0;
}


