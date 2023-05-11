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
#include <map>
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
    TypeTransaction type;

    if (portefeuille.getTitre().empty()) {
        if (bour.getPrixJournaliersDispoAujourdhui(portefeuille.getSolde()).empty()){return Transaction(rienAFaire, "", 0);}
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
    return Transaction(rienAFaire, "", 0);
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
    map<string, pair<double, int>> moydAction;
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
    
    vector<PrixJournalier>PrixJournaliers=bour.getPrixJournaliersAujourdhui();
    vector<PrixJournalier>PrixJactionen=bour.getPrixJournaliersAujourdhui();
    //cout<< "solde restant : " <<portef.getSolde() <<endl;
    //cout<< "lmarchi fih pj  dispo :" <<PrixJournaliers.size() << endl;
    //cout<< "lmarchi fih  pj khw  :" <<PrixJactionen.size() << endl;
    //cout<< "portefill fih "<<portef.getTitre().size()<<endl;
    //vector<PrixJournalier> PrixJournaliers = vPJ;
    //double minPrice = PrixJournaliers.empty() ? 0:1; 
    if (portef.getTitre().size()==0){
        //cout << "portef feragh "<<endl ; 
        vector<PrixJournalier>PJdispo=bour.getPrixJournaliersDispoAujourdhui(portef.getSolde());
        if (PJdispo.empty()){return Transaction(rienAFaire,"",0);}
        PrixJournalier pluscher=PJdispo[0];
        for (unsigned int i = 1; i < PJdispo.size(); i++) {
            if (PJdispo[i].getPrix() > pluscher.getPrix()) {
                 pluscher = PJdispo[i]; // update most expensive
            }
        }

        double qteDispo = portef.getSolde() / pluscher.getPrix();
        //int qte = min(3, static_cast<int>(qteDispo));
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

        moyenne = ((moyenne * nbInstances) + prixJournalier.getPrix()*2) / (nbInstances + 2);
        ++nbInstances;

        double ecartType = calculerEcartType(historique, moyenne);
        double bornInf = calculerBornInf(moyenne, ecartType);
        double bornSup = calculerBornSup(moyenne, ecartType);

        if (bornSup <= dernierPrix || portef.getSolde()<1) {
            for (const Titre& titre : portef.getTitre()) {
                if (titre.getNomAction() == nomAction) {
                    int qte = titre.getQte();
                    return Transaction(vente, nomAction, qte);
                }
            }
        }
        else if (bornInf > dernierPrix && prixJournalier.getPrix() < portef.getSolde()){
            double qteDispo = portef.getSolde() / prixJournalier.getPrix();
            int qte = min(5, static_cast<int>(qteDispo));
            return Transaction(achat, nomAction, floor(qte));
        }
        if (&prixJournalier == &PrixJournaliers.back()){
        triedAll = true;
        //cout<<"ARRIVED"<<endl;
        }
    }
    if (triedAll){return Transaction(rienAFaire, "", 0);}
    return Transaction(rienAFaire, "", 0);
}
double TraderBollin1::calculerEcartType(const vector<PrixJournalier>& historique, double moyenne) {
double sommeDiffCarrees = 0.0;
int n = historique.size();
int nbValuesToConsider= min(static_cast<int>(floor(n * 0.1)), 10); // only consider 10% of the most recent data or 10 data points, whichever is smaller
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

class TraderReverseMean : public Trader {
private:
    map<string, pair<double, int> > moydAction;

public:
    Transaction choisirTransaction(const Bourse&, const Portefeuille&);

private:
    bool comparePriceDescending(const PrixJournalier& pj1, const PrixJournalier& pj2);
};
bool TraderReverseMean::comparePriceDescending(const PrixJournalier& pj1, const PrixJournalier& pj2){
    return pj1.getPrix() > pj2.getPrix();
}
Transaction TraderReverseMean::choisirTransaction(const Bourse& bour, const Portefeuille& portef) {
    vector<PrixJournalier> PrixJournaliers = bour.getPrixJournaliersAujourdhui();
    for (const PrixJournalier& prixJournalier : PrixJournaliers) {
        const string nomAction = prixJournalier.getNomAction();
        const vector<PrixJournalier>& historique = bour.getHistoriqueAction(nomAction);
        double dernierPrix = bour.getLastPrixAction(nomAction);

        double& moyenne = moydAction[nomAction].first;
        int& nbInstances = moydAction[nomAction].second;

        moyenne = ((moyenne * nbInstances) + prixJournalier.getPrix()) / (nbInstances + 1);
        ++nbInstances;
        int qte=0;
        if (dernierPrix > moyenne ) {
            for (const Titre& titre : portef.getTitre()) {
                if (titre.getNomAction() == nomAction) {
                    qte = titre.getQte();
                }
            }   
            if (qte>0){return Transaction(TypeTransaction::vente, nomAction, qte);}
        }

        
        if (dernierPrix <= moyenne && prixJournalier.getPrix() < portef.getSolde()) {
            double qteDispo = portef.getSolde() / prixJournalier.getPrix();
            int qte = min(5, static_cast<int>(qteDispo));
            return Transaction(TypeTransaction::achat, nomAction, floor(qte));
        }
    }

    return Transaction(TypeTransaction::rienAFaire, "", 0);
}

    


class TraderManuel:public Trader{
    public:
        Transaction choisirTransaction(const Bourse& bour, const Portefeuille& portefeuille);
};
Transaction TraderManuel::choisirTransaction(const Bourse&bourse,const Portefeuille&portefeuille){
    int choixType,i,j,qte;
    string nom;
    //TypeTransaction tx;
    vector<string>v=bourse.getActionDisponibleAujourdhui();  
    Date dateDebut;
    Date dateFin(1,1,2011);
    vector<PrixJournalier>v2;
    vector<PrixJournalier> vs;
    vector<string> vs2 =portefeuille.getNomAction();
    

    double prix;
    while (1){
        cout<<" 1 - Achat"<<endl;
        cout<<" 2 - vente"<<endl;
        cout<<" 3 - Rien a faire"<<endl;
        cout<<" 4 - Acces a l'historique"<<endl;
        do{
            cout<<"\n Choisir une trasaction:\t";
            cin>>choixType;
        }while(choixType>4||choixType<1);
        switch (choixType){
        case 1://achat
            do{
                cout<<" 1 - Liste des prix journaliers disponibles aujourd'hui "<<endl;
                cout<<" 2 - Confirmer l'achat"<<endl;
                cout<<" 3 - Retour"<<endl;
                do{
                    cout<<"\n Votre choix:\t";
                    cin>>i;
                }while(i>3||i<1);
                switch (i)
                {
                case 1:
                    v2=bourse.getPrixJournaliersDispoAujourdhui(portefeuille.getSolde());
                    for(unsigned int i=0;i<v2.size();i++){
                        cout<<v2[i]<<endl;
                    }
                    break;
                case 2:        
                    do{
                        cout<<"Donner le nom de l'action:\t";
                        cin>>nom;    
                    }while(!appartientAction(nom, v));
                    prix=bourse.getPrixAujourdhui(nom,v);
                    do{
                        cout<<"Donner la quantite choisie:\t";
                        cin>>qte;                             
                    }while(qte<0 || portefeuille.getSolde()<(qte*prix));    
                    return Transaction(achat,nom,qte);                 
                case 3:
                    break;
                default:
                    break;
                }
            
            }while(i==1||i==2);
            break;
        case 2://vente
            if(portefeuille.getNomAction().empty()){
                cout<<"\tVous n'avez rien a vendre"<<endl;
            }
             do{
                cout<<endl;
                cout<<" 1 - liste des titres de votre portefeuille "<<endl;
                cout<<" 2 - Voir votre solde"<<endl;
                cout<<" 3 - Confirmer la vente"<<endl;
                cout<<" 4 - Retour"<<endl;
                do{
                    cout<<"\n Votre choix:\t";
                    cin>>i;
                }while(i>4||i<1);  
                switch (i)
                {
                case 1:
                    for(unsigned int i=0;i<portefeuille.getTitre().size();i++){
                        cout<<portefeuille.getTitre()[i];
                    }
                    break;
                case 2:
                    cout<<"Votre solde:\t"<<portefeuille.getSolde()<<endl;
                    break;
                case 3:
                    do{
                        cout<<"Donner le nom de l'action a vendre"<<endl;
                        cin>>nom;
                    }while(!appartientAction(nom,vs2));
                    i=portefeuille.findTitre(nom);
                    int qteMax=portefeuille.getTitre()[i].getQte();
                    do{
                    cout<<"Donner la quantite de l'action a vendre"<<endl;
                    cin>>qte;   
                    }while(qte<0||qte>qteMax);
                    return Transaction(vente,nom,qte);
                                     
                }
                
            }while(i==1||i==2||i==3);

        case 3://rien a faire
            return Transaction(rienAFaire,"",0);
            break;
        case 4://Acces a l'historique
            do{
                cout<<" 1 - Acceceder a l'historique d'une action"<<endl;
                cout<<" 2 - Acceder a l'historique de toutes les actions"<<endl;
                cout<<" 3 - Retour"<<endl;
                do{
                    cout<<"\n Votre choix:\t";
                    cin>>j;
                }while(j>3||j<1);

                
                switch (j)
                {
                    case 1:

                        do{
                            cout<<"Donner date du debut de l'historique (jour/mois/annee)\t";
                            string dateDStr;
                            do { 
                                cin >> dateDStr;                             
                                dateDebut=Date(dateDStr);
                                if (dateDebut.getJour()==-1 || dateDebut.getMois()==-1) {
                                    cout << "Date Invalide. Ressayer: ";
                                }
                            } while (dateDebut.getJour()==-1 || dateDebut.getMois()==-1);

                        }while(dateDebut>bourse.getDateAujourdhui());
                        do{
                            cout<<"Donner date de la fin de l'historique (jour/mois/annee)\t";
                            string dateFStr;
                            do { 
                                cin >> dateFStr;                             
                                dateFin=Date(dateFStr);
                                if (dateFin.getJour()==-1 || dateFin.getMois()==-1) {
                                    cout << "Date Invalide. Ressayer: ";
                                }
                            } while (dateFin.getJour()==-1 || dateFin.getMois()==-1);                            
                        }while((dateDebut>dateFin)&&(dateFin>bourse.getDateAujourdhui())&&dateDebut>Date(4,1,2010));
                        cout<<"Donner le nom de l'action\t";
                        cin>>nom;
                        vs =bourse.getActionParPeriode(dateDebut,dateFin,nom);
                        for( unsigned int i=0;i<vs.size();i++){
                            cout<<vs[i]<<endl;
                        }
                        break;
                    case 2:
                        
                        do{
                            cout<<"Donner date du debut de l'historique (jour/mois/annee)\t";
                            string dateDStr;
                            do { 
                                cin >> dateDStr;                             
                                dateDebut=Date(dateDStr);
                                if (dateDebut.getJour()==-1 || dateDebut.getMois()==-1) {
                                    cout << "Date Invalide. Ressayer: ";
                                }
                            } while (dateDebut.getJour()==-1 || dateDebut.getMois()==-1);

                        }while(dateDebut>bourse.getDateAujourdhui());
                        do{
                            cout<<"Donner date de la fin de l'historique (jour/mois/annee)\t";
                            string dateFStr;
                            do { 
                                cin >> dateFStr;                             
                                dateFin=Date(dateFStr);
                                if (dateFin.getJour()==-1 || dateFin.getMois()==-1) {
                                    cout << "Date Invalide. Ressayer: ";
                                }
                            } while (dateFin.getJour()==-1 || dateFin.getMois()==-1);                            
                        }while((dateDebut>dateFin)&&(dateFin>bourse.getDateAujourdhui()));
                        v2=bourse.getPrixJournalierParPeriode(dateDebut,dateFin);
                        for( unsigned int i=0;i<v2.size();i++){
                            cout<<v2[i]<<endl;
                        }                                       
                        break;
                    case 3:
                        break;                    

                    }
                    
            }while(j==1||j==2);
            break;

           // break;
        }
        break;
    }
    return Transaction(rienAFaire,"",0);
}

#endif
