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
	vector<PrixJournalier> Pj;
	//dictionnaire pour les statistiques
    map <string, long> stats;

	while(bourse.dateAujourdhui<dateFin)
	{   
		cout<<"0"<<endl;
		//dans une meme journee
		//stats pour la fct getPrixJournalierAujourdhui

		auto start = chrono::high_resolution_clock::now();
		cout<<"a"<<endl;
		Pj=bourse.getPrixJournaliersAujourdhui();
		cout<<"b"<<endl;
		auto stop = chrono::high_resolution_clock::now();
		cout<<"c"<<endl;
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		cout<<"d"<<endl;
		stats["Temps_GetPrixJournalierAujourdhui_µs"]+=duration.count();
		cout<<"e"<<endl;
		stats["Nbr_fois_appelauPJA"]++;
		cout<<"f"<<endl;
		//stats pour la fct getActionDisponibleAujourdhui
		Date dd=bourse.dateAujourdhui;
		cout<<"*****"<<endl;
		if(!Pj.empty()){
			cout<<"1"<<endl;
			start = chrono::high_resolution_clock::now();
			vector<string> Actions=bourse.getActionDisponibleAujourdhui();
			stop = chrono::high_resolution_clock::now();
			duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			stats["Temps_GetActionDisponibleAujourdhui_µs"]+=duration.count();
			// les choix de transactions dans une meme journee
			int i=0;
			cout<<"i="<<i<<endl;
			while(i<100)
			{	cout<<"2"<<endl;
				//stats pour la fct choisirTransaction
				stats["NombreDeTransaction"]++;
				start = chrono::high_resolution_clock::now();
				Transaction T=trader.choisirTransaction(bourse ,portefeuille); 
				cout<<"kamalna transaction f simulation"<<endl;
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
							cout<<"le prix d'achat"<<prix<<endl;
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
								cout<<"last prix de laction="<<prix<<endl;
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
			cout<<"3"<<endl;
			stats["Nbr_de_Jours"]++;
			dd.incrementerDate();
			cout<<"\t JOUR SUIVANT : "<<dd<<endl ; 
		}
		(bourse.dateAujourdhui).incrementerDate();
		cout<<"4";

	}
	if(portefeuille.getTitre().size()>0){
		cout<<"5"<<endl;
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
	cout<<"7"<<endl;
	stats["soldeFinal"]=portefeuille.getSolde();
	cout<<"soldecbon"<<endl;
	stats["Taux_du_gain_en_%"]=(stats["soldeFinal"]/soldeInit*100)-100;
	cout<<"taux du gain cbon"<<endl;
	if(stats["NombreDeTransaction"])
		stats["temps_moyen_transaction"]=stats["Temps_ChoixTransaction_µs"]/stats["NombreDeTransaction"];
	cout<<"temps moyen1 cbon"<<endl;
	if(stats["Nbr_fois_appelauPJA"]!=0)
		stats["temps_moyen_getPJparDate"]=stats["Temps_GetPrixJournalierAujourdhui_µs"]/stats["Nbr_fois_appelauPJA"];
	cout<<"temps moyen2 cbon"<<endl;
	if(stats["nombreDVente"]!=0)
		{stats["temps_moyen_de_getlastprix"]=stats["Temps_getLPrixAction"]/stats["nombreDVente"];}
	cout<<"temps moyen getLast prixcbon"<<endl;
	cout<<"kamalna simulation"<<endl;
	return stats;

}
#endif 
