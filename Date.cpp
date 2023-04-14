#include <iostream>
#include <string>
#include <cstdlib>
#include"Date.h"
using namespace std;
//constructeurs
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
};
int Date::nbJourDuMois(){
    if ((mois==1)||(mois==3)||(mois==5)||(mois==7)||(mois==8)||(mois==10)||(mois==12)){
        return 31;}
    else if (((mois==4)||(mois==6)||(mois==9)||(mois==11))){
        return 30;}
    else if (anneeBissextile()) return 29;
    else return 28;
}

void Date::incrementerDate()
{
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

class Test {
void verif(Date, Date,string )const;
};
//void Test::verif(Date dateDonnee, Date dateJuste,string message )


//operateurs de surcharge
 bool operator==(Date const&d1, Date const&d2)
 {
     bool test=false;
     if (d1.getJour()==d2.getJour())
        if(d1.getMois()==d2.getMois())
            if(d1.getAnnee()==d2.getAnnee())
                test=true ;
     return test;
 }

 bool operator <(Date const& date1, Date const& date2)
{
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
 bool operator >(Date & date1, Date & date2)
{
    if(date1.getAnnee()>date2.getAnnee())
        return true;
    else if(date1.getAnnee()==date2.getAnnee()){
            if(date1.getMois()>date2.getMois())
                return true;
            else if(date1.getMois()==date2.getMois())
                    if(date1.getJour()>date2.getJour())
                        return true;

    }

    return false;
}

