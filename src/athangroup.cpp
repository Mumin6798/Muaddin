//Muaddin include.
#include "athangroup.h"

//Qt includes.
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>

AthanGroup::AthanGroup(QWidget *parent) : QGroupBox(parent){
    //Create and setting up the group layout.
    AthanBox = new QHBoxLayout();
    AthanBox->setAlignment(Qt::AlignVCenter|Qt::AlignJustify);
    AthanBox->setSpacing(10);

    //Create the widgets.
    CreateWidget();

    //Set the group layout.
    AthanGroup::setLayout(AthanBox);
}

void AthanGroup::CreateWidget(){
    //Creating the buttons.
    StopButton = new QPushButton(QIcon(":/res/Stop.svg"), "");
    PlayButton = new QPushButton(QIcon(":/res/Play.svg"), "");

    //Creating the slider.
    VolumeSlider = new QSlider(Qt::Horizontal);
    VolumeSlider->setRange(0, 100);

    //Adding the widgets to the layout.
    AthanBox->addWidget(StopButton);
    AthanBox->addWidget(PlayButton);
    AthanBox->addWidget(VolumeSlider);
}
