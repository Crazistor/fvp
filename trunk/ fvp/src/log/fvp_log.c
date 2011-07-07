/*
 * File: fvp_log.c
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
 * 2011-06-20 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include<stdarg.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"fvp_log.h"


static LogLevel fvp_log_level = LOG_DEBUG;
static LogSaveMode fvp_log_save_mode = LOG_PRINT;
static char *log_file = NULL;


	
#define LOG_BUFFER_SIZE 1024
static int log_handle(const char* format, va_list ap)
{
    char buffer[LOG_BUFFER_SIZE] = {0};
    vsnprintf(buffer, LOG_BUFFER_SIZE, format, ap);

	if(fvp_log_save_mode == LOG_FILE_MODE)
	{    
        int fd = -1;
        fd = open(log_file, O_WRONLY|O_CREAT|O_APPEND);
        if(fd > 0)
        {
            write(fd,buffer,sizeof(buffer));
            
            close(fd);
            fd = -1;
        }
    }
    
    printf(buffer);
  
    return 0;
}

int fvp_log_init(FvpLogLevel log_level, FvpLogSaveMode mode, char *filename)	
{
	static int log_inited = 0;

	if(log_inited === 1)
	{
		return 0;
	}
	
    fvp_log_level = log_level;
    fvp_log_save_mode = mode;

	if(mode == LOG_MODE_FILE)
	{	
	    if(filename != NULL)
        {
            log_file = FTK_STRDUP(filename);
        }   
        else
        {
            log_file = FTK_STRDUP("./log.dat");
        }
       
	}
	
	log_inited = 1;

    return 0;
}


/*debug log*/
void fvp_log_d(char *format, ...)
{
    if(fvp_log_level > LOG_D)
    {
    	return;
    }

    va_list ap;
    va_start(ap, format);

    log_handle(format, ap);
	
    va_end(ap);

    return;	
}

/*infomation log*/
void fvp_log_i(char *format, ...)
{
	if(fvp_log_level > LOG_I)
	{
		return;
	}

	va_list ap;
	va_start(ap, format);

	log_handle(format, ap);

	va_end(ap);

	return; 
}

/*warn log*/
void fvp_log_w(char *format, ...)
{
	if(fvp_log_level > LOG_W)
	{
		return;
	}

	va_list ap;
	va_start(ap, format);

	log_handle(format, ap);

	va_end(ap);

	return; 
}

/*error log*/
void fvp_log_e(char *format, ...)
{
	if(fvp_log_level > LOG_E)
	{
		return;
	}

	va_list ap;
	va_start(ap, format);

	log_handle(format, ap);

	va_end(ap);

	return; 
}



