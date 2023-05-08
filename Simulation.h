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
	{   
		//dans une meme journee
		//stats pour la fct getPrixJournalierAujourdhui

		auto start = chrono::high_resolution_clock::now();
		vector<PrixJournalier> Pj=bourse.getPrixJournaliersAujourdhui();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		stats["Temps_GetPrixJournalierAujourdhui_µs"]+=duration.count();
		//stats pour la fct getActionDisponibleAujourdhui
		start = chrono::high_resolution_clock::now();
		vector<string> Actions=bourse.getActionDisponibleAujourdhui();
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		stats["Temps_GetActionDisponibleAujourdhui_µs"]+=duration.count();
		// les choix de transactions dans une meme journee
		int i=0;
		while(i<100)
		{	
			//stats pour la fct choisirTransaction
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
					
					//bool found = appartientAction(actionNom,Actions);
					double p=bourse.getPrixAujourdhui(T.getnomdAction(),Actions);
				    if ((portefeuille.getSolde()>=p)&& (p>0.5)) {
						stats["nombreDAchat"]++;
						cout <<portefeuille.getSolde() <<"\t" << p << endl; 
					    action=T.getnomdAction();
					    qte=T.getqtedAction();
					    prix=p;
					    portefeuille.achatTitre(action,qte,prix);
					cout<<"Achat de "<<T.getqtedAction()<<" of "<<T.getnomdAction()<<endl ;
					}
				}
				else if ((T.getTypeTx()==vente)&&(T.getqtedAction()>0)){
					
					for(unsigned int i=0;i<(portefeuille.titres).size();i++){
						if ((portefeuille.titres)[i].getNomAction() == actionNom){
							stats["nombreDVente"]++;
							action=T.getnomdAction();
							qte=T.getqtedAction();
							prix=bourse.getLastPrixAction(action);
							stats["NombreDActionsPresentesLorsDuDernierJour"]++;
							portefeuille.venteTitre(action,qte,prix);
					cout<<"Vente de "<<T.getqtedAction()<<" of "<<T.getnomdAction()<<endl ; 
						}

					}
				}
				i++;
				cout<<"solde du portefeuille"<<portefeuille.getSolde();
		}
		(bourse.dateAujourdhui).incrementerDate();

	}
	if(portefeuille.getTitre().size()>0){
	for(unsigned int i=0;i<portefeuille.getTitre().size();i++){
		if(portefeuille.getTitre()[i].getQte()>0){
			action=portefeuille.getTitre()[i].getNomAction();
			qte=portefeuille.getTitre()[i].getQte();
			prix=bourse.getLastPrixAction(action);
			stats["NombreDActionsPresentesLorsDuDernierJour"]++;
			portefeuille.venteTitre(action,qte,prix);
			stats["nombreDVentes"]++;
		}
	}	
	}
	stats["soldeFinal"]=portefeuille.getSolde();
	stats["Taux_du_gain_en_%"]=stats["soldeFinal"]/soldeInit*100-100;
	return stats;

}
#endif 
