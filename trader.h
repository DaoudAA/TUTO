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
    cout <<"506"<<endl;
    if (type == rienAFaire) {
        return Transaction(rienAFaire, "", 0);
    }
    else if (type == achat) {
        vector<PrixJournalier> Pj = bour.getPrixJournaliersAujourdhui();
        int n =(int) Pj.size();
        if (n>0){
        int choixDAction = rand() % Pj.size();
        cout << choixDAction << endl;
        double QteDispo = portefeuille.getSolde() / Pj[choixDAction].getPrix();
        int maxQte = floor(QteDispo);
        cout << "3" << endl;
        int choixQte = 1 + rand() % maxQte;
        cout << "3" << endl;
        return Transaction(achat, Pj[choixDAction].getNomAction(), choixQte);
    }}
    else {
        cout << "5" << endl;
        vector<Titre> Pt = portefeuille.getTitre();
        int n = Pt.size();
        int choixDAction = rand() % n;
        int x = Pt[choixDAction].getQte();
        int choixQte = 1 + rand() % x;
        return Transaction(vente, Pt[choixDAction].getNomAction(), choixQte);
    }
}
};
/*Transaction TraderAlea::choisirTransaction(const Bourse & bour, const Portefeuille &portefeuille){
    //1 ere transaction suggere est achat 
    TypeTransaction type;
    
    if ((portefeuille.getTitre()).size()==0){type = achat ;}
    else type = static_cast<TypeTransaction>(rand() % 3);
    
    if (type==rienAFaire){cout<<"2"<<endl ; return Transaction(rienAFaire,"",0);}
    else if (type==achat){
        vector<PrixJournalier> Pj=bour.getPrixJournaliersAujourdhui();
        int n=Pj.size();
        int choixDAction=rand()%n;
        double QteDispo=portefeuille.getSolde()/(Pj[choixDAction].getPrix());
        int maxQte=floor(QteDispo);
        int choixQte=1+rand()%maxQte;
        return Transaction(achat,Pj[choixDAction].getNomAction(),choixQte);
    }
    else {
        vector<Titre> Pt=portefeuille.getTitre();
        int n=Pt.size();
        int choixDAction=rand()%n;
        int x=Pt[choixDAction].getQte();
        int choixQte=1+rand()%x;
        return Transaction(vente,Pt[choixDAction].getNomAction(),choixQte); 
    }
}
*/
/*Transaction TraderAlea::choisirTransaction(const Bourse& bour, const Portefeuille& portefeuille) {
    // 1st suggested transaction is buying
    TypeTransaction type;

    if (portefeuille.getTitre().empty()) {
        type = achat;
    }
    else {
        type = static_cast<TypeTransaction>(rand() % 3);
    }
    cout <<"506"<<endl;
    if (type == rienAFaire) {
        return Transaction(rienAFaire, "", 0);
    }
    else if (type == achat) {
        vector<PrixJournalier> Pj = bour.getPrixJournaliersAujourdhui();
        int n =(int) Pj.size();
        if (n>0){
        int choixDAction = rand() % Pj.size();
        cout << choixDAction << endl;
        double QteDispo = portefeuille.getSolde() / Pj[choixDAction].getPrix();
        int maxQte = floor(QteDispo);
        cout << "3" << endl;
        int choixQte = 1 + rand() % maxQte;
        cout << "3" << endl;
        return Transaction(achat, Pj[choixDAction].getNomAction(), choixQte);
    }}
    else {
        cout << "5" << endl;
        vector<Titre> Pt = portefeuille.getTitre();
        int n = Pt.size();
        int choixDAction = rand() % n;
        int x = Pt[choixDAction].getQte();
        int choixQte = 1 + rand() % x;
        return Transaction(vente, Pt[choixDAction].getNomAction(), choixQte);
    }
}
*/
// trader algorithmique 1
class TraderAlgo1 :public Trader{
public:
    Transaction choisirTransaction(const Bourse& , const Portefeuille &);
};

Transaction TraderAlgo1::choisirTransaction(const Bourse&bourse , const Portefeuille &portefeuille){
	int qte=0;
	Transaction t(TypeTransaction,string,int);	
	vector<PrixJournalier>vPJ=bourse.getPrixJournaliersDispoAujourdhui(portefeuille.getSolde());
    cout<< vPJ.size() << endl;
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
/*
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
};*/

/*Transaction TraderBollin::choisirTransaction(const Bourse& bour, const Portefeuille & portef){
    double ss=portef.getSolde();
    vector<PrixJournalier> vPj=bour.getPrixJournaliersDispoAujourdhui(ss);
    sort(vPj.begin(), vPj.end(), [](PrixJournalier pj1, PrixJournalier pj2){ return pj1.getPrix() < pj2.getPrix(); });
    bool achatNecess=((portef.getTitre()).size()==0);
    if (achatNecess){
       double QteDispo=portef.getSolde()/(vPj[0].getPrix());
        if(QteDispo>3){return Transaction(achat,vPj[0].getNomAction(),3);}
        else if(QteDispo>2){return Transaction(achat,vPj[0].getNomAction(),2);}
        else{return Transaction(achat,vPj[0].getNomAction(),1);}
    }
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
                for (unsigned int i = historique1Action.size() - 1; i >= historique1Action.size() - 10; i--) {
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
}*/

/*
class TraderBollin : public Trader {
private:
    vector<pair<double, int>> MoydAction; // moving average and number of instances for each action
public:
    Transaction choisirTransaction(const Bourse&, const Portefeuille&);
    inline bool casdVente(double lastprix, double Bornesup) { return Bornesup < lastprix; };
    inline bool casdAchat(double lastprix, double Borneinf) { return Borneinf > lastprix; };
    inline double bornInf(double moy, double eT) { return (moy - 3 * eT); }
    inline double bornSup(double moy, double eT) { return (moy + 3 * eT); }
    void mettreajour(vector<pair<double, int>>&, const PrixJournalier&,const Bourse& );
};

Transaction TraderBollin::choisirTransaction(const Bourse& bour, const Portefeuille& portef) {
    double ss = portef.getSolde();
    vector<PrixJournalier> vPj = bour.getPrixJournaliersDispoAujourdhui(ss);
    sort(vPj.begin(), vPj.end(), [](PrixJournalier pj1, PrixJournalier pj2) { return pj1.getPrix() < pj2.getPrix(); });
    bool achatNecess = ((portef.getTitre()).size() == 0);
    if (achatNecess) {
        double QteDispo = portef.getSolde() / (vPj[0].getPrix());
        if (QteDispo > 3) { return Transaction(achat, vPj[0].getNomAction(), 3); }
        else if (QteDispo > 2) { return Transaction(achat, vPj[0].getNomAction(), 2); }
        else { return Transaction(achat, vPj[0].getNomAction(), 1); }
    }
    for (auto pj : vPj) {
        bool pasmisajour = find(bour.getActionDisponibleAujourdhui().begin(), bour.getActionDisponibleAujourdhui().end(), pj.getNomAction()) == bour.getActionDisponibleAujourdhui().end();

        if ((pj.getPrix() > portef.getSolde()) && pasmisajour)  break;
        else {
            string nomdActi = pj.getNomAction();
            vector<PrixJournalier> historique1Action = bour.getHistoriqueAction(nomdActi);
            mettreajour(MoydAction, pj,bour);
            double sommeDiff = 0.0;
            double ecartType;
            //calcul decart type en se basant au plus sur les 10 derniers val
                if (historique1Action.size() > 10) {
                 for (unsigned int i = historique1Action.size() - 1; i >= historique1Action.size() - 10; i--) {
                     double diff = historique1Action[i].getPrix() - MoydAction[i].first;
                     sommeDiff += diff * diff;
                    }
                 ecartType = sqrt(sommeDiff / 10);
                }
                else {
                 for (int i = 0; i < historique1Action.size(); i++) {
                        double diff = historique1Action[i].getPrix() - MoydAction[i].first;
                        sommeDiff += diff * diff;
                 }
            ecartType = sqrt(sommeDiff / historique1Action.size());
            }
            double bornesup = bornSup(MoydAction[historique1Action.size() - 1].first, ecartType);
            double borneinf = bornInf(MoydAction[historique1Action.size() - 1].first, ecartType);
            int nbActions = MoydAction[historique1Action.size() - 1].second;
            if (casdVente(pj.getPrix(), bornesup) && (nbActions > 0)) {
                return Transaction(vente, nomdActi, min(3, nbActions));
            }
            else if (casdAchat(pj.getPrix(), borneinf) && (portef.getSolde() >= pj.getPrix())) {
            double QteDispo = portef.getSolde() / (pj.getPrix());
            if (QteDispo > 3) { return Transaction(achat, nomdActi, 3); }
            else if (QteDispo > 2) { return Transaction(achat, nomdActi, 2); }
            else { return Transaction(achat, nomdActi, 1); }
            }
        }
    }
    return Transaction(rienAFaire, "", 0);
}

void TraderBollin::mettreajour(vector<pair<double, int>>& v, const PrixJournalier& p,const Bourse& bour) {
string nomActi = p.getNomAction();
double lastPrix = p.getPrix();
int i = 0;
for (auto& paire : v) {
if (paire.second > 0 && bour.getActionDisponibleAujourdhui()[i] == nomActi) {
paire.first = (paire.first * paire.second + lastPrix) / (paire.second + 1);
paire.second++;
return;
}
i++;
}
v.push_back(make_pair(lastPrix, 1));
}
*/

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
    //vector<PrixJournalier>PrixJactionen=bour.getPrixJournaliersAujourdhui();
    cout<< "lmarchi fih pj  dispo :" <<PrixJournaliers.size() << endl;
    //cout<< "lmarchi fih  pj khw  :" <<PrixJactionen.size() << endl;
    cout<< "portefill fih "<<portef.getTitre().size()<<endl;
    //vector<PrixJournalier> PrixJournaliers = vPJ;
    if (portef.getTitre().size() == 0) {
        cout << "portef feragh "<<endl ; 
        PrixJournalier pluscher=PrixJournaliers[0];
        for (int i = 1; i < PrixJournaliers.size(); i++) {
             if (PrixJournaliers[i].getPrix() > pluscher.getPrix()) {
                 pluscher = PrixJournaliers[i]; // update most expensive
             }
        }

        double qteDispo = portef.getSolde() / pluscher.getPrix();
        int qte = min(3, static_cast<int>(qteDispo));
        return Transaction(TypeTransaction::achat, pluscher.getNomAction(), floor(qteDispo));
    }
    bool triedAll=false;
    for (const PrixJournalier& prixJournalier : PrixJournaliers) {
        const string nomAction = prixJournalier.getNomAction();
        if (prixJournalier.getPrix() > portef.getSolde() ) {
        //|| find(bour.getActionDisponibleAujourdhui().begin(), bour.getActionDisponibleAujourdhui().end(), nomAction) == bour.getActionDisponibleAujourdhui().end()
            continue;
        }
        cout <<prixJournalier.getNomAction() << endl;
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

        if (bornSup < dernierPrix) {
            for (const Titre& titre : portef.getTitre()) {
                if (titre.getNomAction() == nomAction) {
                    int qte = titre.getQte();
                    return Transaction(TypeTransaction::vente, nomAction, qte);
                }
            }
        }
        else if (bornInf > dernierPrix) {
            double qteDispo = portef.getSolde() / prixJournalier.getPrix();
            int qte = min(3, static_cast<int>(qteDispo));
            return Transaction(TypeTransaction::achat, nomAction, qte);
        }
        if (&prixJournalier == &PrixJournaliers.back()){
        triedAll = true;
        cout<<"ARRIVED"<<endl;
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
