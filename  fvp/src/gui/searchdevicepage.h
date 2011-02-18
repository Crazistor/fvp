/*
 * File: searchdevicepage.h
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
 
#ifndef SEARCHDEVICEPAGE_H
/*
 * File: searchdevicepage.h
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
#define SEARCHDEVICEPAGE_H


#include <QtGui>
#include <QWidget>
#include "ui_searchdevice.h"

class SearchDevicePage : public QWidget
{
    Q_OBJECT
public:
	SearchDevicePage();
	
//public function
	int setUiToWaitingStatus();
	int displayHintMessagebox(char *message);
	int cleanDeviceQListView();
	int addDeviceIpStrToQListViewWidget(char *ipaddr_string);

public slots:
	void searchDeviceHandle();

private:
	Ui::searchDevice ui;
	QStringListModel *deviceModel;
	QStringList *deviceIpStringList;
		
};




#endif /*SEARCHDEVICEPAGE_H*/

