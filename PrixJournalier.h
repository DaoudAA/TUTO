#ifndef PRIXJOURNALIER_H_INCLUDED
#define PRIXJOURNALIER_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>
#include "Date.h"
using namespace std;

class PrixJournalier
{
private:
    Date  date;
    string nomAction;
    double  prix;
public:
    PrixJournalier(){};
    Date getDate()const{return date;}
    string getNomAction()const {return nomAction;}
    double getPrix()const{return prix;}
    PrixJournalier(Date  d, string  n , double  p):date(d),nomAction(n),prix(p){};
    friend ostream& operator<<(ostream& , const PrixJournalier&);
    friend istream& operator>>(istream& , PrixJournalier&);
};

ostream& operator<<(ostream& flux , const PrixJournalier& pj){
        flux << "La date :" << pj.date ;
		flux << "\n Le nom de l'action:\t" << pj.nomAction << endl << "Le prix est:\t" << pj.prix <<endl;
        return flux;
    }

istream& operator>>(istream& flux , PrixJournalier& pj){
    string chDate,chAction,chPrix;
    getline(flux,chDate,';');
    pj.date=convStrToDate(chDate);
    getline(flux,chAction,';');
    pj.nomAction = chAction.substr(0,chAction.find(';'));
    getline(flux,chPrix,'\n');
    pj.prix=atof(chPrix.c_str());
    return flux;
    
}

#endif // PRIXJOURNALIER_H_INCLUDED
