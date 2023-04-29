#ifndef TRADER_H_INCLUDED
#define TRADER_H_INCLUDED
#include "Bourse.h"
#include "portefeuille.h"
#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include <algorithm>
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
class TraderBollin :public Trader{
 private : 
    map <string,pair<double , int>> MoydAction;
public:
    Transaction choisirTransaction(const Bourse& , const Portefeuille &);
    inline bool casdVente(double lastprix,double Bornesup){return Bornesup<lastprix ;};
    inline bool casdAchat(double lastprix,double Borneinf){return Borneinf>lastprix ;};
    inline double bornInf(double moy,double eT){return (moy - 3* eT);}
    inline double bornSup(double moy,double eT){return (moy + 3* eT);}
    void mettreajour(map <string,pair<double , int>>& MoydAction,const PrixJournalier & pj );
};

Transaction TraderBollin::choisirTransaction(const Bourse& bour, const Portefeuille & portef){
    double ss=portef.getSolde();
    vector<PrixJournalier> vPj=bour.getPrixJournaliersDispoAujourdhui(ss);
    sort(vPj.begin(), vPj.end(), [](PrixJournalier pj1, PrixJournalier pj2){ return pj1.getPrix() < pj2.getPrix(); });
    for (auto pj : vPj){
        bool pasmisajour=find(bour.getActionDisponibleAujourdhui().begin(),bour.getActionDisponibleAujourdhui().end(),pj.getNomAction()) == bour.getActionDisponibleAujourdhui().end();
        if ((pj.getPrix()>portef.getSolde())&& pasmisajour)  break; 
        else{
            string nomdActi=pj.getNomAction();
            vector<PrixJournalier> historique1Action=bour.getHistoriqueAction(nomdActi);
            mettreajour(MoydAction, pj);
            double sommeDiff = 0.0;
            double ecartType ;
            //calcul decart type en se basant au plus sur les 10 derniers val
            if (historique1Action.size()>10){
                for (int i = historique1Action.size() - 1; i >= historique1Action.size() - 10; i--) {
                    double diff = historique1Action[i].getPrix() - MoydAction[nomdActi].first ;
                    sommeDiff += diff * diff;
                }
                ecartType=sqrt(sommeDiff/10);
            }
            else{
                for (int i = historique1Action.size() - 1; i >= 0; i--) {
                    double diff = historique1Action[i].getPrix() - MoydAction[nomdActi].first ;
                    sommeDiff += diff * diff;
                }
                ecartType=sqrt(sommeDiff/(historique1Action.size()+1));
            }
            double Bs = bornSup(MoydAction[nomdActi].first, ecartType);
            double Bi = bornInf(MoydAction[nomdActi].first, ecartType); 
            //------------------------------
            if (casdVente(bour.getLastPrixAction(nomdActi),Bs)){
                vector<Titre> Pt=portef.getTitre();
                int choixQte;
                for(auto elt :Pt){
                    if (elt.getNomAction()==nomdActi){
                        choixQte=elt.getQte();break;
                    }
                }
                return Transaction(vente,nomdActi,choixQte);
            }
            else if (casdAchat(bour.getLastPrixAction(nomdActi),Bi)){
                double QteDispo=portef.getSolde()/(pj.getPrix());
                if(QteDispo>3){return Transaction(achat,nomdActi,3);}
                else if(QteDispo>2){return Transaction(achat,nomdActi,2);}
                else{return Transaction(achat,nomdActi,1);}
            }
            
        }
    }
    return Transaction(rienAFaire,"",0);
}
void TraderBollin::mettreajour(map <string,pair<double , int>>& MoydAction,const PrixJournalier & pj ){
    if (MoydAction.find(pj.getNomAction())==MoydAction.end()){
            MoydAction[pj.getNomAction()]=make_pair(pj.getPrix(),1);
    }
    else {
        double& moyenne=MoydAction[pj.getNomAction()].first;
        int& nbdinstances=MoydAction[pj.getNomAction()].second;
        moyenne=((moyenne*nbdinstances)+pj.getPrix())/(nbdinstances+1); 
        nbdinstances++;
    }
}
#endif
