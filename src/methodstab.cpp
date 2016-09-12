//Muaddin include.
#include "methodstab.h"

//Qt includes.
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QEvent>

MethodsTab::MethodsTab(QWidget *parent) : QWidget(parent){
    //Creating the tab for the methods and setting up it's layout.
    MethodsBox = new QVBoxLayout();
    MethodsBox->setAlignment(Qt::AlignHCenter|Qt::AlignJustify);
    //Adding the groups into the tab.
    MethodsBox->addWidget(CreateMethodsGroup());
    MethodsBox->addWidget(CreateExtremeMethodsGroup());
    MethodsTab::setLayout(MethodsBox);

    //Connect the slots to the signals.
    ConnectEverything();

    //Set GUI text.
    SetText();
}

QGroupBox *MethodsTab::CreateMethodsGroup(){
    //Creating the methods group and it's layout.
    MethodsGroup = new QGroupBox();
    MethodsLayout = new QFormLayout();

    //Creating the methods' labels and the fields.
    MethodsLabel = new QLabel();
    MethodsComboBox = new QComboBox();
    CustomFajrLabel = new QLabel();
    CustomFajrSpinBox = new QDoubleSpinBox();
    CustomFajrSpinBox->setRange(-90.0, -0.001);
    CustomFajrSpinBox->setSingleStep(0.001);
    CustomFajrSpinBox->setDecimals(3);
    CustomFajrSpinBox->setEnabled(false);
    CustomIshaLabel = new QLabel();
    CustomIshaSpinBox = new QDoubleSpinBox();
    CustomIshaSpinBox->setRange(-90.0, -0.001);
    CustomIshaSpinBox->setSingleStep(0.001);
    CustomIshaSpinBox->setDecimals(3);
    CustomIshaSpinBox->setEnabled(false);
    JuristicLabel = new QLabel();
    JuristicComboBox = new QComboBox();

    //Adding the labels and the fields.
    MethodsLayout->addRow(MethodsLabel, MethodsComboBox);
    MethodsLayout->addRow(CustomFajrLabel, CustomFajrSpinBox);
    MethodsLayout->addRow(CustomIshaLabel, CustomIshaSpinBox);
    MethodsLayout->addRow(JuristicLabel, JuristicComboBox);
    MethodsGroup->setLayout(MethodsLayout);
    return MethodsGroup;
}

QGroupBox *MethodsTab::CreateExtremeMethodsGroup(){
    //Creating the group and  the layout.
    ExtremeMethodsGroup = new QGroupBox();
    ExtremeMethodsLayout = new QFormLayout();

    //Creating the label and the field.
    ExtremeMethodsLabel = new QLabel();
    ExtremeMethodsComboBox = new QComboBox();
    //Adding the label and the field the group.
    ExtremeMethodsLayout->addRow(ExtremeMethodsLabel, ExtremeMethodsComboBox);
    ExtremeMethodsGroup->setLayout(ExtremeMethodsLayout);
    return ExtremeMethodsGroup;
}

void MethodsTab::ConnectEverything(){
    //Connecting the MethodsComboBox to the EnableCustomAngles.
    void (QComboBox::* currentIndexChangedOverloadPtr)(int) = &QComboBox::currentIndexChanged;
    connect(MethodsComboBox, currentIndexChangedOverloadPtr, this, &MethodsTab::EnableCustomAngles);
}

void MethodsTab::EnableCustomAngles(int CurrectIndex){
    //Checking to see if the current index is not Custom.
    if(CurrectIndex == 6){
        CustomFajrSpinBox->setEnabled(true);
        CustomIshaSpinBox->setEnabled(true);
    }else{
        CustomFajrSpinBox->setEnabled(false);
        CustomIshaSpinBox->setEnabled(false);
    }
}

void MethodsTab::SetText(){
    //Settings texts.
    MethodsGroup->setTitle(tr("Methods"));
    MethodsLabel->setText("<font size=4>"+tr("Method:")+"</font>");
    MethodsComboBox->clear();
    MethodsComboBox->addItem(tr("University of Islamic Sciences (Karachi)"));
    MethodsComboBox->addItem(tr("Islamic Society of North America (ISNA)"));
    MethodsComboBox->addItem(tr("Muslim World League (MWL)"));
    MethodsComboBox->addItem(tr("Egyptian General Authority of Survey (Egypt)"));
    MethodsComboBox->addItem(tr("Shia Ithna Ashari (Jafari)"));
    MethodsComboBox->addItem(tr("Umm al-Qura (Makkah)"));
    MethodsComboBox->addItem(tr("Custom"));
    CustomFajrLabel->setText("<font size=4>"+tr("Fajr Angle:")+"</font>");
    CustomIshaLabel->setText("<font size=4>"+tr("Isha Angle:")+"</font>");
    JuristicLabel->setText("<font size=4>"+tr("Juristic Method:")+"</font>");
    JuristicComboBox->clear();
    JuristicComboBox->addItem(tr("Standard"));
    JuristicComboBox->addItem(tr("Hanafi"));

    ExtremeMethodsGroup->setTitle(tr("Extreme Day Methods"));
    ExtremeMethodsLabel->setText("<font size=4>"+tr("Extreme Day Method:")+"</font>");
    ExtremeMethodsComboBox->clear();
    ExtremeMethodsComboBox->addItem(tr("Seventh of the Night"));
    ExtremeMethodsComboBox->addItem(tr("Angle"));
    ExtremeMethodsComboBox->addItem(tr("Midnight"));
}

void MethodsTab::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        SetText();
    }else{
        QWidget::changeEvent(event);
    }
}
