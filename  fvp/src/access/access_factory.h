/*
 * File: access_factory.h
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
 * Tue Apr 19 10:30:57 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */
#ifndef ACCESS_FACTORY_H
#define ACCESS_FACTORY_H


#include"access.h"

#ifdef __cplusplus
extern "C"{
#endif 


Access *accesser_factory_create_a_accesser(char *access_path);



#ifdef __cplusplus
}
#endif 


#endif /*ACCESS_FACTORY_H*/



