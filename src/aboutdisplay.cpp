//Muaddin include.
#include "aboutdisplay.h"

//Qt includes.
#include <QSvgWidget>
#include <QLabel>
#include <QEvent>

AboutDisplay::AboutDisplay(QWidget *parent) : QDialog(parent){
    //Set up display.
    SetUpDisplay();

    //Create GUI.
    CreateImage();
    CreateText();

    //Set GUI text.
    SetText();
}

void AboutDisplay::SetUpDisplay(){
    //Setting up the display.
    AboutDisplay::setFixedSize(400, 225);
    AboutDisplay::setWindowFlags(Qt::WindowCloseButtonHint);
}

void AboutDisplay::CreateImage(){
    //Creating the svg image.
    SVGWidget = new QSvgWidget(":/res/Icon.svg", this);
    SVGWidget->setGeometry(10, 20, 150, 150);
}

void AboutDisplay::CreateText(){
    //Creating labels and setting the text of the labels and properties.
    AboutLabel = new QLabel(this);
    AboutLabel->setAlignment(Qt::AlignHCenter|Qt::AlignJustify);
    AboutLabel->setWordWrap(true);
    AboutLabel->setGeometry(170, 20, 220, 150);

    DonationLabel = new QLabel(this);
    DonationLabel->setAlignment(Qt::AlignCenter);
    DonationLabel->setGeometry(10, 180, 380, 20);
}

void AboutDisplay::SetText(){
    //Setting text.
    AboutDisplay::setWindowTitle(tr("About"));

    AboutLabel->setText("<p><font size=8><b>Muaddin</b></font></p>"
                        ""
                        "<font size=5><p>"+tr("A multi-platform athan program created in QT.")+
                        "</p><p>"+tr("The code can be found on Github.")+"</p></font>");

    DonationLabel->setText("<font size=4>"+tr("Donate to Bitcoin wallet: ")+"18KxNg7UHsNqjAXdkGxJjFfdX8Fm9ArYwR"+"</font>");
}

void AboutDisplay::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        SetText();
    }else{
        QWidget::changeEvent(event);
    }
}
