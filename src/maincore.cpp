//Muaddin includes.
#include "maincore.h"
#include "aboutdisplay.h"
#include "settingsdisplay.h"
#include "maindisplay.h"
#include "mainmenubar.h"
#include "languagemenu.h"
#include "athangroup.h"
#include "prayergroup.h"
#include "systemtraymenu.h"
#include "timecore.h"

//QT includes.
#include <QSettings>
#include <QInputDialog>
#include <QTimer>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QSystemTrayIcon>
#include <QThread>
#include <QMediaPlayer>
#include <QFileDialog>

MainCore::MainCore(QObject *parent) : QObject(parent){
    //Creating QSettings.
    MuaddinSettings = new QSettings("Muaddin", "Muaddin", this);

    //Creating QTranslators pointers.
    MuaddinTranslator = new QTranslator(this);

    //Getting layout direction.
    LayoutDirectionString = tr("LTR");

    //Check to see if there are any properties saved in settings.
    CheckVariables();

    //Create the main display.
    CreateMainDisplay();

    //Checking if there is a system tray.
    if(QSystemTrayIcon::isSystemTrayAvailable()){
        //Create system tray icon.
        CreateSystemTrayIcon();
    }

    //Create time core.
    CreateTimeCore();

    //Create the player.
    CreatePlayer();
}

void MainCore::CheckVariables(){
    MuaddinSettings->beginGroup("Settings");
    //Getting a boolean if there is any latitude saved.
    bool CalculationVariablesExist = MuaddinSettings->value("Latitude").isNull();
    MuaddinSettings->endGroup();

    //Checking if there any Calculation variables saved.
    if(CalculationVariablesExist){
        //Create settings display.
        CreateSettingsDisplay(true);
    }
}

void MainCore::GetAndSaveLanguage(QString Language){
    //Getting the language the users wants.
    bool OKPressed = true;
    /*Language = QInputDialog::getItem(NULL, "", ":", QStringList(), 0, false, &OKPressed)
                            .remove(QRegExp("*(", Qt::CaseSensitive, QRegExp::Wildcard)).remove(')');*/

    //Checking if ok button was pressed.
    if(OKPressed){
        //Saving the languages.
        MuaddinSettings->beginGroup("Settings");
        MuaddinSettings->setValue("Language", Language);
        MuaddinSettings->endGroup();

        //Update language.
        UpdateTranslations(Language);
    }
}

void MainCore::UpdateTranslations(QString Language){
    //Setting the translation for the program.
    MuaddinTranslator->load("Muaddin_" + Language, ":/translations");
    QApplication::instance()->installTranslator(MuaddinTranslator);

    //Setting layout direction.
    SetGUILayoutDirection();
}

void MainCore::SetGUILayoutDirection(){
    //Updating layout direction string.
    LayoutDirectionString = tr("LTR");

    //Setting MainDisplay's layout.
    if(LayoutDirectionString == "LTR"){
        Maindisplay->setLayoutDirection(Qt::LeftToRight);
    }else{
        Maindisplay->setLayoutDirection(Qt::RightToLeft);
    }
}

void MainCore::CreateSettingsDisplay(bool CanExit){
    //Creating the settings display.
    SettingsDisplay Settingsdisplay(0, !CanExit);
    if(LayoutDirectionString == "LTR"){
        Settingsdisplay.setLayoutDirection(Qt::LeftToRight);
    }else{
        Settingsdisplay.setLayoutDirection(Qt::RightToLeft);
    }
    Settingsdisplay.setModal(true);
    Settingsdisplay.exec();
    emit UpdateEverything();
}

void MainCore::CreateAboutDisplay(bool){
    //Creating the About Display.
    AboutDisplay Aboutdisplay;
    if(LayoutDirectionString == "LTR"){
        Aboutdisplay.setLayoutDirection(Qt::LeftToRight);
    }else{
        Aboutdisplay.setLayoutDirection(Qt::RightToLeft);
    }
    Aboutdisplay.setModal(true);
    Aboutdisplay.exec();
}

void MainCore::CreateMainDisplay(){
    //Creating Main display.
    Maindisplay = new MainDisplay();

    //Set preferences.
    SetMainDisplayPreferences();
    SetGUILayoutDirection();

    //Setting the event filter.
    Maindisplay->installEventFilter(this);

    //Connecting the signals and slots of Maindisplay.
    connect(Maindisplay->MenuBar->SettingsAction, &QAction::triggered, this, &MainCore::CreateSettingsDisplay);
    connect(Maindisplay->MenuBar->Languagemenu, &LanguageMenu::UpdateLanguage, this, &MainCore::GetAndSaveLanguage);
    connect(Maindisplay->MenuBar->StartupAction, &QAction::triggered, this, &MainCore::on_StartupAction);
    connect(Maindisplay->MenuBar->NoAthanAction, &QAction::triggered, this, &MainCore::SetToNoAthan);
    connect(Maindisplay->MenuBar->DefaultAthanAction, &QAction::triggered, this, &MainCore::SetToDefaultAthan);
    connect(Maindisplay->MenuBar->CustomAthanAction, &QAction::triggered, this, &MainCore::SetToCustomAthan);
    connect(Maindisplay->MenuBar->AboutAction, &QAction::triggered, this, &MainCore::CreateAboutDisplay);

    connect(Maindisplay->Athangroup->StopButton, &QPushButton::released, this, &MainCore::Stop);
    connect(Maindisplay->Athangroup->PlayButton, &QPushButton::released, this, &MainCore::Play);
    connect(Maindisplay->Athangroup->VolumeSlider, &QSlider::valueChanged, this, &MainCore::SetVolume);

    connect(Maindisplay, &MainDisplay::StopTimeThread, this, &MainCore::StopTimeThread);
    connect(Maindisplay, &MainDisplay::SavePreferences, this, &MainCore::SaveMainDisplayPreferences);
}

void MainCore::SetMainDisplayPreferences(){
    MuaddinSettings->beginGroup("Settings");
    //Setting saved view mode.
    if(MuaddinSettings->value("View Mode", "Default").toString() == "Default"){
        Maindisplay->SetViewToDefault();
    }else{
        Maindisplay->SetViewToDefault();
    }

    //Setting the location of the window.
    if(!MuaddinSettings->value("Position").isNull()){
        Maindisplay->move(MuaddinSettings->value("Position").toPoint());
    }

    //Setting volume.
    Maindisplay->Athangroup->VolumeSlider->setValue(MuaddinSettings->value("Volume", 50).toInt());

    //Setting visibility.
    Maindisplay->setVisible(MuaddinSettings->value("Visibility", true).toBool());

    //Setting the athan menu and startup values.
    QString Url = MuaddinSettings->value("Athan", "Default").toString();
    bool StartonStartup = MuaddinSettings->value("Start on Startup", true).toBool();
    MuaddinSettings->endGroup();

    if(Url == "Default"){
        Maindisplay->MenuBar->DefaultAthanAction->setChecked(true);
    }else if(Url == "No Athan"){
        Maindisplay->MenuBar->NoAthanAction->setChecked(true);
    }else{
        Maindisplay->MenuBar->CustomAthanAction->setChecked(true);
    }

    Maindisplay->MenuBar->StartupAction->setChecked(StartonStartup);
}

void MainCore::on_StartupAction(bool Startup){
    //Saving if the user wants to start on startup or not.
    MuaddinSettings->beginGroup("Settings");
    MuaddinSettings->setValue("Start on Startup", Startup);
    MuaddinSettings->endGroup();
}

void MainCore::SaveMainDisplayPreferences(){
    //Saving the user preferences.
    MuaddinSettings->beginGroup("Settings");
    MuaddinSettings->setValue("Position", Maindisplay->geometry());
    MuaddinSettings->setValue("View Mode", (Maindisplay->MenuBar->DefaultAction->isChecked())? "Default": "Minimal");
    MuaddinSettings->setValue("Volume", Maindisplay->Athangroup->VolumeSlider->value());
    MuaddinSettings->setValue("Visibility", Maindisplay->isVisible());
    MuaddinSettings->endGroup();
}

void MainCore::CreateSystemTrayIcon(){
    //Creating the system tray icon.
    SystemTray = new QSystemTrayIcon(QIcon(":/res/Icon.svg"), Maindisplay);

    //Calling the creation of the menu.
    CreateSystemTrayMenu();
}

void MainCore::CreateSystemTrayMenu(){
    //Creating the menu of the system tray.
    TrayMenu = new SystemTrayMenu(Maindisplay);
    SystemTray->setContextMenu(TrayMenu);

    //Connecting the actions to the slots.
    connect(TrayMenu->GithubAction, &QAction::triggered, Maindisplay->MenuBar, &MainMenuBar::on_GithubAction);
    connect(TrayMenu->AboutAction, &QAction::triggered, this, &MainCore::CreateAboutDisplay);

    connect(TrayMenu->DefaultAction, &QAction::triggered, this, &MainCore::on_TrayDefaultAction);
    connect(TrayMenu->MinimalAction, &QAction::triggered, this, &MainCore::on_TrayMinimalAction);

    connect(TrayMenu->ExitAction, &QAction::triggered, this, &MainCore::Quitting);
}

void MainCore::on_TrayDefaultAction(bool){
    //Making the display visible then changing the view if it's minimal.
    Maindisplay->setVisible(true);
    if(!Maindisplay->MenuBar->DefaultAction->isChecked()){
        Maindisplay->SetViewToDefault();
    }
}

void MainCore::on_TrayMinimalAction(bool){
    //Making the display visible then changing the view if it's default.
    Maindisplay->setVisible(true);
    if(!Maindisplay->MenuBar->MinimalAction->isChecked()){
        Maindisplay->SetViewToMinimal();
    }
}

void MainCore::SetTrayText(QString NextPrayer){
    //Setting the text for the system tray.
    SystemTray->setToolTip(NextPrayer);
}

void MainCore::SystemTrayActivated(QSystemTrayIcon::ActivationReason Reason){
    //Checks if the icon was double clicked then making the main display visible.
    if(Reason == QSystemTrayIcon::DoubleClick){Maindisplay->show();}
}

void MainCore::CreateTimeCore(){
    //Creating the time core in a thread.
    TimeCoreThread = new QThread(Maindisplay);
    Timecore = new TimeCore(0, TimeCoreThread);
    Timecore->moveToThread(TimeCoreThread);

    //Connecting TimeCore.
    connect(TimeCoreThread, &QThread::finished, Timecore, &QObject::deleteLater);

    connect(this, &MainCore::UpdateEverything, Timecore, &TimeCore::UpdateEverything);
    connect(this, &MainCore::UpdateLanguage, Timecore, &TimeCore::SetText);

    connect(Timecore, &TimeCore::UpdateTime, Maindisplay, &MainDisplay::UpdateTimeLabel);
    connect(Timecore, &TimeCore::UpdateDate, Maindisplay, &MainDisplay::UpdateDateLabel);
    connect(Timecore, &TimeCore::UpdateNextPrayer, Maindisplay, &MainDisplay::UpdateNextPrayerLabel);
    connect(Timecore, &TimeCore::UpdateNextPrayer, this, &MainCore::SetTrayText);
    connect(Timecore, &TimeCore::UpdateFajr, Maindisplay->Prayergroup, &PrayerGroup::UpdateFajrLabel);
    connect(Timecore, &TimeCore::UpdateSunRise, Maindisplay->Prayergroup, &PrayerGroup::UpdateSunRiseLabel);
    connect(Timecore, &TimeCore::UpdateDhuhr, Maindisplay->Prayergroup, &PrayerGroup::UpdateDhuhrLabel);
    connect(Timecore, &TimeCore::UpdateAsr, Maindisplay->Prayergroup, &PrayerGroup::UpdateAsrLabel);
    connect(Timecore, &TimeCore::UpdateMaghrib, Maindisplay->Prayergroup, &PrayerGroup::UpdateMaghribLabel);
    connect(Timecore, &TimeCore::UpdateIsha, Maindisplay->Prayergroup, &PrayerGroup::UpdateIshaLabel);
    connect(Timecore, &TimeCore::UpdateCompass, Maindisplay, &MainDisplay::UpdateCompass);

    connect(Timecore, &TimeCore::Play, this, &MainCore::Play);
}

void MainCore::StopTimeThread(){
    //Stopping the Time Thread.
    TimeCoreThread->quit();
    if(!TimeCoreThread->wait(3000)){
        TimeCoreThread->terminate();
        TimeCoreThread->wait();
    }
}

void MainCore::CreatePlayer(){
    //Creating the player to play mp3.
    Player = new QMediaPlayer(this);
    Player->setAudioRole(QAudio::MusicRole);

    //Setting the volume and media saved.
    MuaddinSettings->beginGroup("Settings");
    Player->setVolume(MuaddinSettings->value("Volume").toInt());
    MuaddinSettings->endGroup();

    //Setting the athan.
    SetMedia();
}

void MainCore::Stop(){
    //Stops athan.
    Player->stop();
}

void MainCore::Play(){
    //Plays athan if NoAthanAction is not ticked.
    if(!Maindisplay->MenuBar->NoAthanAction->isChecked()){
        Player->play();
        if(!Maindisplay->isVisible()){Maindisplay->setVisible(true);}
    }
}

void MainCore::SetVolume(int NewVolume){
    //Setting the player's volume.
    Player->setVolume(NewVolume);
}

void MainCore::SetMedia(){
    //Setting up Athans and volume.
    MuaddinSettings->beginGroup("Settings");
    QString Url = MuaddinSettings->value("Athan", "Default").toString();
    int Volume = MuaddinSettings->value("Volume", 50).toInt();
    MuaddinSettings->endGroup();
    if(Url == "Default"){
        SetToDefaultAthan(true);
    }else if(Url == "No Athan"){
        SetToNoAthan(true);
    }else{
        Player->setMedia(QUrl::fromLocalFile(Url));
    }

    Player->setVolume(Volume);
}

void MainCore::SetToNoAthan(bool Checked){
    //Checking to see if the user has clicked the action while ticked.
    if(Checked){
        //The user has not so athan is turned off.
        Maindisplay->MenuBar->DefaultAthanAction->setChecked(false);
        Maindisplay->MenuBar->CustomAthanAction->setChecked(false);
        MuaddinSettings->beginGroup("Settings");
        MuaddinSettings->setValue("Athan", "No Athan");
        MuaddinSettings->endGroup();
    }else{
        Maindisplay->MenuBar->NoAthanAction->setChecked(false);
    }
}

void MainCore::SetToDefaultAthan(bool Checked){
    //Checking to see if the user has clicked the action while ticked.
    if(Checked){
        //The user has not so athan is set to default.
        Maindisplay->MenuBar->NoAthanAction->setChecked(false);
        Maindisplay->MenuBar->CustomAthanAction->setChecked(false);
        MuaddinSettings->beginGroup("Settings");
        Player->setMedia(QUrl("qrc:/res/Athan.mp3"));
        MuaddinSettings->setValue("Athan", "Default");
        MuaddinSettings->endGroup();
    }else{
        Maindisplay->MenuBar->DefaultAthanAction->setChecked(false);
    }
}

void MainCore::SetToCustomAthan(bool Checked){
    //Checking to see if the user has clicked the action while ticked.
    if(Checked){
        //The user has not so athan is now what the user chooses.
        QString Url = QFileDialog::getOpenFileName(NULL, "MP3", QDir::homePath(), "MP3( *.mp3)");
        if(Url != NULL){
            Maindisplay->MenuBar->NoAthanAction->setChecked(false);
            Maindisplay->MenuBar->DefaultAthanAction->setChecked(false);
            MuaddinSettings->beginGroup("Settings");
            Player->setMedia(QUrl::fromLocalFile(Url));
            MuaddinSettings->setValue("Athan", Url);
            MuaddinSettings->endGroup();
        }else{
            Maindisplay->MenuBar->CustomAthanAction->setChecked(false);
        }
    }else{
        Maindisplay->MenuBar->CustomAthanAction->setChecked(false);
    }
}

bool MainCore::eventFilter(QObject *watched, QEvent *event){
    if(watched == Maindisplay && event->type() == QEvent::Close){
        //Stopping the display from closing if the close button is pressed.
        #ifdef Q_OS_OSX
            if (!event->spontaneous() || !Maindisplay->isVisible()) {return false;}
        #endif
            if (SystemTray->isVisible()) {
                Maindisplay->hide();
                event->ignore();
            }
        return true;
    }else if(watched == Maindisplay && event->type() == QEvent::LanguageChange){
        //Updating MainCore and TimeCore's text.
        emit UpdateLanguage();
        emit UpdateEverything();
        return false;
    }else{
        return false;
    }
}

void MainCore::Start(){
    //Starts main program.
    SystemTray->show();
    Maindisplay->show();
    emit UpdateEverything();
    TimeCoreThread->start();
}

void MainCore::Quitting(bool){
    //Disconnecting TimeCore and closing the program.
    disconnect(Timecore, 0, 0, 0);
    Maindisplay->deleteLater();
    QApplication::quit();
}
