#ifndef ATHAN_H_
#define ATHAN_H_
/*
	Islamic Calculation Methods:
	University of Islamic Sciences (Karachi) = 0
	Islamic Society of North America (ISNA) = 1
	Muslim World League (MWL) = 2
	Egyptian General Authority of Survey (Egypt) = 3
	Shia Ithna Ashari (Jafari) = 4
	Umm al-Qura (Makkah) = 5

    Inputs Notes:
    Latitude is in degrees where north is positive.
    Longitude is in degrees where east is positive.
    Angles are negative which means it's bellow the horizon.
*/

class Athan{
    public:
        typedef enum ExtremeDayMethods {One_Seventh_Night, Angle, Midnight} ExtremeDayMethods;
        static const double FajrAngles[6];
        static const double IshaAngles[6];
        void Init(double Latitude, double Longitude, double TimeZone, int DayofTheYear);
        int getFajr(ExtremeDayMethods ExtremeDay, double FajrAngle);
        int getSunrise();
        int getDhuhr();
        int getAsr(int UseHanafi);
        int getMaghrib();
        int getIsha(ExtremeDayMethods ExtremeDay, double IshaAngle);
        double getQiblah();

    private:
        double SeventhMethod();
        double MidnightMethod();
        double AngleMethod(double angle);
        double getHourAngle(double angle);
        double Declination;
        double dhuhr;
        double Latitude;
        double Longitude;
        double hourangleofsunset;

};
#endif
