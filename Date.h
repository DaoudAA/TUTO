#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class Date {
private:
    int jour;
    int mois;
    int annee;

public:
    Date(int d, int m, int y);
    Date(string ch);
    int getJour()const{return jour;}
    int getMois()const{return mois;}
    int getAnnee()const{return annee;}
    void incrementerDate();
    bool anneeBissextile();
    int nbJourDuMois();
    friend ostream& operator<<(ostream& flux , const Date& );
    friend istream& operator>>(istream& flux, Date &);
    friend bool operator==(const Date& ,const Date&);
    friend bool operator<(const Date& ,const Date&);
};

Date::Date(int d, int m, int y){
    if (y>0) annee=y;
    jour=-1;
    mois=-1;
    if (d>0)
    {
        if (d<=31 && (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)){
            jour=d;
            mois=m;
        }
        if (d<=30 && ( m==4 || m==6 || m==9 || m==11)){
            jour=d;
            mois=m;
        }
        if (d<=29 && m==2){
            if ((y%4)==0 && d<=29)
            {
                jour=d;
                mois=m;
            }
            else if ((y%4)!=0 && d<=28) {
                jour=d;
                mois=m;
            }
        }
    }
}

Date::Date(string ch){
    string ch1,ch2,ch3;
    ch1=ch.substr(0, ch.find('/'));
    jour = atoi(ch1.c_str());
    ch2=ch.erase(0, ch.find('/') + 1);
    ch2=ch.substr(0, ch.find('/'));
    mois= atoi(ch2.c_str());
    ch3=ch.erase(0, ch.find('/') + 1);
    annee = atoi(ch3.c_str());

    if (jour <= 0 || mois <= 0 || mois > 12) {
        jour= -1;
        mois= -1;
    }
    else if (mois == 2) {
        if (annee% 4 == 0 )
        {
            if (jour > 29)
            {
                jour = -1;
                mois = -1;
            }
        }
        else
        {
            if (jour > 28) {
                jour = -1;
                mois = -1;
            }
        }
    }
    else if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) {
        jour = -1;
        mois = -1;
    }
    else if (jour > 31) {
        jour = -1;
        mois = -1;
    }
}
//fonction incrementerDate
bool Date::anneeBissextile(){
    if (annee%4==0) return true;
    return false;
}
int Date::nbJourDuMois(){
    if ((mois==1)||(mois==3)||(mois==5)||(mois==7)||(mois==8)||(mois==10)||(mois==12)){
        return 31;}
    else if (((mois==4)||(mois==6)||(mois==9)||(mois==11))){
        return 30;}
    else if (anneeBissextile()) return 29;
    else return 28;
}

void Date::incrementerDate(){
    if(jour==nbJourDuMois()){
        if (mois ==12){
            annee++;
            mois=1;
            jour=1;
        }
        else {mois++;jour=1;}
    }
    else jour++;
}

ostream& operator<<(ostream& flux , const Date& D){
        flux<< D.jour << "/" << D.mois << "/" << D.annee <<endl;
        return flux;
    }

istream& operator>>(istream& flux, Date &date){
    flux>>date.jour>>date.mois>>date.annee;
    return flux;
}
bool operator==(const Date& d1 ,const Date& d2){
    if ((d1.getJour()==d2.getJour())&&(d1.getMois()==d2.getMois())
            &&(d1.getAnnee()==d2.getAnnee()))
                {return true;}
    else return false;
}

bool operator<(const Date& date1,const Date& date2){
    if(date1.getAnnee()<date2.getAnnee())
        return true;
    else if(date1.getAnnee()==date2.getAnnee()){
            if(date1.getMois()<date2.getMois())
                return true;
            else if(date1.getMois()==date2.getMois())
                    if(date1.getJour()<date2.getJour())
                        return true;
    }
    return false;
}
#endif
