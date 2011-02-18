/*
 * File: searchdevicepage.cpp
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
 * 2011-02-28 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include "searchdevicepage.h"
#include <QMessageBox>
#include "fvp_globals.h"
#include "searchdialog.h"

SearchDevicePage::SearchDevicePage()
{
	ui.setupUi(this);

	deviceModel =  new QStringListModel(this);
	deviceIpStringList = new QStringList();

	deviceIpStringList->append("hello world");
	deviceModel->setStringList(*deviceIpStringList);
	ui.listView_device->setModel(deviceModel);
	
	connect(ui.button_searchDevice, SIGNAL(clicked()), this, SLOT(searchDeviceHandle()));
}



int SearchDevicePage::setUiToWaitingStatus()
{
	printf("SearchDevicePage::setUiToWaitingStatus\n");
	return 0;
}

int SearchDevicePage::cleanDeviceQListView()
{
	deviceIpStringList->clear(); 
	return 0;
}

int SearchDevicePage::addDeviceIpStrToQListViewWidget(char *ipaddr_string)
{
	return_val_if_failed(ipaddr_string != NULL, RET_INVALID_PARAMETER);
	deviceIpStringList->append(ipaddr_string);
	deviceModel->setStringList(*deviceIpStringList);
	ui.listView_device->setModel(deviceModel);
	return 0;
}

int SearchDevicePage::displayHintMessagebox(char *message)
{
	return_val_if_failed(message != NULL, RET_INVALID_PARAMETER);
	QMessageBox::information(NULL, "Hint", message, QMessageBox::Yes, QMessageBox::Yes);
	return 0;
}

void SearchDevicePage::searchDeviceHandle()
{	
	controller_search_device(fvp_default_controller(), this);
	
	return;	
}


