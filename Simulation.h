#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include "Bourse.h"
#include "portefeuille.h"
#include "trader.h"
#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<chrono>
#include <random>
using namespace std;
class Simulation{
private:
//	const Date debut;
//	const Date fin;
	double budget;
public: 
	//Simulation(const Date d1, const Date d2, double b):debut(d1),fin(d2),budget(b){}
	Simulation( double b):budget(b){}
	static map <string , long > executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double soldeInit);
	//map <string,long>

};
map <string , long > Simulation::executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double soldeInit)
{
	Portefeuille portefeuille(soldeInit);
	bourse.setDateaujourdhui(dateDebut);
	string action;
	int qte;
	double prix;
	//dictionnaire pour les statistiques
    map <string, long> stats;
	while(bourse.dateAujourdhui<dateFin)
	{   //cout<<"1"<<endl ; 
		//dans une meme journee
		//stats pour la fct getPrixJournalierAujourdhui
		stats["getPrixJournaliersAujourdhui"]++;
		auto start = chrono::high_resolution_clock::now();
		//cout<<"chronostart"<<endl ; 
		vector<PrixJournalier> Pj=bourse.getPrixJournaliersAujourdhui();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		//cout<<"getPJaujourd"<<endl ; 
		stats["Temps_GetPrixJournalierAujourdhui_µs"]+=duration.count();
		//stats pour la fct getActionDisponibleAujourdhui
		start = chrono::high_resolution_clock::now();
		stats["getActionDisponibleAujourdhui"]++;
		vector<string> Actions=bourse.getActionDisponibleAujourdhui();
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		stats["Temps_GetActionDisponibleAujourdhui_µs"]+=duration.count();
		// les choix de transactions dans une meme journee
		//cout<<"6"<<endl ; 
		int i=0;
		while(i<100)
		{	//cout<<"1"<<endl ; 
			//stats pour la fct choisirTransaction
		    stats["NombreDeTransaction"]++;
			cout<<"Trader en acceuil "<<endl;
		    start = chrono::high_resolution_clock::now();
			Transaction T=trader.choisirTransaction(bourse ,portefeuille);
			//cout<<"2"<<endl ; 
			//cout << T.getnomdAction() << T.getqtedAction() << endl ; 
			stop = chrono::high_resolution_clock::now();
			duration =chrono::duration_cast<chrono::microseconds>(stop-start);
			//cout<<"2"<<endl ; 
			stats["Temps_ChoixTransaction_µs"]+=duration.count();
			//cout<<"2"<<endl ; 
			const string actionNom = T.getnomdAction();
			//cout<<"2"<<endl ; 
				if(T.getTypeTx()==rienAFaire){
				    stats["nombreDRienAFaire"]++;
					cout<<"JOUR SUIVANT : "<<bourse.dateAujourdhui<<endl ; 
					break;
				}
				else if ((T.getTypeTx()==achat)&&(T.getqtedAction()>0)){
					stats["nombreDAchat"]++;
					cout<<"Achat dans sim "<<endl ; 
					string str=	T.getnomdAction()	;			
					bool found = appartientAction(str,Actions);
					//cout<<Actions.size()<<endl;
					if (found ){cout<<"ma<joud"<<endl ; }
					//cout<<"dec found"<<endl ;
					//cout <<portefeuille.getSolde() <<"\t" << bourse.getPrixAujourdhui(T.getnomdAction()) << endl; 
					//system("pause");
					double p=bourse.getPrixAujourdhui(T.getnomdAction());
				    if ((portefeuille.getSolde()>=p)) {
						//cout<<"found"<<endl ;
						stats["getPrixAujourdhui(action)/NbDachatachevees"]++;
					    action=T.getnomdAction();
					    qte=T.getqtedAction();
					    prix=p;
					    portefeuille.achatTitre(action,qte,prix);
					}
				}
				else if ((T.getTypeTx()==vente)&&(T.getqtedAction()>0)){
					stats["nombreDVente"]++;
					cout<<"V"<<endl ; 
					for(unsigned int i=0;i<(portefeuille.titres).size();i++){
						if ((portefeuille.titres)[i].getNomAction() == actionNom){
							action=T.getnomdAction();
							qte=T.getqtedAction();//chrono 
							prix=bourse.getLastPrixAction(action);
							stats["getLastPrixAction/NbDventeachevees"]++;
							portefeuille.venteTitre(action,qte,prix);
						}
						//else
					}
				}
				i++;
		}
		(bourse.dateAujourdhui).incrementerDate();
	}
	return stats;
}
#endif 
