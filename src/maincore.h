#ifndef MAINCORE_H
#define MAINCORE_H

//QT includes.
#include <QObject>
#include <QSystemTrayIcon>

//Muaddin forward declarations.
class MainDisplay;
class SystemTrayMenu;
class TimeCore;

//QT forward declarations.
class QSettings;
class QTranslator;
class QThread;
class QMediaPlayer;

class MainCore : public QObject{
    Q_OBJECT

public:
    explicit MainCore(QObject *parent = 0);

    void Start();

signals:
    void UpdateEverything();
    void UpdateLanguage();

private slots:
    void CreateSettingsDisplay(bool CanExit);

    void CreateAboutDisplay(bool);

    void GetAndSaveLanguage(QString Language);

    void SetMainDisplayPreferences();
    void on_StartupAction(bool Startup);
    void SaveMainDisplayPreferences();

    void on_TrayDefaultAction(bool);
    void on_TrayMinimalAction(bool);
    void SetTrayText(QString NextPrayer);
    void SystemTrayActivated(QSystemTrayIcon::ActivationReason Reason);

    void StopTimeThread();

    void Stop();
    void Play();
    void SetVolume(int NewVolume);
    void SetToNoAthan(bool Checked);
    void SetToDefaultAthan(bool Checked);
    void SetToCustomAthan(bool Checked);

    void Quitting(bool);

private:
    //Functions.
    void CheckVariables();
    void UpdateTranslations(QString Language);
    void SetGUILayoutDirection();

    void CreateMainDisplay();

    void CreateSystemTrayIcon();
    void CreateSystemTrayMenu();

    void CreateTimeCore();

    void CreatePlayer();
    void SetMedia();

    bool eventFilter(QObject *watched, QEvent *event);

    //Variable.
    QString LayoutDirectionString;

    //Pointers.
    QSettings *MuaddinSettings;
    QTranslator *MuaddinTranslator;

    MainDisplay *Maindisplay;

    SystemTrayMenu *TrayMenu;
    QSystemTrayIcon *SystemTray;

    QThread *TimeCoreThread;
    TimeCore *Timecore;

    QMediaPlayer *Player;
};

#endif
