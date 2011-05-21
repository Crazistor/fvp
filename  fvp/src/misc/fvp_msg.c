/*
 * File: fvp_msg.c
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
 * Tue Apr 12 12:11:16 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include<stdarg.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"fvp_msg.h"

#define MSG_BUFFER_SIZE 1024

static int msg_handle(const char* format, va_list ap)
{
   	char buffer[MSG_BUFFER_SIZE] = {0};
	vsnprintf(buffer, MSG_BUFFER_SIZE, format, ap);
	
	printf(buffer);
  
	return 0;
}

void msg_dbg(char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	msg_handle(format, ap);
	
	va_end(ap);

	return;	
}


