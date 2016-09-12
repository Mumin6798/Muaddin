//Muaddin includes.
#include "timecore.h"
#include "athan.hpp"

//Qt includes.
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QSettings>
#include <QLocale>
#include <QEvent>

TimeCore::TimeCore(QObject *parent, QThread *thread) : QObject(parent){
    //Setting up the class to use the threads.
    Thread = thread;
    MuaddinSettings = new QSettings("Muaddin", "Muaddin", this);
    PrayerTimes = new Athan();
    PrayerTimeList = new QList<QTime>();
    connect(Thread, &QThread::started, this, &TimeCore::start);
    SetText();
}

void TimeCore::start(){
    //The code starts here and creates a timer and it's connections.
    EventTimer = new QTimer(this);
    EventTimer->setTimerType(Qt::PreciseTimer);
    connect(EventTimer, &QTimer::timeout, this, &TimeCore::Update);
    EventTimer->start(10);
}

void TimeCore::Update(){
    //This gets called every centisecond.
    int NowInDeciSecs = (int)QTime::currentTime().msecsSinceStartOfDay()/100;
    //Checks if a new unit of time has elapsed.
    if(NowInDeciSecs%10 == 0){
        UpdatePerSecond();
        if(NowInDeciSecs%600 == 0){
            UpdatePerMinute();
            if(NowInDeciSecs == 0){
               UpdatePerDay();
            }
        }
    }
}

void TimeCore::UpdatePerSecond(){
    //This updates the TimeLabel every second.
    MuaddinSettings->beginGroup("Settings");
    emit UpdateTime(QLocale(MuaddinSettings->value("Language").toString()).toString(QTime::currentTime(), "HH:mm:ss"));
    MuaddinSettings->endGroup();
}

void TimeCore::UpdatePerMinute(){
    //This Updates NextPrayerLabel every minute and checks if it's time to pray.
    if(NextPrayer < 5){
        MuaddinSettings->beginGroup("Settings");
        int SecondsToNextPrayer = QTime::currentTime().secsTo(PrayerTimeList->at(NextPrayer));
        QString NextPrayerTimeDifference = QLocale(MuaddinSettings->value("Language").toString()).toString(QTime(0, 0).addSecs(
                    SecondsToNextPrayer), "H") + HourString + QLocale(MuaddinSettings->value("Language").toString())
                        .toString(QTime(0, 0).addSecs(SecondsToNextPrayer), "m") + MinuteString;

        //Finding what pray is up next.
        switch(NextPrayer){
            case 0:
                emit UpdateNextPrayer(PrayerStringList.at(0) + NextPrayerTimeDifference);
                break;
            case 1:
                emit UpdateNextPrayer(PrayerStringList.at(1) + NextPrayerTimeDifference);
                break;
            case 2:
                emit UpdateNextPrayer(PrayerStringList.at(2) + NextPrayerTimeDifference);
                break;
            case 3:
                emit UpdateNextPrayer(PrayerStringList.at(3) + NextPrayerTimeDifference);
                break;
            case 4:
                emit UpdateNextPrayer(PrayerStringList.at(4) +NextPrayerTimeDifference);
                break;
        }
        MuaddinSettings->endGroup();

        //Checks to see if it's time to pray.
        if(SecondsToNextPrayer == 0){
            emit Play();
            NextPrayer++;
        }
    }else{
        emit UpdateNextPrayer("");
    }
}

void TimeCore::UpdatePerDay(){
    //This updates every days.
    MuaddinSettings->beginGroup("Settings");
    emit UpdateDate(QLocale(MuaddinSettings->value("Language").toString()).toString(QDate::currentDate(), "yyyy MMMM d dddd"));
    //Updates prayer times.
    if(MuaddinSettings->value("Daylight").toBool() && QDateTime::currentDateTime().isDaylightTime()){
        PrayerTimes->Init(MuaddinSettings->value("Latitude").toDouble(), MuaddinSettings->value("Longitude").toDouble(),
                          MuaddinSettings->value("Time Zone").toDouble() + 1.0, QDate::currentDate().dayOfYear());
    }else{
        PrayerTimes->Init(MuaddinSettings->value("Latitude").toDouble(), MuaddinSettings->value("Longitude").toDouble(),
                          MuaddinSettings->value("Time Zone").toDouble(), QDate::currentDate().dayOfYear());
    }
    PrayerTimeList->clear();
    if(MuaddinSettings->value("Method").toInt() == 6){
        PrayerTimeList->operator <<(QTime(0, 0).addSecs(PrayerTimes->getFajr(static_cast<Athan::ExtremeDayMethods>(
                                        MuaddinSettings->value("Extreme Method").toInt()),
                                            MuaddinSettings->value("Custom Fajr Angle").toDouble())));
        PrayerTimeList->operator <<(QTime(0, 0).addSecs(PrayerTimes->getIsha(static_cast<Athan::ExtremeDayMethods>(
                                        MuaddinSettings->value("Extreme Method").toInt()),
                                            MuaddinSettings->value("Custom Isha Angle").toDouble())));
    }else{
        PrayerTimeList->operator <<(QTime(0, 0).addSecs(PrayerTimes->getFajr(static_cast<Athan::ExtremeDayMethods>(
                                        MuaddinSettings->value("Extreme Method").toInt()), Athan::FajrAngles[
                                                                        MuaddinSettings->value("Method").toInt()])));
        PrayerTimeList->operator <<(QTime(0, 0).addSecs(PrayerTimes->getIsha(static_cast<Athan::ExtremeDayMethods>(
                                        MuaddinSettings->value("Extreme Method").toInt()), Athan::IshaAngles[
                                                                        MuaddinSettings->value("Method").toInt()])));
    }
    PrayerTimeList->operator <<(QTime(0, 0).addSecs(PrayerTimes->getAsr(MuaddinSettings->value("Juristic Method").toInt())));
    PrayerTimeList->operator <<(QTime(0, 0).addSecs(PrayerTimes->getMaghrib()));
    PrayerTimeList->operator <<(QTime(0, 0).addSecs(PrayerTimes->getDhuhr()));
    PrayerTimeList->swap(1, 4);

    //Finding out what the next prayer is.
    for(int i = 0; i < 5; i++){
        QTime PrayerTime = PrayerTimeList->at(i);
        if(QTime::currentTime().hour() < PrayerTime.hour() || (QTime::currentTime().hour() == PrayerTime.hour() &&
                                                               QTime::currentTime().minute() < PrayerTime.minute())){
            NextPrayer = i;
            break;
        }else if(i == 4){
            NextPrayer = 5;
            break;
        }
    }

    //Send data to display.
    emit UpdateFajr(QLocale(MuaddinSettings->value("Language").toString()).toString(PrayerTimeList->at(0), "HH:mm:ss"));
    emit UpdateSunRise(QLocale(MuaddinSettings->value("Language").toString()).toString(
                                QTime(0, 0).addSecs(PrayerTimes->getSunrise()), "HH:mm:ss"));
    emit UpdateDhuhr(QLocale(MuaddinSettings->value("Language").toString()).toString(PrayerTimeList->at(1), "HH:mm:ss"));
    emit UpdateAsr(QLocale(MuaddinSettings->value("Language").toString()).toString(PrayerTimeList->at(2), "HH:mm:ss"));
    emit UpdateMaghrib(QLocale(MuaddinSettings->value("Language").toString()).toString(PrayerTimeList->at(3), "HH:mm:ss"));
    emit UpdateIsha(QLocale(MuaddinSettings->value("Language").toString()).toString(PrayerTimeList->at(4), "HH:mm:ss"));
    emit UpdateCompass(PrayerTimes->getQiblah());

    MuaddinSettings->endGroup();
}

void TimeCore::UpdateEverything(){
    //Updating all the information.
    UpdatePerSecond();
    UpdatePerDay();
    UpdatePerMinute();
}

void TimeCore::SetText(){
    //Setting texts.
    HourString = tr(" hours and ");
    MinuteString = tr(" minutes.");
    PrayerStringList.clear();
    PrayerStringList << tr("Fajr is in ");
    PrayerStringList << tr("Dhuhr is in ");
    PrayerStringList << tr("Asr is in ");
    PrayerStringList << tr("Maghrib is in ");
    PrayerStringList << tr("Isha is in ");
}
