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
    virtual vector<string>getActionDisponibleParDate(const Date &){}
    virtual vector<PrixJournalier>getPrixJournaliersParDate(const Date &){}
	vector<PrixJournalier>getPrixJournaliersAujourdhui(){return getPrixJournaliersParDate(dateAujourdhui);}
	vector<PrixJournalier>getPrixJournaliersDispoAujourdhui(double solde);
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


class BourseVector2:public Bourse{
private:
	vector<PrixJournalier>historique;
public:
	BourseVector2(vector<PrixJournalier>&b,const Date& d):historique(b),Bourse(d){}
	vector<string> getActionDisponibleParDate(const Date &);
    vector<PrixJournalier> getPrixJournaliersParDate(const Date&);
    ~BourseVector2(){}
		
		
};
bool appartientAction (string,vector<string>&);
bool appartientPrixJournalier (PrixJournalier pj,vector<PrixJournalier>& vecteurPrixJournalier);

#endif // BOURSE_H_INCLUDED
