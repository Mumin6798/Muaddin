#ifndef ATHANGROUP_H
#define ATHANGROUP_H

//Qt include.
#include <QGroupBox>

//Qt forward declaration.
class QHBoxLayout;
class QPushButton;
class QSlider;

class AthanGroup : public QGroupBox{
    Q_OBJECT
    friend class MainCore;
    friend class MainDisplay;

public:
    explicit AthanGroup(QWidget *parent = 0);

private:
    //Functions.
    void CreateWidget();

    //Pointers.
    QHBoxLayout *AthanBox;

    QPushButton *StopButton;
    QPushButton *PlayButton;
    QSlider *VolumeSlider;

};

#endif
