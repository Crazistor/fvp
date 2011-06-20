/*
 * File: fvp_log.h
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
 * 2011-06-20 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef FVP_LOG_H
#define FVP_LOG_H


#ifdef __cplusplus
extern "C"{
#endif 

typedef enum  _LogLevel
{
    LOG_D,
    LOG_I,
    LOG_W,
    LOG_E,
}LogLevel;


typedef enum _LogSaveMode
{
    LOG_PRINT_MODE,
    LOG_FILE_MODE,
}LogSaveMode;

/*Init the log module
 @log_level set the log level  LOG_D --handle the debug log 
 @mode LOG_PRINT_MODE -- print the msg  LOG_FILE_MODE -- SAVE the log to the log file
 @filename if mode == LOG_FILE_MODE then the log save to filename file
 @return 0 -- success,  -1 --failed 
*/
int log_init(LogLevel log_level, LogSaveMode mode, char *filename);

/*debug log*/
void log_d(char *format, ...);

/*infomation log*/
void log_i(char *format, ...);

/*warn log*/
void log_w(char *format, ...);

/*error log*/
void log_e(char *format, ...);


#ifdef __cplusplus
}
#endif 

#endif /*FVP_LOG_H*/



