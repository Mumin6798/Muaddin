#ifndef PRAYERGROUP_H
#define PRAYERGROUP_H

//Qt include.
#include <QGroupBox>

//Qt forward declarations.
class QGridLayout;
class QLabel;

class PrayerGroup : public QGroupBox{
    Q_OBJECT
    friend class MainCore;
    friend class MainDisplay;

public:
    explicit PrayerGroup(QWidget *parent = 0);

private slots:
    void UpdateFajrLabel(QString NewFajr);
    void UpdateSunRiseLabel(QString NewSunRise);
    void UpdateDhuhrLabel(QString NewDhuhr);
    void UpdateAsrLabel(QString NewAsr);
    void UpdateMaghribLabel(QString NewMaghrib);
    void UpdateIshaLabel(QString NewIsha);

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    //Functions.
    void CreateLabels();

    void SetText();

    //Pointers.
    QGridLayout *PrayerTimesLayout;

    QLabel *FajrTitleLabel;
    QLabel *SunRiseTitleLabel;
    QLabel *DhuhrTitleLabel;
    QLabel *AsrTitleLabel;
    QLabel *MaghribTitleLabel;
    QLabel *IshaTitleLabel;
    QLabel *FajrLabel;
    QLabel *SunRiseLabel;
    QLabel *DhuhrLabel;
    QLabel *AsrLabel;
    QLabel *MaghribLabel;
    QLabel *IshaLabel;

};

#endif
