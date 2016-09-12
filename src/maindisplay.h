#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

//Qt include.
#include <QMainWindow>

//Muaddin forward declarations.
class MainMenuBar;
class PrayerGroup;
class AthanGroup;

//QT forward declarations.
class QLabel;
class QGroupBox;

class MainDisplay : public QMainWindow{
    Q_OBJECT
    friend class MainCore;

public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();

signals:
    void StopTimeThread();

    void SavePreferences();

protected:
    void paintEvent(QPaintEvent *);

    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void SetViewToDefault();
    void SetViewToMinimal();

    void UpdateDateLabel(QString NewDate);
    void UpdateTimeLabel(QString NewTime);
    void UpdateNextPrayerLabel(QString NextPrayer);
    void UpdateCompass(int NewAngle);

private:
    //Functions.
    void CreateMenuBar();

    void CreateCentralWidget();

    void CreatePrayers();

    void CreateLocation();

    void CreateAthan();

    //Variables.
    int Angle = 0;

    //Pointers.
    MainMenuBar *MenuBar;

    QWidget *CentralWidget;
    QLabel *DateLabel;
    QLabel *TimeLabel;
    QLabel *NextPrayerLabel;

    PrayerGroup *Prayergroup;

    QGroupBox *LocationGroup;

    AthanGroup *Athangroup;
};

#endif
