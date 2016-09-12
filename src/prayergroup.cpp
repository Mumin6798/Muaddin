//Muaddin include.
#include "prayergroup.h"

//Qt includes.
#include <QGridLayout>
#include <QLabel>
#include <QEvent>

PrayerGroup::PrayerGroup(QWidget *parent) : QGroupBox(parent){
    //Setting the title of the group and the layout.
    PrayerTimesLayout = new QGridLayout();
    PrayerTimesLayout->setVerticalSpacing(3);
    PrayerTimesLayout->setHorizontalSpacing(20);

    //Create the Labels.
    CreateLabels();

    //Set the layout.
    PrayerGroup::setLayout(PrayerTimesLayout);

    //Set GUI texts.
    SetText();
}

void PrayerGroup::CreateLabels(){
    //Creating the pray times title labels.
    FajrTitleLabel = new QLabel(this);
    SunRiseTitleLabel = new QLabel(this);
    DhuhrTitleLabel = new QLabel(this);
    AsrTitleLabel = new QLabel(this);
    MaghribTitleLabel = new QLabel(this);
    IshaTitleLabel = new QLabel(this);

    //Creating the labels in prayer times.
    FajrLabel = new QLabel(this);
    SunRiseLabel = new QLabel(this);
    DhuhrLabel = new QLabel(this);
    AsrLabel = new QLabel(this);
    MaghribLabel = new QLabel(this);
    IshaLabel = new QLabel(this);

    //Adding the labels to the group.
    PrayerTimesLayout->addWidget(FajrTitleLabel, 0, 0, Qt::AlignRight);
    PrayerTimesLayout->addWidget(FajrLabel, 0, 1, Qt::AlignCenter);
    PrayerTimesLayout->addWidget(SunRiseTitleLabel, 1, 0, Qt::AlignRight);
    PrayerTimesLayout->addWidget(SunRiseLabel, 1, 1, Qt::AlignCenter);
    PrayerTimesLayout->addWidget(DhuhrTitleLabel, 2, 0, Qt::AlignRight);
    PrayerTimesLayout->addWidget(DhuhrLabel, 2, 1, Qt::AlignCenter);
    PrayerTimesLayout->addWidget(AsrTitleLabel, 3, 0, Qt::AlignRight);
    PrayerTimesLayout->addWidget(AsrLabel, 3, 1, Qt::AlignCenter);
    PrayerTimesLayout->addWidget(MaghribTitleLabel, 4, 0, Qt::AlignRight);
    PrayerTimesLayout->addWidget(MaghribLabel, 4, 1, Qt::AlignCenter);
    PrayerTimesLayout->addWidget(IshaTitleLabel, 5, 0, Qt::AlignRight);
    PrayerTimesLayout->addWidget(IshaLabel, 5, 1, Qt::AlignCenter);
}

//Updating the text on the labels.
void PrayerGroup::UpdateFajrLabel(QString NewFajr){
    FajrLabel->setText("<font size=5>"+NewFajr+"</font>");
}

void PrayerGroup::UpdateSunRiseLabel(QString NewSunRise){
    SunRiseLabel->setText("<font size=5>"+NewSunRise+"</font>");
}

void PrayerGroup::UpdateDhuhrLabel(QString NewDhuhr){
    DhuhrLabel->setText("<font size=5>"+NewDhuhr+"</font>");
}

void PrayerGroup::UpdateAsrLabel(QString NewAsr){
    AsrLabel->setText("<font size=5>"+NewAsr+"</font>");
}

void PrayerGroup::UpdateMaghribLabel(QString NewMaghrib){
    MaghribLabel->setText("<font size=5>"+NewMaghrib+"</font>");
}

void PrayerGroup::UpdateIshaLabel(QString NewIsha){
    IshaLabel->setText("<font size=5>"+NewIsha+"</font>");
}

void PrayerGroup::SetText(){
    //Setting texts.
    PrayerGroup::setTitle(tr("Time"));

    FajrTitleLabel->setText("<font size=5>"+tr("Fajr:")+"</font>");
    SunRiseTitleLabel->setText("<font size=5>"+tr("Sunrise:")+"</font>");
    DhuhrTitleLabel->setText("<font size=5>"+tr("Dhuhr:")+"</font>");
    AsrTitleLabel->setText("<font size=5>"+tr("Asr:")+"</font>");
    MaghribTitleLabel->setText("<font size=5>"+tr("Maghrib:")+"</font>");
    IshaTitleLabel->setText("<font size=5>"+tr("Isha:")+"</font>");
}

void PrayerGroup::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        SetText();
    }else{
        QWidget::changeEvent(event);
    }
}
