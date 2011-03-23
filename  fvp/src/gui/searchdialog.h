#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H


#include <QtGui>

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
	SearchDialog();
	int setSearchDialogTextContent(char *textContent);

private:
	QLabel *searchLabel;
	

};


#endif /*SEARCHDIALOG_H*/
