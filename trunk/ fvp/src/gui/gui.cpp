#include <QtGui>
#include <QWSServer>
#include <QApplication>
#include "configdialog.h"
#include "gui.h"


void init_gui(int argc, char *argv[])
{
	QBrush *BackColor = new QBrush(QColor(255,0,0)); 
	QWSServer::setBackground(*BackColor); 

	Q_INIT_RESOURCE(configdialog);
	QApplication app(argc, argv);
	ConfigDialog dialog;
	dialog.exec();
 	
	return;
}


