#ifndef PRIXJOURNALIER_H_INCLUDED
#define PRIXJOURNALIER_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>
#include "Date.h"
using namespace std;

class PrixJournalier{
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
    friend  bool operator==(const PrixJournalier &pj1,const PrixJournalier&pj2);
    friend bool operator<(const PrixJournalier& pj1, const PrixJournalier& pj2);
    friend ostream& operator<<(ostream& , const PrixJournalier&);
    friend istream& operator>>(istream& , PrixJournalier&);
};


ostream& operator<<(ostream& flux , const PrixJournalier& pj){
        flux << endl<<"La date :" << pj.date<<endl ;
		flux << "\t Le nom de l'action:\t" << pj.nomAction << endl << "\t Le prix est:\t" << pj.prix <<endl;
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
bool operator==(const PrixJournalier &pj1,const PrixJournalier&pj2){
    if ((pj1.getDate() == pj2.getDate()) && (pj1.getNomAction() == pj2.getNomAction()))
        return true;
    else
        return false;
}
bool operator<(const PrixJournalier& pj1, const PrixJournalier& pj2) {
    return (pj1.getDate() < pj2.getDate());
}
#endif // PRIXJOURNALIER_H_INCLUDED
