/*
 * File: controller.cpp
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
 * 2011-02-17 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include<stddef.h>
#include"controller.h"
#include"fvp_common.h"
#include"cores.h"
#include"fvp_gui.h"
#include"searchdevicepage.h"


struct _Controller
{
	Cores *cores;
	SearchDeviceClient *search_device_client;
};

#define DECL_CORES(thiz, cores) Cores *cores = (thiz != NULL)? thiz->cores:NULL

Controller *controller_create()
{
	Controller *thiz = NULL;
	thiz = (Controller *)COMM_ZALLOC(sizeof(Controller));	

	return thiz;
}


/*
 * bind cores model to the controller
 */
int controller_bind_cores(Controller *thiz, Cores *cores)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	thiz->cores = cores;

	return RET_OK;
}

int controller_save_parameter(Controller *thiz, SetupParameter *setup_para)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	DECL_CORES(thiz, cores);
	
	return cores_save_parameter(cores, setup_para);
}

/*
 * bind the search device client model to the controller
 */
int controller_bind_search_device_client(Controller *thiz, SearchDeviceClient *search_device_client)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	thiz->search_device_client = search_device_client;

	return RET_OK;
}


/*
 * search the dvr device which in the LAN
 */
int controller_search_device(Controller *thiz, void *ui_this)
{
	return_val_if_failed(thiz != NULL && thiz->search_device_client != NULL, RET_INVALID_PARAMETER);
	
	int search_result = 0;
	int device_numbers = 0;
	int i = 0;
	RemoteDeviceInformation remote_device_infor = {0};
	
	search_device_client_search_device(thiz->search_device_client, &search_result);
	
	((SearchDevicePage *)ui_this)->cleanDeviceQListView();
	((SearchDevicePage *)ui_this)->setUiToWaitingStatus();
	
	while(search_result == SEARCH_DEVICE_START)
	{	
		sleep(1);
	}	
	
	switch(search_result)
	{
		case SEARCH_DEVICE_FAILED:
			/*failed display a  messagebox*/			
			((SearchDevicePage *)ui_this)->displayHintMessagebox("Search Device Failed!\n");
			break;
		case SEARCH_DEVICE_SUCCESS:
			/*get the number of the  device numbers*/
			device_numbers = search_device_client_get_device_numbers(thiz->search_device_client);
			for(i = 1; i <= device_numbers; i++)
			{
				if(search_device_client_get_remote_device_by_id(thiz->search_device_client, i, &remote_device_infor)\
					== RET_OK)
				{
					/*update the ui  listview wedget*/
					((SearchDevicePage *)ui_this)->addDeviceIpStrToQListViewWidget(remote_device_infor.ipaddr_str);
				}
				else
				{
					break;
				}			
			}			
			((SearchDevicePage *)ui_this)->displayHintMessagebox("Search Device Success!\n");
		default:
			break;
	}
	
	return RET_OK;
}

void controller_destroy(Controller *thiz)
{
	if(thiz)
	{
		if(thiz->cores)
		{
			cores_destroy(thiz->cores);
		}		
		if(thiz->search_device_client)
		{
			search_device_client_destory(thiz->search_device_client);
		}	
		
		COMM_FREE(thiz);
	}

	return;
}

