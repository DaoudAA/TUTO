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
    virtual vector<PrixJournalier>getPrixJournaliersParDate ( const Date &)const = 0;
    virtual vector<string> getActionDisponibleParDate(const Date& ) const = 0;
	vector<PrixJournalier>getPrixJournaliersAujourdhui()const{return getPrixJournaliersParDate(dateAujourdhui);}		
    vector<string>getActionDisponibleAujourdhui() const {return getActionDisponibleParDate(dateAujourdhui);}
	vector<PrixJournalier>getPrixJournaliersDispoAujourdhui(double solde)const;
	virtual vector<PrixJournalier>getHistoriqueAction(string)const = 0 ;
	double getPrixAujourdhui(string);// ona utiliser cette fonction dans l simulation pour donner directement le prix d'une action 
	virtual double getLastPrixAction(string)const ;// il faut s'assurer que le vecteur provenant de gethistoriqueAction est trier par date
	virtual double getAvantDernierPrixDAction(string)const ; // est utilisee dans la partie du trader algorithique 1
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
    vector<PrixJournalier> getHistoriqueAction(string)const;
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
	vector<PrixJournalier> getHistoriqueAction(string)const;
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
	vector<PrixJournalier> getHistoriqueAction(string)const;
};
class BourseDictDate:public Bourse{
    map< Date , vector<PrixJournalier> > historique ;
    public:
    BourseDictDate( vector<PrixJournalier> & ); 
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &)const;   
    vector<string> getActionDisponibleParDate(const Date &)const ;
    vector<PrixJournalier> getHistoriqueAction(string)const;
};
#endif // BOURSE_H_INCLUDED
