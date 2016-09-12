//Muaddin include.
#include "locationtab.h"

//Qt includes.
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QEvent>

LocationTab::LocationTab(QWidget *parent) : QWidget(parent){
    //Creating the tab for location and time and setting up it's layout.
    LocationBox = new QVBoxLayout();
    LocationBox->setAlignment(Qt::AlignHCenter|Qt::AlignJustify);

    //Adding the groups into the tab.
    LocationBox->addWidget(CreateCoordinatesGroup());
    LocationBox->addWidget(CreateTimeGroup());
    LocationTab::setLayout(LocationBox);

    //Set GUI texts.
    SetText();
}

QGroupBox *LocationTab::CreateCoordinatesGroup(){
    //Creating a group for the geographic coordinate system and it's layout.
    CoordinatesGroup = new QGroupBox();
    CoordinatesLayout = new QFormLayout();

    //Creating the labels and the fields.
    LatitudeLabel = new QLabel();
    LatitudeSpinBox = new QDoubleSpinBox();
    LatitudeSpinBox->setRange(-90.0, 90.0);
    LatitudeSpinBox->setSingleStep(0.0001);
    LatitudeSpinBox->setDecimals(4);
    LongitudeLabel = new QLabel();
    LongitudeSpinBox = new QDoubleSpinBox();
    LongitudeSpinBox->setRange(-180.0, 180.0);
    LongitudeSpinBox->setSingleStep(0.0001);
    LongitudeSpinBox->setDecimals(4);

    //Adding the widget to the layout and the layout to the group.
    CoordinatesLayout->addRow(LatitudeLabel, LatitudeSpinBox);
    CoordinatesLayout->addRow(LongitudeLabel, LongitudeSpinBox);
    CoordinatesLayout->setVerticalSpacing(15);
    CoordinatesGroup->setLayout(CoordinatesLayout);
    //The return is to easily add it to the tab.
    return CoordinatesGroup;
}

QGroupBox * LocationTab::CreateTimeGroup(){
    //Creating the time group and it's layout.
    TimeGroup = new QGroupBox();
    TimeLayout = new QFormLayout();

    //Creating the label for the time zone and the field.
    TimeZoneLabel = new QLabel();
    TimeZoneSpinBox = new QDoubleSpinBox();
    TimeZoneSpinBox->setRange(-12.0, 14.0);
    TimeZoneSpinBox->setSingleStep(0.05);
    //Creating the check box.
    DayLightCheckBox = new QCheckBox();

    //Adding the widgets to the layout and the layout to the group.
    TimeLayout->addRow(TimeZoneLabel, TimeZoneSpinBox);
    TimeLayout->addRow(DayLightCheckBox);
    TimeLayout->setVerticalSpacing(15);
    TimeGroup->setLayout(TimeLayout);
    //Returning to add to the tab.
    return TimeGroup;
}

void LocationTab::SetText(){
    //Setting text.
    CoordinatesGroup->setTitle(tr("Coordinates"));
    LatitudeLabel->setText("<font size=4>"+tr("Latitude:(degrees and north is positive)")+"</font>");
    LongitudeLabel->setText("<font size=4>"+tr("Longitude:(degrees and east is positive)")+"</font>");

    TimeGroup->setTitle(tr("Time"));
    TimeZoneLabel->setText("<font size=4>"+tr("Time Zone:(5.75 is +05:45 UTC)")+"</font>");
    DayLightCheckBox->setText(tr("Use Daylight Savings Time"));
}

void LocationTab::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        SetText();
    }else{
        QWidget::changeEvent(event);
    }
}
