/*
 * File: fvp_gui.cpp
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

#include <QtGui>
#include <QWSServer>
#include <QApplication>
#include "fvp_gui.h"


static int set_osd_bg_color()
{
	QBrush BackColor = QBrush(QColor(255,0,0)); 
	QWSServer::setBackground(BackColor); 
	
	return 0;
}


void init_gui(int argc, char *argv[])
{
	set_osd_bg_color();

	Q_INIT_RESOURCE(configdialog);
	QApplication app(argc, argv);
#if 0
	ConfigDialog dialog;
	dialog.exec();
#endif 
	SearchDevicePage searchdevice_dialog;
	ConfigDialog dialog;

//hile(1)
	{
		searchdevice_dialog.show();
		app.exec();
 //dialog.exec();
	}
	return;
}

