/*
 * File: watchdog_servers_test.c
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
 * 2011-6-16 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"fvp_watch_dog_servers.h"



static int monitor_handle(FvpMonitor *thiz)
{
	return_val_if_failed(thiz != NULL, -1);

	printf("fun(%s) handle!\n", __func__);
	printf("if the monitor is block, that will cause the watch dog to reboot the system!\n");
	printf("enter a char to cancel the block status!\n");
	
	getchar();
	
	return 0;
}

static void monitor_destroy(FvpMonitor *thiz)
{
	return_if_failed(thiz != NULL);

	COMM_FREE(thiz);		
	
	return;
}

static FvpMonitor *monitor_create(void)
{
	FvpMonitor *monitor = NULL;

	monitor = (FvpMonitor *)COMM_ALLOC(sizeof(FvpMonitor));

	monitor->handle = monitor_handle;
	monitor->destroy = monitor_destroy;

	return monitor;
}

int main(int argc, char *argv[])
{
	TEST_BEGIN("Test watch dog servers");

	FvpMonitor *monitor = NULL;

	fvp_watch_dog_servers_init();
	
	monitor = monitor_create();
	fvp_watch_dog_servers_add_monitor(monitor);

	sleep(10);

	fvp_watch_dog_servers_remove_monitor(monitor);
	fvp_monitor_destroy(monitor);
	
	sleep(25);
	
	fvp_watch_dog_servers_deinit();

	TEST_END("Test watch dog servers");

	return 0;
}


