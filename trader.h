#ifndef TRADER_H_INCLUDED
#define TRADER_H_INCLUDED
#include "portefeuille.h"
#include "Bourse.h"
#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include <algorithm>
#include <unordered_map>
using namespace std;
enum TypeTransaction { achat, vente, rienAFaire };
class Transaction {
private:
    TypeTransaction typeTx;
    string nomdAction;
    int qtedAction;

public:
    Transaction(TypeTransaction type , string nomdAct, int qte): typeTx(type), nomdAction(nomdAct), qtedAction(qte) {}
    TypeTransaction getTypeTx() const { return typeTx; }
    string getnomdAction() const { return nomdAction; }
    int getqtedAction() const { return qtedAction; }
    virtual ~Transaction(){};
};
class Trader
{
public:
    virtual Transaction choisirTransaction(const Bourse& , const Portefeuille &portefeuille)=0;
};

class TraderAlea :public Trader{
public:
    Transaction choisirTransaction(const Bourse& bour, const Portefeuille& portefeuille) {
    // 1st suggested transaction is buying
    TypeTransaction type;

    if (portefeuille.getTitre().empty()) {
        type = achat;
    }
    else {
        type = static_cast<TypeTransaction>(rand() % 3);
    }
    if (type == rienAFaire) {
        return Transaction(rienAFaire, "", 0);
    }
    else if (type == achat) {
        vector<PrixJournalier> Pj = bour.getPrixJournaliersDispoAujourdhui(portefeuille.getSolde());
        int n =(int) Pj.size();
        if (n>0){
        int choixDAction = rand() % Pj.size();
        double QteDispo = portefeuille.getSolde() / Pj[choixDAction].getPrix();
        int maxQte = floor(QteDispo);
        int choixQte = 1 + rand() % maxQte;
        return Transaction(achat, Pj[choixDAction].getNomAction(), choixQte);
    }}
    else {
        vector<Titre> Pt = portefeuille.getTitre();
        int n = Pt.size();
        int choixDAction = rand() % n;
        int x = Pt[choixDAction].getQte();
        int choixQte = 1 + rand() % x;
        return Transaction(vente, Pt[choixDAction].getNomAction(), choixQte);
    }
}
};

// trader algorithmique 1
class TraderAlgo1 :public Trader{
public:
    Transaction choisirTransaction(const Bourse& , const Portefeuille &);
};

Transaction TraderAlgo1::choisirTransaction(const Bourse&bourse , const Portefeuille &portefeuille){
	int qte=0;
	Transaction t(TypeTransaction,string,int);	
	vector<PrixJournalier>vPJ=bourse.getPrixJournaliersDispoAujourdhui(portefeuille.getSolde());
    int maxv=(int)vPJ.size();
	for(int i=0;i<maxv;i++){
		double dernierPrix=bourse.getLastPrixAction(vPJ[i].getNomAction());
		double avantDernierPrix=bourse.getAvantDernierPrixDAction(vPJ[i].getNomAction());
		if((dernierPrix>avantDernierPrix)&&(portefeuille.getSolde()>dernierPrix)){
			while(portefeuille.getSolde()>dernierPrix*(qte+1))
				qte	++;	
            		
			return Transaction(achat,vPJ[i].getNomAction(),qte);			
		}

	}
	if((portefeuille.getTitre()).size()==0)
		return Transaction(rienAFaire,"",0);	
    int maxp=(int)(portefeuille.getTitre()).size();	
	for(int i=0;i<maxp;i++){
		double dernierPrix=bourse.getLastPrixAction(portefeuille.getTitre()[i].getNomAction());
		double avantDernierPrix=bourse.getAvantDernierPrixDAction(portefeuille.getTitre()[i].getNomAction());
		if(dernierPrix<avantDernierPrix){
			qte=portefeuille.getTitre()[i].getQte();		
			return Transaction(vente,portefeuille.getTitre()[i].getNomAction(),qte);			
		}

	}
	return Transaction(rienAFaire,"",0);	
	
	
	
	
}

class TraderBollin1 : public Trader {
private:
    unordered_map<string, pair<double, int>> moydAction;
public:
    Transaction choisirTransaction(const Bourse&, const Portefeuille&);

private:
    double calculerEcartType(const vector<PrixJournalier>& historique, double moyenne);
    double calculerBornInf(double moyenne, double ecartType);
    double calculerBornSup(double moyenne, double ecartType);
    //double calculerMoyenne(const vector<PrixJournalier>& historique);
    bool comparePriceDescending(const PrixJournalier& pj1, const PrixJournalier& pj2);
};
bool TraderBollin1::comparePriceDescending(const PrixJournalier& pj1, const PrixJournalier& pj2){
    return pj1.getPrix() > pj2.getPrix();
}
Transaction TraderBollin1::choisirTransaction(const Bourse& bour, const Portefeuille& portef) {
    
    vector<PrixJournalier>PrixJournaliers=bour.getPrixJournaliersDispoAujourdhui(portef.getSolde());
    vector<PrixJournalier>PrixJactionen=bour.getPrixJournaliersAujourdhui();
    //cout<< "solde restant : " <<portef.getSolde() <<endl;
    //cout<< "lmarchi fih pj  dispo :" <<PrixJournaliers.size() << endl;
    //cout<< "lmarchi fih  pj khw  :" <<PrixJactionen.size() << endl;
    //cout<< "portefill fih "<<portef.getTitre().size()<<endl;
    //vector<PrixJournalier> PrixJournaliers = vPJ;
    if (portef.getTitre().size() == 0){
        //cout << "portef feragh "<<endl ; 
        PrixJournalier pluscher=PrixJournaliers[0];
        for (unsigned int i = 1; i < PrixJournaliers.size(); i++) {
            if (PrixJournaliers[i].getPrix() > pluscher.getPrix()) {
                 pluscher = PrixJournaliers[i]; // update most expensive
            }
        }

        double qteDispo = portef.getSolde() / pluscher.getPrix();
        int qte = min(3, static_cast<int>(qteDispo));
        return Transaction(TypeTransaction::achat, pluscher.getNomAction(), floor(qteDispo));
    }
    bool triedAll=false;
    //cout << "PJ size this time "<<PrixJournaliers.size()<<endl;
    for (const PrixJournalier& prixJournalier : PrixJournaliers) {
        const string nomAction = prixJournalier.getNomAction();
        
        //|| find(bour.getActionDisponibleAujourdhui().begin(), bour.getActionDisponibleAujourdhui().end(), nomAction) == bour.getActionDisponibleAujourdhui().end()
        
        //cout <<prixJournalier.getNomAction() << endl;
        const vector<PrixJournalier>& historique = bour.getHistoriqueAction(nomAction);
        //cout<<"historique dyal l action "<<bour.getHistoriqueAction(nomAction).size() <<endl ;
        double dernierPrix = bour.getLastPrixAction(nomAction);

        double& moyenne = moydAction[nomAction].first;
       // double  =moy;
        int& nbInstances = moydAction[nomAction].second;

        moyenne = ((moyenne * nbInstances) + prixJournalier.getPrix()) / (nbInstances + 1);
        ++nbInstances;

        double ecartType = calculerEcartType(historique, moyenne);
        double bornInf = calculerBornInf(moyenne, ecartType);
        double bornSup = calculerBornSup(moyenne, ecartType);

        if (moyenne*1.05 <= dernierPrix || portef.getSolde()<1) {
            for (const Titre& titre : portef.getTitre()) {
                if (titre.getNomAction() == nomAction) {
                    int qte = titre.getQte();
                    return Transaction(TypeTransaction::vente, nomAction, qte);
                }
            }
        }
        else if (moyenne*0.95 > dernierPrix && prixJournalier.getPrix() < portef.getSolde()){
            double qteDispo = portef.getSolde() / prixJournalier.getPrix();
            int qte = min(5, static_cast<int>(qteDispo));
            return Transaction(TypeTransaction::achat, nomAction, floor(qte));
        }
        if (&prixJournalier == &PrixJournaliers.back()){
        triedAll = true;
        //cout<<"ARRIVED"<<endl;
        }
    }
    if (triedAll){return Transaction(TypeTransaction::rienAFaire, "", 0);}
}
double TraderBollin1::calculerEcartType(const vector<PrixJournalier>& historique, double moyenne) {
double sommeDiffCarrees = 0.0;
int n = historique.size();
int nbValuesToConsider; //= min(n * 0.1, 10); // only consider 10% of the most recent data or 10 data points, whichever is smaller
if (n>10) {nbValuesToConsider=10 ;}else {nbValuesToConsider=n;}
int startIndex = n - nbValuesToConsider;
for (int i = startIndex; i < n; i++) {
double diff = historique[i].getPrix() - moyenne;
sommeDiffCarrees += diff * diff;
}
return sqrt(sommeDiffCarrees / nbValuesToConsider);
}
double TraderBollin1::calculerBornInf(double moyenne, double ecartType) {
    return moyenne - 2 * ecartType;
}

double TraderBollin1::calculerBornSup(double moyenne, double ecartType) {
    return moyenne + 2 * ecartType;
}

/*double TraderBollin1::calculerMoyenne(const vector<PrixJournalier>& historique) {
    double somme = 0.0;
    int n = historique.size();
    for (const PrixJournalier& pj : historique) {
        somme += pj.getPrix();
    }
    return somme / n;
}*/


#endif
