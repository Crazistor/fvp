/*
 * File: parameter.c
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

#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<errno.h>
#include"parameter.h"

#define PARAMETER_DEV_FILE "/dev/mtdblock3"

static void parameter_default_record_mode(RecordMode *record_mode)
{
	if(record_mode)
	{
		int i = 0;
		for(i = 0; i < MAX_CHANNEL_NUM; i++)
		{
			record_mode->is_chn_open[i] = 1;
			record_mode->chn_quality[i] = 1;
			record_mode->chn_resolution[i] = 1;
			record_mode->fps[i] = 25;
		}
		record_mode->packet_time = 1;
		record_mode->audio = 1;
		record_mode->record_mode = 1;
	}
}

static void parameter_default_all_para(SetupParameter *para)
{
	if(para)
	{
		parameter_default_record_mode(&para->record_mode);
	}
}

static Ret parameter_check_para(SetupParameter *para)
{
	return_val_if_failed(para != NULL, RET_INVALID_PARAMETER);
	
	/*check magic number*/
	if(para->magic !=  PARAMETER_MAGIC_NUMBER)
	{
		printf("para->magic != PARAMETER_MAGIC_NUMBER \n");
		para->magic = PARAMETER_MAGIC_NUMBER;
		parameter_default_all_para(para);
		return RET_FAILED;
	}
		
	return RET_OK;
}

Parameter *parameter_create()
{
	Parameter *thiz  = NULL;

	thiz = (Parameter *)COMM_ZALLOC(sizeof(Parameter));
	
	return thiz;
}

Ret parameter_init(Parameter *thiz)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);
	
	int dev_fd = -1;	
	Ret ret = RET_OK;	

	/*open the dev */
	dev_fd = open(PARAMETER_DEV_FILE, O_RDWR);
	return_val_if_failed(dev_fd >= 0, RET_FAILED);

	/*read the parameter from the dev  file*/
	thiz->setup_para = (SetupParameter *)COMM_ZALLOC(sizeof(SetupParameter));
	if(thiz->setup_para == NULL)
	{
		ret = RET_FAILED;
		goto OUT;
	}	
	if(read(dev_fd, thiz->setup_para, sizeof(SetupParameter)) != sizeof(SetupParameter))
	{
		ret = RET_FAILED;
		goto OUT;
	}
	/*check the parameter*/
	if(parameter_check_para(thiz->setup_para) !=  RET_OK)
	{
		printf("parameter check parameter falied!\n");
		ret = RET_FAILED;
	}

OUT:
	if(dev_fd >= 0)
	{
		close(dev_fd);
		dev_fd = -1;
	}
	return ret;	
}


Ret parameter_set_para(Parameter *thiz, SetupParameter *setup_para)
{
	return_val_if_failed(thiz != NULL && setup_para != NULL, RET_INVALID_PARAMETER);
	
	memcpy(thiz->setup_para, setup_para, sizeof(SetupParameter));
	printf("gggggggggggggggggggggggggg\n");
	printf("value(%d)\n", thiz->setup_para->record_mode.is_chn_open[0]);
	return RET_OK;
}

/*
 * return the setup parameter point
 */
SetupParameter *parameter_get_para(Parameter *thiz)
{
	return_val_if_failed(thiz != NULL, NULL);
	
	return thiz->setup_para;
}

/*
 * save the parameter to the flash
 */
Ret parameter_save_para(Parameter *thiz)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	int dev_fd = -1;	
	Ret ret = RET_OK;

	printf("parameter_save_para\n");
	/*write the parameter to the flash*/
	dev_fd = open(PARAMETER_DEV_FILE, O_RDWR);
	if(dev_fd < 0)
	{
		ret = RET_FAILED;	
		goto OUT;
	}
	
	printf("write to the dev file\n");

	thiz->setup_para->magic = PARAMETER_MAGIC_NUMBER;
	
	if(write(dev_fd, thiz->setup_para, sizeof(SetupParameter))== -1)
	{
		ret = RET_FAILED;	
		printf("write file failed(%s), error(%d)\n", PARAMETER_DEV_FILE,  errno);
		goto OUT;
	}
	fsync(dev_fd);

OUT:
	if(dev_fd >= 0)
	{
		close(dev_fd);
		dev_fd = -1;
	}

	return ret;
}

void parameter_destroy(Parameter *thiz)
{
	if(thiz)
	{
		if(thiz->setup_para != NULL)
		{	
			COMM_FREE(thiz->setup_para);
		}
		
		COMM_FREE(thiz);
	}

	return;
}
