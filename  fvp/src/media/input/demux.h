/*
 * File: demux.h
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
 * 2011-4-4 zhoumin <dcdcmin@gmail.com> created
 *
 */

#ifndef DEMUX_H
#define DEMUX_H


#include"fvp_common.h"

#ifdef __cplusplus
extern "C"
#endif 

struct _Demux
{
	
};

typedef struct _Demux Demux;




static inline int demux_demux(Demux *thiz)
{	
	
}

static inline int demux_va_control( Demux *demux, int query, va_list args )
{
    return demux->pf_control( demux, query, args );
}


static inline int demux_control(Demux *thiz, int query, ...)
{
    va_list args;
    int     i_result;

    va_start( args, i_query );
    i_result = demux_vaControl( p_demux, i_query, args );
    va_end( args );
    return i_result;
}



#ifdef __cplusplus
}
#endif

#endif /*DEMUX_H*/



