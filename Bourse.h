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

    Date setDate(Date& d1){return dateAujourdhui=d1;}
    virtual vector<PrixJournalier>getPrixJournaliersParDate ( const Date &)const = 0;
    virtual vector<string> getActionDisponibleParDate(const Date& ) const = 0;
    virtual vector<PrixJournalier> getHistoriqueAction(string) const =0;
    double getLastPrixAction(string)const;
	vector<PrixJournalier>getPrixJournaliersAujourdhui()const{return getPrixJournaliersParDate(dateAujourdhui);}		
    vector<string>getActionDisponibleAujourdhui() const {return getActionDisponibleParDate(dateAujourdhui);}
	vector<PrixJournalier>getPrixJournaliersDispoAujourdhui(double solde);
	double getPrixAujourdhui(string);
    virtual ~Bourse(){};
    friend class Simulation;

};



class BourseVector:public Bourse{
private:
    vector<PrixJournalier>historique;

public:
    BourseVector(vector<PrixJournalier>&b):historique(b){}
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &)const;
    vector<string> getActionDisponibleParDate(const Date &)const;
    vector<PrixJournalier> getHistoriqueAction(string) const;
    ~BourseVector(){}

};
vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier>, const Date&);


class BourseVector2:public Bourse{
private:
	vector<PrixJournalier>historique;
public:
	BourseVector2(vector<PrixJournalier>&b):historique(b){}
    vector<PrixJournalier> getPrixJournaliersParDate(const Date&)const;
	vector<string> getActionDisponibleParDate(const Date&)const;
    vector<PrixJournalier> getHistoriqueAction(string) const;
    ~BourseVector2(){}
		
		
};
bool appartientAction (string,vector<string>&);
bool appartientPrixJournalier (PrixJournalier pj,vector<PrixJournalier>& vecteurPrixJournalier);

class BourseDictNom:public Bourse{
private:
	map<string, vector<PrixJournalier> >  historique;
	
public:
	BourseDictNom(vector<PrixJournalier>&vPJ);
    vector<PrixJournalier> getPrixJournaliersParDate(const Date&)const;
	vector<string> getActionDisponibleParDate(const Date&)const;
	vector<PrixJournalier> getHistoriqueAction(string);
    double getLastPrixAction(string);
};
class BourseDictDate:public Bourse{
    map< Date , vector<PrixJournalier>> historique ;
    public:
    BourseDictDate( vector<PrixJournalier> & ); 
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &)const;   
    vector<string> getActionDisponibleParDate(const Date &)const ;
    vector<PrixJournalier> getHistoriqueAction(string)const;
    double getLastPrixAction(string)const;
};
#endif // BOURSE_H_INCLUDED
