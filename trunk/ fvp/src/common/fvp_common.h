/*
 * File: fvp_common.h
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
 * 2011-01-05 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef FVP_COMMON_H
#define FVP_COMMON_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h> 
#include <sys/ioctl.h>
#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "hi_comm_vo.h"
#include "hi_comm_vi.h"
#include "hi_comm_vpp.h"
#include "hi_comm_venc.h"
#include "hi_comm_vdec.h"
#include "hi_type.h"
#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_vi.h"
#include "mpi_vo.h"
#include "mpi_vpp.h"
#include "mpi_venc.h"
#include "mpi_vdec.h"
#include "hifb.h"


#ifdef __cplusplus
extern "C"{
#endif


#define FVP_PROFILE

#ifdef FVP_PROFILE
static size_t profile_begin;
#define PROFILE_START() profile_begin = get_relative_time();
#define PROFILE_END(what) msg_dbg("%s:%d %s cost %d ms\n", __func__, __LINE__, \
	what, get_relative_time() - profile_begin);
#define PROFILE_TIME(what) msg_dbg("%s:%d %s time=%d\n", __func__, __LINE__, what, get_relative_time());
#else
#define PROFILE_START()
#define PROFILE_END(what)
#define PROFILE_TIME(what) 
#endif


#define return_val_if_failed(p, val) if(!(p))\
	{printf("%s:%d Warning: "#p" failed.\n",\
	__func__, __LINE__); return (val);}


#define return_if_failed(p) if(!(p))\
	{printf("%s:%d Warning: "#p" failed.\n", \
		__func__, __LINE__); return;}


#define MPP_RETURN_CHECK(ret, func, fail_return_val) if(ret != HI_SUCCESS){\
										msg_dbg("%s fail 0x%08x.\n", func, ret); \
										return fail_return_val; \
								   	}


#define color_t unsigned short


#define DECL_PRIV(thiz, priv) PrivInfo* priv = thiz != NULL ? (PrivInfo*)thiz->priv : NULL

#define DECL_PRIV0(thiz, priv) PrivInfo *priv = (thiz != NULL)?(PrivInfo *)thiz->priv_subclass[0]:NULL


#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif/*__cplusplus*/



#define COMM_ALLOC(s)       malloc(s)
#define COMM_REALLOC(p, s)  realloc(p, s)
#define COMM_ZALLOC(s)      calloc(1, s)
#define COMM_FREE(p)        if(p) {free(p); p = NULL;}
#define COMM_ZFREE(p, size) if(p) {memset((p), 0x00, (size)); free(p); p = NULL;}
#define COMM_STRDUP(s)		comm_strdup(s)

static inline char *comm_strdup(char *s)
{
	char *buf = NULL;
	if(s)
	{
		int length = strlen(s) + 1;
		buf = (char *)COMM_ALLOC(length);
		memcpy(buf, s, length);
	}
	return buf;
}




#ifdef __cplusplus
}
#endif

#endif /*FVP_COMMON_H*/
