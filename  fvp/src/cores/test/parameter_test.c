/*
 * File: parameter_test.c
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
 * 2011-02-12 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include"parameter.h"
#include"fvp_common.h"
#include"parameter_define.h"

int main(int argc, char *argv[])
{

	Parameter *thiz = parameter_create();
	SetupParameter *para = NULL;	

	parameter_init(thiz);
	para = parameter_get_para(thiz);
	printf("record_mode channel 1 state(%d)\n", para->record_mode.is_chn_open[1]);
	para->record_mode.is_chn_open[1] = 1;
	assert(parameter_save_para(thiz) == RET_OK);
	parameter_destroy(thiz);

	return 0;
}
