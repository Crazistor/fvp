#include <QtGui>
#include <QtGui/QDialog> 
#include <QWSServer>
#include "configdialog.h"
#include "pages.h"
#include "setuppage.h"
#include "fvp_globals.h"
#include "controller.h"

ConfigDialog::ConfigDialog()
{
    contentsWidget = new QListWidget;
	QPalette pal = contentsWidget->palette();   
	pal.setBrush(QPalette::Base, QBrush(QPixmap("./images/listwidget_backgroud.png")));

    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(80, 68));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(112);
    contentsWidget->setSpacing(8);

    pagesWidget = new QStackedWidget;
	pagesWidget->addWidget(new SetupPage);
    pagesWidget->addWidget(new UpdatePage);
    pagesWidget->addWidget(new QueryPage);
	pagesWidget->addWidget(new NetworkdPage);

	QPushButton *saveButton  = new QPushButton(tr("Save"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    createIcons();
    contentsWidget->setCurrentRow(0);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveParameter()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
	buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(24);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
	mainLayout->setContentsMargins(12, 36, 6, 12);

    setWindowTitle(tr("Config Dialog"));

	setFixedSize(512,384);
	pal.setBrush(QPalette::Window, QBrush(QPixmap("./images/mainwindow_background.png")));
	setPalette(pal);

  	setWindowFlags(Qt::FramelessWindowHint);
	
}


void ConfigDialog::createIcons()
{
    QListWidgetItem *setupButton = new QListWidgetItem(contentsWidget);
    setupButton->setIcon(QIcon("./images/setup.png"));
    setupButton->setText(tr("Setup"));
    setupButton->setTextAlignment(Qt::AlignHCenter);
    setupButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon("./images/display.png"));
    updateButton->setText(tr("Display"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon("./images/network.png"));
    queryButton->setText(tr("Network"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

/*
 * save parameter
 */
void ConfigDialog::saveParameter()
{
	int ret = RET_FAILED;	
	QWidget *currentPage = NULL;
	
	currentPage = pagesWidget->currentWidget();
	
	ret = controller_save_parameter(fvp_default_controller(), fvp_default_setup_parameter());

	if(ret == RET_OK)
	{
		QMessageBox::warning(NULL, tr("Hint"), tr("Save Parameter success!"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else
	{
		QMessageBox::warning(NULL, tr("Hint"), tr("Save Parameter failed!"), QMessageBox::Yes, QMessageBox::Yes);
	}
	return;	
}
