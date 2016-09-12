#ifndef SETTINGSDISPLAY_H
#define SETTINGSDISPLAY_H

//Qt include.
#include <QDialog>

//Muaddin forward declarations.
class LocationTab;
class MethodsTab;

//Qt forward declarations.
class QSettings;
class QPushButton;
class QTabWidget;

class SettingsDisplay : public QDialog{
    Q_OBJECT

public:
    explicit SettingsDisplay(QWidget *parent = 0, bool CanExit = true);

private slots:
    void on_Set();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    //Functions.
    void CreateButtons();

    void CreateTabs();

    void ConnectEverything();

    void SetProperties(bool CanExit);
    void SetValues();
    void SetText();

    //Pointers.
    QSettings *MuaddinSettings;

    QPushButton *SetButton;
    QPushButton *CancelButton;

    LocationTab *Locationtab;
    MethodsTab *Methodstab;
    QTabWidget *SettingsTabsWidget;

};

#endif
