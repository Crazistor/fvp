/*
 * File: fvp_mutex.c
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
 * 2011-02-14 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"fvp_mutex.h"


void fvp_mutex_init(fvp_mutex_t *mutex)
{
    pthread_mutex_init(mutex, NULL);   
}
void fvp_mutex_lock(fvp_mutex_t *mutex)
{

	pthread_mutex_lock(mutex);
}

void fvp_mutex_unlock(fvp_mutex_t *mutex)
{
	
	pthread_mutex_unlock(mutex);
}


void fvp_mutex_destroy (fvp_mutex_t *mutex)
{
    pthread_mutex_destroy( mutex );
}


