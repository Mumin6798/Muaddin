#ifndef METHODSTAB_H
#define METHODSTAB_H

//QT includes.
#include <QWidget>

//QT forward declarations.
class QVBoxLayout;
class QGroupBox;
class QFormLayout;
class QLabel;
class QComboBox;
class QDoubleSpinBox;

class MethodsTab : public QWidget{
    Q_OBJECT
    friend class MainCore;
    friend class SettingsDisplay;

public:
    explicit MethodsTab(QWidget *parent = 0);

protected slots:
    void EnableCustomAngles(int CurrectIndex);

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    //Functions.
    QGroupBox *CreateMethodsGroup();

    QGroupBox *CreateExtremeMethodsGroup();

    void SetText();

    void ConnectEverything();

    //Pointers.
    QVBoxLayout *MethodsBox;

    QGroupBox *MethodsGroup;
    QFormLayout *MethodsLayout;
    QLabel *MethodsLabel;
    QComboBox *MethodsComboBox;
    QLabel *CustomFajrLabel;
    QDoubleSpinBox *CustomFajrSpinBox;
    QLabel *CustomIshaLabel;
    QDoubleSpinBox *CustomIshaSpinBox;
    QLabel *JuristicLabel;
    QComboBox *JuristicComboBox;

    QGroupBox *ExtremeMethodsGroup;
    QFormLayout *ExtremeMethodsLayout;
    QLabel *ExtremeMethodsLabel;
    QComboBox *ExtremeMethodsComboBox;

};

#endif
