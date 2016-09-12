#ifndef TIMECORE_H
#define TIMECORE_H

//Qt include.
#include <QObject>

//Qt forward declaration.
class QTimer;
class QSettings;
class Athan;

class TimeCore : public QObject{
    Q_OBJECT
    friend class MainCore;

public:
    explicit TimeCore(QObject *parent = 0, QThread *Thread = 0);

signals:
    void UpdateTime(QString NewTime);
    void UpdateDate(QString NewDate);
    void UpdateNextPrayer(QString NewNextPrayer);
    void UpdateFajr(QString NewFajr);
    void UpdateSunRise(QString NewSunRise);
    void UpdateDhuhr(QString NewDhuhr);
    void UpdateAsr(QString NewAsr);
    void UpdateMaghrib(QString NewMaghrib);
    void UpdateIsha(QString NewIsha);
    void UpdateCompass(int angle);

    void Play();

public slots:
    void start();

    void UpdateEverything();
    void SetText();

protected slots:
    void Update();

private:
    //Non pointers.
    int NextPrayer;
    QString HourString;
    QString MinuteString;
    QStringList PrayerStringList;

    //Functions.
    void UpdatePerSecond();
    void UpdatePerMinute();
    void UpdatePerDay();

    //Pointers.
    QThread *Thread;
    QSettings *MuaddinSettings;
    Athan *PrayerTimes;
    QList<QTime> *PrayerTimeList;

    QTimer *EventTimer;
};

#endif
