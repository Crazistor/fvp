/*
 * File: fvp_fujnction.c
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

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<pthread.h>
#include<error.h>
#include<signal.h>
#include"fvp_function.h"


Ret create_normal_thread(ThreadFunction function, void *para, pthread_t *pid)
{
	return_val_if_failed(para != NULL, RET_INVALID_PARAMETER);	
	
	pthread_t thread_id;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	if(pthread_create(&thread_id, &attr, function, para) == 0)
    {
        pthread_attr_destroy(&attr);
		if(pid != NULL)		
		{
			*pid = thread_id;
		}
        return RET_OK;
    }
	pthread_attr_destroy(&attr);
	
	return RET_FAILED;
}


void public_msleep(unsigned int milli_second)
{
	struct timeval time;

    time.tv_sec = milli_second / 1000;
    time.tv_usec = milli_second* 1000 % 1000000;

    select(0, NULL, NULL, NULL, &time);

}

/*
 * get the file size
 */
int public_get_file_size(char *file_name)
{
	return_val_if_failed(file_name != NULL, -1);

	struct stat buf;
	int fd = -1;
	
	if(stat(file_name, &buf) == 0)
	{
		return buf.st_size;
	}
	else
	{
		printf("stat log file failed! error(%d)\n", error);
	}
	
	return  -1;
}
