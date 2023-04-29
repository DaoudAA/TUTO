#ifndef TRADER_H_INCLUDED
#define TRADER_H_INCLUDED
#include "Bourse.h"
#include "portefeuille.h"
#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;
enum TypeTransaction { achat, vente, rienAFaire };
class Transaction {
private:
    TypeTransaction typeTx;
    string nomdAction;
    int qtedAction;

public:
    Transaction(TypeTransaction type, string nomdAct, int qte): typeTx(type), nomdAction(nomdAct), qtedAction(qte) {}
    TypeTransaction getTypeTx() const { return typeTx; }
    string getnomdAction() const { return nomdAction; }
    int getqtedAction() const { return qtedAction; }
};
class Trader
{
public:
    virtual Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille)=0;
};

class TraderAlea :public Trader{
public:
    Transaction choisirTransaction(const Bourse& , const Portefeuille &);
};
Transaction TraderAlea::choisirTransaction(const Bourse& bour, const Portefeuille &portef){
    //1 ere transaction suggere est achat 
    TypeTransaction type;
    if ((portef.getTitre()).size()==0){type = achat ;}
    else type = static_cast<TypeTransaction>(rand() % 3);
    double ss=portef.getSolde();
    if (type==rienAFaire){return Transaction(rienAFaire,"",0);}
    else if (type==achat){
        vector<PrixJournalier> Pj=bour.getPrixJournaliersDispoAujourdhui(ss);
        int n=Pj.size();
        int choixDAction=rand()%n;
        double QteDispo=portef.getSolde()/(Pj[choixDAction].getPrix());
        int maxQte=floor(QteDispo);
        int choixQte=1+rand()%maxQte;
        return Transaction(achat,Pj[choixDAction].getNomAction(),choixQte);
    }
    else {
        vector<Titre> Pt=portef.getTitre();
        int n=Pt.size();
        int choixDAction=rand()%n;
        int x=Pt[choixDAction].getQte();
        int choixQte=1+rand()%x;
        return Transaction(vente,Pt[choixDAction].getNomAction(),choixQte); 
    }
}

#endif
