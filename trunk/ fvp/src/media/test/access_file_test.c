/*
 * File: access_file_test.c
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
 * Thu Apr  7 12:14:39 CST 2011 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"access_file.h"


#define TEST_FILENAME "./test.txt"

int main(int argc, char *argv[])
{
	MSG_DBG("Test the access file\n");
	Access *access_file = NULL;
	unsigned char buffer[1024]  = {0};
		
	access_file = access_file_create(TEST_FILENAME);
	assert(access_file != NULL);
	
	access_seek(access_file , 0);
	access_control(access_file , 0, NULL);
	
	while(getchar() != 'q')
	{
		access_read(access_file, buffer, 128);
	}

	access_destroy(access_file);

	return  0;
}



