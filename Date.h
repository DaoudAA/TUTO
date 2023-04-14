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
    friend ostream& operator<<(ostream& flux , const Date& D){
        flux<< D.jour << "/" << D.mois << "/" << D.annee <<endl;
        return flux;
    }


    friend istream& operator>>(istream& flux, Date &date){
         flux>>date.jour>>date.mois>>date.annee;
        return flux;
    }

};

#endif
