//Muaddin includes.
#include "mainmenubar.h"
#include "languagemenu.h"

//Qt includes.
#include <QDesktopServices>
#include <QUrl>
#include <QEvent>

MainMenuBar::MainMenuBar(QWidget *parent) : QMenuBar(parent){
    Parent = parent;

    //Create the GUI.
    CreateViewMenu();
    CreateOptionsMenu();
    CreateHelpMenu();

    //Set GUI texts.
    SetText();
}

void MainMenuBar::CreateViewMenu(){
    //Creating the View Menu.
    ViewMenu = new QMenu(this);

    //Creating ViewMenu's actions.
    DefaultAction = new QAction(this);
    MinimalAction = new QAction(this);
    //Making the actions checkable and checking one of them.
    DefaultAction->setCheckable(true);
    MinimalAction->setCheckable(true);
    //Adding the actions to ViewMenu.
    ViewMenu->addAction(DefaultAction);
    ViewMenu->addAction(MinimalAction);

    //Connecting the actions to the slots.
    connect(DefaultAction, &QAction::triggered, this, &MainMenuBar::on_DefaultAction);
    connect(MinimalAction, &QAction::triggered, this, &MainMenuBar::on_MinimalAction);

    //Adding the menu to the menubar.
    MainMenuBar::addMenu(ViewMenu);
}

void MainMenuBar::CreateOptionsMenu(){
    //Creating the Options menu.
    OptionsMenu = new QMenu(this);

    //Creating OptionsMenu's action.
    SettingsAction = new QAction(this);
    Languagemenu = new LanguageMenu(this);
    StartupAction = new QAction(this);
    NoAthanAction = new QAction(this);
    DefaultAthanAction = new QAction(this);
    CustomAthanAction = new QAction(this);
    //Making the actions checkable and checking one of them.
    StartupAction->setCheckable(true);
    NoAthanAction->setCheckable(true);
    DefaultAthanAction->setCheckable(true);
    CustomAthanAction->setCheckable(true);
    //Adding the actions to SettingMenu.
    OptionsMenu->addAction(SettingsAction);
    OptionsMenu->addMenu(Languagemenu);
    OptionsMenu->addAction(StartupAction);
    OptionsMenu->addAction(NoAthanAction);
    OptionsMenu->addAction(DefaultAthanAction);
    OptionsMenu->addAction(CustomAthanAction);

    //Adding the menu to the menubar.
    MainMenuBar::addMenu(OptionsMenu);
}

void MainMenuBar::CreateHelpMenu(){
    //Creating the Help menu.
    HelpMenu = new QMenu(this);

    //Create HelpMenu's action.
    GithubAction = new QAction("Github", this);
    AboutAction = new QAction(this);
    //Adding the actions to HelpMenu.
    HelpMenu->addAction(GithubAction);
    HelpMenu->addAction(AboutAction);

    //Connecting GithubAction to on_GithubAction.
    connect(GithubAction, &QAction::triggered, this, &MainMenuBar::on_GithubAction);

    //Adding the menu to the menubar.
    MainMenuBar::addMenu(HelpMenu);
}

void MainMenuBar::on_DefaultAction(bool){
    //Making the display visible.
    Parent->setVisible(true);
    //Check if the user has click on the action while ticked.
    if(DefaultAction->isChecked()){
        //The window changes to default.
        emit SetViewToDefault();
    }else{
        //The user clicked while it was ticked, so keep it ticked.
        DefaultAction->setChecked(true);
    }
}

void MainMenuBar::on_MinimalAction(bool){
    //Making the display visible.
    Parent->setVisible(true);
    //Check if the user has click on the action while ticked.
    if(MinimalAction->isChecked()){
        //The window changes to minimal.
        emit SetViewToMinimal();
    }else{
        //The user clicked while it was ticked, so keep it ticked.
        MinimalAction->setChecked(true);
    }
}

void MainMenuBar::on_GithubAction(bool){
    //Making the browser open and go to the source code.
    QDesktopServices::openUrl(QUrl("https://github.com/Mumin6798/Muaddin"));
}

void MainMenuBar::SetText(){
    //Setting texts.
    ViewMenu->setTitle(tr("View"));
    DefaultAction->setText(tr("Default"));
    MinimalAction->setText(tr("Minimal"));

    OptionsMenu->setTitle(tr("Options"));
    SettingsAction->setText(tr("Settings"));
    Languagemenu->setTitle(tr("Language"));
    StartupAction->setText(tr("Start on Startup"));
    NoAthanAction->setText(tr("No Athan"));
    DefaultAthanAction->setText(tr("Default Athan"));
    CustomAthanAction->setText(tr("Custom Athan"));

    HelpMenu->setTitle(tr("Help"));
    AboutAction->setText(tr("About"));
}

void MainMenuBar::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        SetText();
    }else{
        QWidget::changeEvent(event);
    }
}
