//Muaddin include.
#include "maincore.h"

//QT includes.
#include <QApplication>
#include <QIcon>
#include <QSettings>
#include <QInputDialog>
#include <QTranslator>
#include <QLibraryInfo>

bool StopRunning = false;

void CheckStartup(int argc, char *argv[]){
    //Checking if the program was called by the system startup.
    QSettings MuaddinSettings("Muaddin", "Muaddin");
    MuaddinSettings.clear();
    MuaddinSettings.beginGroup("Settings");
    if(!MuaddinSettings.value("Start on Startup", true).toBool()){
        for(int i = 0; i < argc; i++){
            if(!strcmp(argv[i], "-Startup")){
                //Closing the program if the user does not want the program on startup.
                StopRunning = true;
            }
        }
    }
    MuaddinSettings.endGroup();
}

QString GetLanguage(){
    //Setting up supported languages and QSettings.
    QSettings MuaddinSettings("Muaddin", "Muaddin");
    QStringList Languages = (QStringList() << "English (en)" << "العربية (ar)");
    QString Language;

    //Checking if language is set.
    MuaddinSettings.beginGroup("Settings");
    if(MuaddinSettings.value("Language").isNull()){
        //Getting language from user.
        bool OkPressed;
        Language = QInputDialog::getItem(NULL, "Language", "Languages:", Languages, 0, false, &OkPressed)
                .remove(QRegExp("*(", Qt::CaseSensitive, QRegExp::Wildcard)).remove(')');
        if(!OkPressed){
            StopRunning = true;
            return "";
        }
    }else{
        Language = MuaddinSettings.value("Language").toString();
    }
    MuaddinSettings.setValue("Language", Language);
    MuaddinSettings.endGroup();
    return Language;
}

int main(int argc, char *argv[]){
    QApplication Application(argc, argv);

    //Setting application properties.
    Application.setStyle("fusion");
    Application.setWindowIcon(QIcon(":/res/Icon.svg"));
    Application.setOrganizationName("Muaddin");
    Application.setApplicationName("Muaddin");
    Application.setApplicationVersion("1.0");

    //Check if the system startup called the program.
    CheckStartup(argc, argv);

    //Checking if program should close.
    if(StopRunning){return 0;}

    //Get language.
    QString Language = GetLanguage();

    //Checking if program should close.
    if(StopRunning){return 0;}

    //Setting the translation for the program.
    QTranslator MuaddinTranslator;
    MuaddinTranslator.load("Muaddin_" + Language, ":/translations");
    Application.installTranslator(&MuaddinTranslator);

    //Create program.
    MainCore Maincore;
    Maincore.Start();

    return Application.exec();
}
