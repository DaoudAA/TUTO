#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include<vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include<map>
#include<set>

using namespace std;


class Bourse{
	protected:
    Date dateAujourdhui;


public:

    Bourse( Date& d1):dateAujourdhui(d1){}

    virtual vector<string>getActionDisponibleParDate( const Date &)const{};
    virtual vector<PrixJournalier>getPrixJournaliersParDate ( const Date &)const{};
	vector<PrixJournalier>getPrixJournaliersAujourdhui()const{return getPrixJournaliersParDate(dateAujourdhui);}		
	vector<PrixJournalier>getPrixJournaliersDispoAujourdhui(double solde);
	double getPrixAujourdhui(string);
    virtual ~Bourse(){};
    friend class Simulation;

};



class BourseVector:public Bourse{
private:
    vector<PrixJournalier>historique;

public:
    BourseVector(vector<PrixJournalier>&b, Date& d1):historique(b),Bourse(d1){}
    vector<string> getActionDisponibleParDate(const Date &)const;
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &)const;
    ~BourseVector(){}

};
vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier>, const Date&);


class BourseVector2:public Bourse{
private:
	vector<PrixJournalier>historique;
public:
	BourseVector2(vector<PrixJournalier>&b, Date& d):historique(b),Bourse(d){}
	vector<string> getActionDisponibleParDate(const Date&)const;
    vector<PrixJournalier> getPrixJournaliersParDate(const Date&)const;
    ~BourseVector2(){}
		
		
};
bool appartientAction (string,vector<string>&);
bool appartientPrixJournalier (PrixJournalier pj,vector<PrixJournalier>& vecteurPrixJournalier);

class BourseDict:public Bourse{
private:
	map<string, vector<PrixJournalier> >  historique;
	
public:
	BourseDict(vector<PrixJournalier>&vPJ, Date &d);
	map<string, vector<PrixJournalier> > getHistoriqueAction(string);
	
};
#endif // BOURSE_H_INCLUDED
