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

	double budget;
public: 
	Simulation( double b):budget(b){}
	static map <string , long > executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double soldeInit);

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
		stats["Temps_GetPrixJournalierAujourdhui_µs"]+=duration.count();
		//stats pour la fct getActionDisponibleAujourdhui
		start = chrono::high_resolution_clock::now();
		stats["getActionDisponibleAujourdhui"]++;
		vector<string> Actions=bourse.getActionDisponibleAujourdhui();
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		stats["Temps_GetActionDisponibleAujourdhui_µs"]+=duration.count();
		// les choix de transactions dans une meme journee
		 
		int i=0;
		while(i<10){
		    stats["NombreDeTransaction"]++;
		    start = chrono::high_resolution_clock::now();
			Transaction T=trader.choisirTransaction(bourse ,portefeuille);
			stop = chrono::high_resolution_clock::now();
			duration =chrono::duration_cast<chrono::microseconds>(stop-start);
			stats["Temps_ChoixTransaction_µs"]+=duration.count();
			Date dd= bourse.dateAujourdhui;
			dd.incrementerDate();
			const string actionNom = T.getnomdAction();
				if(T.getTypeTx()==rienAFaire){
				    stats["Nbr de Jours"]++;
					cout<<"\t JOUR SUIVANT : "<<dd<<endl ; 
					break;
				}
				else if ((T.getTypeTx()==achat)&&(T.getqtedAction()>0)){
					stats["nombreDAchat"]++;
					bool found = appartientAction(actionNom,Actions);
					
					double p=bourse.getPrixAujourdhui(T.getnomdAction(),Actions);
				    if ((portefeuille.getSolde()>=p)&& (p>0.5)) {
						
						stats["getPrixAujourdhui(action)/NbDachatachevees"]++;
					    action=T.getnomdAction();
					    qte=T.getqtedAction();
					    prix=p;
					    portefeuille.achatTitre(action,qte,prix);
					cout<<"Achat de "<<T.getqtedAction()<<" of "<<T.getnomdAction()<<endl ;
					}
				}
				else if ((T.getTypeTx()==vente)&&(T.getqtedAction()>0)){
					stats["nombreDVente"]++;
					for(unsigned int i=0;i<(portefeuille.titres).size();i++){
						if ((portefeuille.titres)[i].getNomAction() == actionNom){
							action=T.getnomdAction();
							qte=T.getqtedAction();//chrono 
							prix=bourse.getLastPrixAction(action);
							stats["getLastPrixAction/NbDventeachevees"]++;
							portefeuille.venteTitre(action,qte,prix);
					cout<<"Vente de "<<T.getqtedAction()<<" of "<<T.getnomdAction()<<endl ; 
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
