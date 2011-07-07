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

#include"fvp_common.h"


#ifdef __cplusplus
extern "C"{
#endif 

typedef enum  _FvpLogLevel
{
    FvpLOG_D,
    FvpLOG_I,
    FvpLOG_W,
    FvpLOG_E,
}FvpLogLevel;

typedef enum _FvpLogSaveMode
{
    FVP_LOG_PRINT_MODE,
    FVP_LOG_FILE_MODE,
}FvpLogSaveMode;

/*Init the log module
 @log_level set the log level  LOG_D --handle the debug log 
 @mode LOG_PRINT_MODE -- print the msg  LOG_FILE_MODE -- SAVE the log to the log file
 @filename if mode == LOG_FILE_MODE then the log save to filename file
 @return 0 -- success,  -1 --failed 
*/
int fvp_log_init(FvpLogLevel log_level, FvpLogSaveMode mode, char *filename);

/*debug log*/
void fvp_log_d(char *format, ...);

/*infomation log*/
void fvp_log_i(char *format, ...);

/*warn log*/
void fvp_log_w(char *format, ...);

/*error log*/
void fvp_log_e(char *format, ...);


#ifdef __cplusplus
}
#endif 

#endif /*FVP_LOG_H*/



