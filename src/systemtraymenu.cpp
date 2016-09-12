//Muaddin include.
#include "systemtraymenu.h"

//Qt includes.
#include <QCoreApplication>
#include <QEvent>

SystemTrayMenu::SystemTrayMenu(QWidget *parent) : QMenu(parent){
    //Create the sections.
    CreateHelp();
    SystemTrayMenu::addSeparator();
    CreateView();
    SystemTrayMenu::addSeparator();
    CreateExit();

    //Set GUI texts.
    SetText();
}

void SystemTrayMenu::CreateHelp(){
    //Creating the help section.
    GithubAction = new QAction("Github", this);
    AboutAction = new QAction(this);

    //Adding the actions.
    SystemTrayMenu::addAction(GithubAction);
    SystemTrayMenu::addAction(AboutAction);
}

void SystemTrayMenu::CreateView(){
    //Creating the view section.
    DefaultAction = new QAction(this);
    MinimalAction = new QAction(this);

    //Adding the actions.
    SystemTrayMenu::addAction(DefaultAction);
    SystemTrayMenu::addAction(MinimalAction);
}

void SystemTrayMenu::CreateExit(){
    //Creating the exit section.
    ExitAction = new QAction(this);

    //Adding the action.
    SystemTrayMenu::addAction(ExitAction);
}

void SystemTrayMenu::SetText(){
    //Setting texts.
    AboutAction->setText(tr("About"));

    DefaultAction->setText(tr("Default View"));
    MinimalAction->setText(tr("Minimal View"));

    ExitAction->setText(tr("Exit"));
}

void SystemTrayMenu::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        SetText();
    }else{
        QWidget::changeEvent(event);
    }
}
