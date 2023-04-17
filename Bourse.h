#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include<vector>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class Bourse{
	protected:
    const Date dateAujourdhui;

public:
    Bourse(const Date& d1):dateAujourdhui(d1){}
    virtual vector<string>getActionDisponibleParDate(const Date &){
	}
    virtual vector<PrixJournalier>getPrixJournaliersParDate(const Date &){
	}
    virtual ~Bourse(){};

};



class BourseVector:public Bourse{
private:
    vector<PrixJournalier>historique;

public:
    BourseVector(vector<PrixJournalier>&b,const Date& d1):historique(b),Bourse(d1){}
    vector<string> getActionDisponibleParDate(const Date &);
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &);
    ~BourseVector(){}

};

vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier>,const Date&);

#endif // BOURSE_H_INCLUDED
