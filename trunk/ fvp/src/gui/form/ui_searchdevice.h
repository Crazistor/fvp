/********************************************************************************
** Form generated from reading ui file 'searchdevice.ui'
**
** Created: Wed Mar 23 18:04:22 2011
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SEARCHDEVICE_H
#define UI_SEARCHDEVICE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_searchDevice
{
public:
    QWidget *verticalLayout_3;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QListView *listView_device;
    QPushButton *button_searchDevice;
    QVBoxLayout *vboxLayout2;
    QPushButton *button_stopPlay;
    QPushButton *button_livePlay;
    QPushButton *button_switchChannel;

    void setupUi(QWidget *searchDevice)
    {
        if (searchDevice->objectName().isEmpty())
            searchDevice->setObjectName(QString::fromUtf8("searchDevice"));
        searchDevice->resize(180, 400);
        verticalLayout_3 = new QWidget(searchDevice);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setGeometry(QRect(10, 40, 161, 321));
        vboxLayout = new QVBoxLayout(verticalLayout_3);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        listView_device = new QListView(verticalLayout_3);
        listView_device->setObjectName(QString::fromUtf8("listView_device"));
        listView_device->setMovement(QListView::Static);
        listView_device->setViewMode(QListView::IconMode);

        vboxLayout1->addWidget(listView_device);

        button_searchDevice = new QPushButton(verticalLayout_3);
        button_searchDevice->setObjectName(QString::fromUtf8("button_searchDevice"));

        vboxLayout1->addWidget(button_searchDevice);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        button_stopPlay = new QPushButton(verticalLayout_3);
        button_stopPlay->setObjectName(QString::fromUtf8("button_stopPlay"));

        vboxLayout2->addWidget(button_stopPlay);

        button_livePlay = new QPushButton(verticalLayout_3);
        button_livePlay->setObjectName(QString::fromUtf8("button_livePlay"));

        vboxLayout2->addWidget(button_livePlay);

        button_switchChannel = new QPushButton(verticalLayout_3);
        button_switchChannel->setObjectName(QString::fromUtf8("button_switchChannel"));

        vboxLayout2->addWidget(button_switchChannel);


        vboxLayout1->addLayout(vboxLayout2);


        vboxLayout->addLayout(vboxLayout1);


        retranslateUi(searchDevice);

        QMetaObject::connectSlotsByName(searchDevice);
    } // setupUi

    void retranslateUi(QWidget *searchDevice)
    {
        searchDevice->setWindowTitle(QApplication::translate("searchDevice", "Form", 0, QApplication::UnicodeUTF8));
        button_searchDevice->setText(QApplication::translate("searchDevice", "Search Device", 0, QApplication::UnicodeUTF8));
        button_stopPlay->setText(QApplication::translate("searchDevice", "Stop Play", 0, QApplication::UnicodeUTF8));
        button_livePlay->setText(QApplication::translate("searchDevice", "Live Play", 0, QApplication::UnicodeUTF8));
        button_switchChannel->setText(QApplication::translate("searchDevice", "Switch Channel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(searchDevice);
    } // retranslateUi

};

namespace Ui {
    class searchDevice: public Ui_searchDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDEVICE_H
