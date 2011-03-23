#include"searchdialog.h"


SearchDialog::SearchDialog()
{
	searchLabel = new QLabel(this);
	searchLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	searchLabel->setText("Search Dialog...");
	searchLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
	
	setFixedSize(400,200);
	setWindowFlags(Qt::FramelessWindowHint);
}

int SearchDialog::setSearchDialogTextContent(char *textContent)
{
	if(textContent)
	{
		searchLabel->setText(textContent);
	}
	
	return 0;
}







