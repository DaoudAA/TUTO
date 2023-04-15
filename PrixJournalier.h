#ifndef PRIXJOURNALIER_H_INCLUDED
#define PRIXJOURNALIER_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>
#include"Date.h"
using namespace std;

class PrixJournalier
{
private:
    Date  date;
    string nomAction;
    double  prix;
public:
    PrixJournalier(Date  d, string  n , double  p):date(d),nomAction(n),prix(p){}
    friend ostream& operator<<(ostream& , const PrixJournalier&);

};

ostream& operator<<(ostream& flux , const PrixJournalier& pj){
        flux<<"La date:\t"<<pj.date<<endl;
        flux<<"Le nom de l'action:\t"<< pj.nomAction<<endl;
        flux<<"Le prix est:\t" << pj.prix <<endl;
        return flux;
    }


#endif // PRIXJOURNALIER_H_INCLUDED
