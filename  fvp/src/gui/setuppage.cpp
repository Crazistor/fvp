/*
 * File: setuppage.cpp
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
 * 2011-01-19 zhoumin <dcdcmin@gmail.com> created
 *
 */
 
#include"setuppage.h"
#include"parameter_define.h"
#include"fvp_globals.h"

SetupPage::SetupPage(QWidget *parent)
    : QWidget(parent)
{
	designUiPage();
	syncParameterToPage();
    connect(recordOnRadioButton, SIGNAL(clicked()), this, SLOT(recordOnRadioButtonClickedHandle()));
    connect(recordOffRadioButton, SIGNAL(clicked()), this, SLOT(recordOffRadioButtonClickedHandle()));
	connect(channelComboBox, SIGNAL(currentIndexChanged (int )), this, SLOT(recordChannelChangedHandle()));
}

/*
 * ui page design
 */
void SetupPage::designUiPage()
{
	/*channel switch 1- 4  all*/
	QLabel *channelLabel = new QLabel(tr("Channel:"));
	channelComboBox = new QComboBox;
	channelComboBox->addItem(tr("Channel 1"));
	channelComboBox->addItem(tr("Channel 2"));
	channelComboBox->addItem(tr("Channel 3"));
	channelComboBox->addItem(tr("Channel 4"));
	channelComboBox->addItem(tr("All"));
	
	/*record on off*/
	QLabel *recordStatusLabel = new QLabel(tr("Record:"));
	recordOnRadioButton = new QRadioButton(tr("On"));
	recordOffRadioButton = new QRadioButton(tr("Off"));

	/*record quality*/
	QLabel *recordQualityLabel = new QLabel(tr("Record Quality:"));	
	recordQualityComboBox = new QComboBox;
	recordQualityComboBox->addItem(tr("High"));
	recordQualityComboBox->addItem(tr("Medium"));
	recordQualityComboBox->addItem(tr("General"));
	
    QHBoxLayout *channelSwitchLayout = new QHBoxLayout;
    channelSwitchLayout->addWidget(channelLabel);
    channelSwitchLayout->addWidget(channelComboBox);
	
	QHBoxLayout *recordStatusLayout = new QHBoxLayout;
	recordStatusLayout->addWidget(recordStatusLabel);
	recordStatusLayout->addWidget(recordOnRadioButton);
	recordStatusLayout->addWidget(recordOffRadioButton);

	QHBoxLayout *recordQualityLayout = new QHBoxLayout;
	recordQualityLayout->addWidget(recordQualityLabel);
	recordQualityLayout->addWidget(recordQualityComboBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(channelSwitchLayout);
	mainLayout->addLayout(recordStatusLayout);
	mainLayout->addLayout(recordQualityLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

}

/*
 *  sync parameter to gui setup page
 */
void SetupPage::syncParameterToPage()
{
	printf("syncParameter aaaaaaaaaaaaaaaaa\n");
	SetupParameter *para = NULL;
	int channel = 0;
	
	para = fvp_default_setup_parameter();
	if(para)
	{	
		channel =  channelComboBox->currentIndex();		
		if(channel >= 0)		
		{
			if(para->record_mode.is_chn_open[channel] ==  1)
			{
				recordOnRadioButton->setChecked(true);
				recordOffRadioButton->setChecked(false);
			}
			else
			{
				recordOnRadioButton->setChecked(false);
				recordOffRadioButton->setChecked(true);
			}
		}
	}
	return;
}


/*
 * slot  handle the record  on RadioButton
 */
void SetupPage::recordOnRadioButtonClickedHandle()
{
	int channel = 0;
	SetupParameter *para = NULL;
	
	channel = channelComboBox->currentIndex();
	if(channel >= 0)
	{
		para = fvp_default_setup_parameter();
		return_if_failed(para != NULL);
		if(recordOnRadioButton->isChecked())		
		{
			para->record_mode.is_chn_open[channel] =  1;
		}
	}

	return;
}

/*
 * slot  handle the record  off RadioButton
 */
void SetupPage::recordOffRadioButtonClickedHandle()
{
	int channel = 0;
	SetupParameter *para = NULL;
	
	channel = channelComboBox->currentIndex();
	if(channel >= 0)
	{
		para = fvp_default_setup_parameter();
		return_if_failed(para != NULL);
		if(recordOffRadioButton->isChecked())		
		{
			para->record_mode.is_chn_open[channel] =  0;
		}
	}

	return;
}


/*
 * slot  handle the QComboBox item changed
 */
void SetupPage::recordChannelChangedHandle()
{
	int index = 0;
	SetupParameter *para = NULL;
	
	index = channelComboBox->currentIndex();

	if(index < MAX_CHANNEL_NUM)
	{
		para = fvp_default_setup_parameter();
		return_if_failed(para != NULL);

		if(para->record_mode.is_chn_open[index])
		{
			recordOnRadioButton->setChecked(true);
			recordOffRadioButton->setChecked(false);
		}
		else
		{
			recordOnRadioButton->setChecked(false);
			recordOffRadioButton->setChecked(true);
		}
	}
}

