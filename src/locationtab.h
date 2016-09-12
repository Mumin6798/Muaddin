#ifndef LOCATIONTAB_H
#define LOCATIONTAB_H

//QT includes.
#include <QWidget>

//QT forward declarations.
class QVBoxLayout;
class QGroupBox;
class QFormLayout;
class QLabel;
class QDoubleSpinBox;
class QCheckBox;

class LocationTab : public QWidget{
    Q_OBJECT
    friend class MainCore;
    friend class SettingsDisplay;

public:
    explicit LocationTab(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    //Functions.
    QGroupBox *CreateCoordinatesGroup();

    QGroupBox *CreateTimeGroup();

    void SetText();

    //Pointers.
    QVBoxLayout *LocationBox;

    QGroupBox *CoordinatesGroup;
    QFormLayout *CoordinatesLayout;
    QLabel *LatitudeLabel;
    QDoubleSpinBox *LatitudeSpinBox;
    QLabel *LongitudeLabel;
    QDoubleSpinBox *LongitudeSpinBox;

    QGroupBox *TimeGroup;
    QFormLayout *TimeLayout;
    QLabel *TimeZoneLabel;
    QDoubleSpinBox *TimeZoneSpinBox;
    QCheckBox *DayLightCheckBox;

};

#endif
