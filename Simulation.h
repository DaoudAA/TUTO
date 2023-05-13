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
	bourse.dateAujourdhui=dateDebut;
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
		stats["Nbr_fois_appelauPJA"]++;
		//stats pour la fct getActionDisponibleAujourdhui
		Date dd=bourse.dateAujourdhui;
		if(!Pj.empty()){
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
				//dd.incrementerDate();//pourquoi incrementer la date est ici ona deja la ecrit ?
				const string actionNom = T.getnomdAction();
					if(T.getTypeTx()==rienAFaire){
						stats["Nbr_de_Jours"]++;dd.incrementerDate();
						cout<<"\t JOUR SUIVANT : "<<dd<<endl ; //a verfier je pense qu'il a des jours ou il ne les ecrit pas
						break;
					}
					else if ((T.getTypeTx()==achat)&&(T.getqtedAction()>0)){
						
						//bool found = appartientAction(actionNom,Actions);
						double p=bourse.getPrixAujourdhui(T.getnomdAction(),Actions);
						if ((portefeuille.getSolde()>=p)&& (p>0.5)) {
							stats["nombreDAchat"]++;
							//cout <<portefeuille.getSolde() <<"\t" << p << endl; 
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
								action=T.getnomdAction();
								qte=T.getqtedAction();
								auto start1 = chrono::high_resolution_clock::now();
								prix=bourse.getLastPrixAction(action);
								auto stop1 = chrono::high_resolution_clock::now();
								auto duration1 =chrono::duration_cast<chrono::microseconds>(stop1-start1);
								stats["Temps_getLPrixAction"]+=duration1.count();
								stats["NombreDActionsPresentesLorsDuDernierJour"]++;
								portefeuille.venteTitre(action,qte,prix);
								stats["nombreDVente"]++;
								cout<<"Vente de "<<T.getqtedAction()<<" of "<<T.getnomdAction()<<endl ; 
							}

						}
					}
					i++;
					cout<<"solde du portefeuille"<<portefeuille.getSolde()<<endl;
			}
		}
		else{
			stats["Nbr_de_Jours"]++;dd.incrementerDate();
			cout<<"\t JOUR SUIVANT : "<<dd<<endl ; 
		}
		(bourse.dateAujourdhui).incrementerDate();

	}
	if(portefeuille.getTitre().size()>0){
	for(unsigned int i=0;i<portefeuille.getTitre().size();i++){
		if(portefeuille.getTitre()[i].getQte()>0){
			action=portefeuille.getTitre()[i].getNomAction();
			qte=portefeuille.getTitre()[i].getQte();
			auto start = chrono::high_resolution_clock::now();
			action=portefeuille.getTitre()[i].getNomAction();
			auto stop = chrono::high_resolution_clock::now();
			auto duration =chrono::duration_cast<chrono::microseconds>(stop-start);
			stats["Temps_getLPrixAction"]+=duration.count();

			prix=bourse.getLastPrixAction(action);
			stats["NombreDActionsPresentesLorsDuDernierJour"]++;
			portefeuille.venteTitre(action,qte,prix);
			stats["nombreDVente"]++;
		}
	}	
	}
	stats["soldeFinal"]=portefeuille.getSolde();
	stats["Taux_du_gain_en_%"]=(stats["soldeFinal"]/soldeInit*100)-100;
	stats["temps_moyen_transaction"]=stats["Temps_ChoixTransaction_µs"]/stats["NombreDeTransaction"];
	stats["temps_moyen_getPJparDate"]=stats["Temps_GetPrixJournalierAujourdhui_µs"]/stats["Nbr_fois_appelauPJA"];
	stats["temps_moyen_de_getlastprix"]=stats["Temps_getLPrixAction"]/stats["nombreDVente"];
	return stats;

}
#endif 
