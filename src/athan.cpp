#include "athan.hpp"
#include <math.h>
#include <stdio.h>

//Setting up all the constants.
#define pi 3.1415926535897932385
#define torad 0.01745329251994329577
#define todeg 57.295779513082320877
#define QiblahLatitude 21.4225
#define QiblahLongitude 39.8262

//Setting an array of the angles for all methods.
const double Athan::FajrAngles[] = {-18.0, -15.0, -18.0, -19.5, -16.0, -18.5};
const double Athan::IshaAngles[] = {-18.0, -15.0, -17.0, -17.5, -14.0, 0.0};

double Athan::getHourAngle(double angle){
    //Calculating the hour angle for the given angle.
	double hourangle = (sin(angle*torad)-sin(Latitude*torad)*sin(Declination*torad))/(cos(Latitude*torad)*cos(Declination*torad));
    //Checking to see if hourangle is greater then 1 which will given an mathematical error.
	if(fabs(hourangle) > 1){
        //Return an number which is impossible to return if there was no error.
		return 1024.0;
	}
	//Returning hourangle in hours not angular units.
	return todeg*acos(hourangle)/15;
}

double Athan::SeventhMethod(){
    //Return seventh of the night plus to sunset hour angle.
	return (24.0+5.0*hourangleofsunset)/7.0;
}

double Athan::AngleMethod(double angle){
    //Return angle/60th the night plus sunset hour angle.
	return hourangleofsunset + (24.0-2*hourangleofsunset)*fabs(angle)/60.0;
}

double Athan::MidnightMethod(){
    //Return solar midnight.
	double midnight = dhuhr - 12.0;
	return (midnight < 0)? fmod(fmod(midnight, 24.0) + 24.0, 24.0) : fmod(midnight, 24.0);
}

int Athan::getIsha(ExtremeDayMethods ExtremeMethod, double IshaAngle){
    //Returns Isha in seconds form 00:00.
	double isha = 0.0;
	//Check if Umm al-Qura (Makkah) method has been chosen and then it adds 90 minutes to maghrib hour angle if true.
	if(IshaAngle == 0.0){
		isha = dhuhr + hourangleofsunset + 1.5;
	}else{
	    //Else it get the hour angle for the angle given then checks the smaller time between the method and the extreme method.
		double a = getHourAngle(IshaAngle);
		switch(ExtremeMethod){
		    case One_Seventh_Night:
                isha = (SeventhMethod() < a)? dhuhr + SeventhMethod(): dhuhr + a;
                break;
            case Angle:
                isha = (AngleMethod(IshaAngle) < a)? dhuhr + AngleMethod(IshaAngle): dhuhr + a;
                break;
            case Midnight:
                isha = (12 < a)? MidnightMethod(): dhuhr + a;
                break;
        }
	}
	return 60*((int)ceil(60*isha));
}

int Athan::getMaghrib(){
    //Returns Maghrib in seconds form 00:00.
	return 60*((int)ceil(60*(dhuhr + hourangleofsunset)));
}

int Athan::getAsr(int UseHanafi){
    //Returns Asr in seconds form 00:00.
	return 60*((int)ceil(60*(dhuhr + getHourAngle(todeg*atan(1/(1+UseHanafi+tan((Latitude-Declination)*torad)))))));
}

int Athan::getDhuhr(){
    //Returns Dhuhr in seconds form 00:00.
	return 60*((int)ceil(60*dhuhr));
}

int Athan::getSunrise(){
    //Returns SunRise in seconds form 00:00.
	return 60*((int)ceil(60*(dhuhr - hourangleofsunset)));
}

int Athan::getFajr(ExtremeDayMethods ExtremeMethod, double FajrAngle){
    //Returns Fajr in seconds form 00:00.
	double a = getHourAngle(FajrAngle);
	double fajr = 0.0;
	//Checks the smaller time between the method and the extreme method.
    switch(ExtremeMethod){
        case One_Seventh_Night:
            fajr = (SeventhMethod() < a)? dhuhr - SeventhMethod() : dhuhr - a;
            break;
        case Angle:
            fajr = (AngleMethod(FajrAngle) < a)? dhuhr - AngleMethod(FajrAngle): dhuhr - a;
            break;
        case Midnight:
            fajr = (12 < a)? MidnightMethod(): dhuhr - a;
            break;
    }
	return 60*((int)ceil(60*fajr));
}

double Athan::getQiblah(){
    //calculates bearing from kabbah.
	double x = cos(QiblahLatitude*torad)*sin((QiblahLongitude-Longitude)*torad);
	double y = cos(Latitude*torad)*sin(QiblahLatitude*torad)-sin(Latitude*torad)*cos(QiblahLatitude*torad)*cos((QiblahLongitude-Longitude)*torad);
	double bearing = atan2(x,y)*todeg;
	return (bearing < 0)? 360.0 + bearing: bearing;
}

void Athan::Init(double Latitude, double Longitude, double TimeZone, int DayofTheYear){
    //Saving the local coordinates to a global coordinates.
    Athan::Latitude = Latitude;
    Athan::Longitude = Longitude;
    //Calculating the Equation of time and the solar declination.
    double x = DayofTheYear*2*pi/365.24;
    double equationoftime = 229.18*(0.000075 + 0.001868*cos(x) - 0.032077*sin(x) - 0.014615*cos(2*x) - 0.040849*sin(2*x));
    Declination = (0.006918 - 0.399912*cos(x) + 0.070257*sin(x) - 0.006758*cos(2*x) + 0.000907*sin(2*x) - 0.002697*cos(3*x) + 0.00148*sin(3*x))*todeg;
    //Calculating dhuhr in hours.
    dhuhr = 12 - Longitude/15.0 - equationoftime/60.0 + TimeZone;
    //Calculating the time difference of sunrise from dhuhr(solar noon).
    hourangleofsunset = getHourAngle(-0.8333);
}
