//Muaddin include.
#include "settingsdisplay.h"
#include "locationtab.h"
#include "methodstab.h"

//Qt includes.
#include <QSettings>
#include <QPushButton>
#include <QTabWidget>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QEvent>

SettingsDisplay::SettingsDisplay(QWidget *parent, bool CanExit) : QDialog(parent){
    //Creating QSettings.
    MuaddinSettings = new QSettings("Muaddin", "Muaddin", this);

    //Create the GUI.
    CreateButtons();
    CreateTabs();

    //Connect the slots to the signals.
    ConnectEverything();

    //Set the display's properties.
    SetProperties(CanExit);

    //Set the values and text of the settings to the previous version.
    SetValues();
    SetText();
}

void SettingsDisplay::CreateButtons(){
    //Creating buttons and set it's geometry.
    SetButton = new QPushButton(this);
    CancelButton = new QPushButton(this);
    SetButton->setGeometry(245, 283, 80, 22);
    CancelButton->setGeometry(330, 283, 80, 22);
}

void SettingsDisplay::CreateTabs(){
    //Creating the location tab.
    Locationtab = new LocationTab(this);

    //Creating the methods tab.
    Methodstab = new MethodsTab(this);

    //Creating and setting up the tabswidget.
    SettingsTabsWidget = new QTabWidget(this);
    SettingsTabsWidget->setGeometry(10, 10, 400, 263);
    SettingsTabsWidget->addTab(Locationtab, "");
    SettingsTabsWidget->addTab(Methodstab, "");
}

void SettingsDisplay::ConnectEverything(){
    //Connecting slots and signals.
    connect(SetButton, &QPushButton::released, this, &SettingsDisplay::on_Set);
    connect(CancelButton, &QPushButton::released, this, &SettingsDisplay::close);
}

void SettingsDisplay::on_Set(){
    //Saving the values into QSettings and then closing the display.
    MuaddinSettings->beginGroup("Settings");
    MuaddinSettings->setValue("Latitude", Locationtab->LatitudeSpinBox->value());
    MuaddinSettings->setValue("Longitude", Locationtab->LongitudeSpinBox->value());
    MuaddinSettings->setValue("Time Zone", Locationtab->TimeZoneSpinBox->value());
    MuaddinSettings->setValue("DayLight", Locationtab->DayLightCheckBox->isChecked());
    MuaddinSettings->setValue("Method", Methodstab->MethodsComboBox->currentIndex());
    MuaddinSettings->setValue("Custom Fajr Angle", Methodstab->CustomFajrSpinBox->value());
    MuaddinSettings->setValue("Custom Isha Angle", Methodstab->CustomIshaSpinBox->value());
    MuaddinSettings->setValue("Juristic Method", Methodstab->JuristicComboBox->currentIndex());
    MuaddinSettings->setValue("Extreme Method", Methodstab->ExtremeMethodsComboBox->currentIndex());
    MuaddinSettings->endGroup();
    this->close();
}

void SettingsDisplay::SetProperties(bool CanExit){
    //Setting up display.
    SettingsDisplay::setFixedSize(420, 315);
    SettingsDisplay::setWindowModality(Qt::WindowModal);

    //Checking to see if the display can close.
    if(CanExit){
        SettingsDisplay::setWindowFlags(Qt::WindowCloseButtonHint);
    }else{
        SettingsDisplay::setWindowFlags(Qt::WindowTitleHint);
        CancelButton->setEnabled(false);
    }
}

void SettingsDisplay::SetValues(){
    //Setting values using QSettings.
    MuaddinSettings->beginGroup("Settings");
    Locationtab->LatitudeSpinBox->setValue(MuaddinSettings->value("Latitude", 0.0).toDouble());
    Locationtab->LongitudeSpinBox->setValue(MuaddinSettings->value("Longitude", 0.0).toDouble());
    Locationtab->TimeZoneSpinBox->setValue(MuaddinSettings->value("Time Zone", 0.0).toDouble());
    Locationtab->DayLightCheckBox->setChecked(MuaddinSettings->value("DayLight", false).toBool());
    Methodstab->MethodsComboBox->setCurrentIndex(MuaddinSettings->value("Method", 0).toInt());
    Methodstab->CustomFajrSpinBox->setValue(MuaddinSettings->value("Custom Fajr Angle", -0.001).toDouble());
    Methodstab->CustomIshaSpinBox->setValue(MuaddinSettings->value("Custom Isha Angle", -0.001).toDouble());
    Methodstab->JuristicComboBox->setCurrentIndex(MuaddinSettings->value("Juristic Method", 0).toInt());
    Methodstab->ExtremeMethodsComboBox->setCurrentIndex(MuaddinSettings->value("Extreme Method", 0).toInt());
    MuaddinSettings->endGroup();
}

void SettingsDisplay::SetText(){
    //Setting texts.
    SettingsDisplay::setWindowTitle(tr("Calculations"));

    SetButton->setText(tr("Set"));
    CancelButton->setText(tr("Cancel"));

    SettingsTabsWidget->setTabText(0, tr("Location"));
    SettingsTabsWidget->setTabText(1, tr("Methods"));
}


void SettingsDisplay::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        SetText();
    }else{
        QWidget::changeEvent(event);
    }
}
