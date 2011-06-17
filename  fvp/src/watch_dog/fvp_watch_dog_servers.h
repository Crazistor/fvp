/*
 * File: fvp_watch_dog.h
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
 * 2011-6-15 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef FVP_WATCH_DOG_SERVERS_H
#define FVP_WATCH_DOG_SERVERS_H

#include"fvp_common.h"
#include"fvp_monitor.h"

#ifdef __cplusplus
extern "C"{
#endif

/*init a watch dog servers module*/
int fvp_watch_dog_servers_init(void);

/*deinit the watch dog servers module*/
int fvp_watch_dog_servers_deinit(void);

/*add a monitor to the watch dog service
 *@monitor :the  moudule monitor 
 *@retrun 0 success , -1 failed
 */
int fvp_watch_dog_servers_add_monitor(FvpMonitor *monitor);

/*remove the monitor frome the watch dog service
 *@monitor:the module monitor
 *@return 0 success, -1 failed
 */
int fvp_watch_dog_servers_remove_monitor(FvpMonitor *monitor);


#ifdef __cplusplus
}
#endif

#endif /*FVP_WATCH_DOG_H*/
