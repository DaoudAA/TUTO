#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include "Bourse.h"
#include "portefeuille.h"
#include"trader.h"
#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<chrono>

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
		stats["getPrixJournaliersAujourdhui"]++;
		auto start = chrono::high_resolution_clock::now();
		vector<PrixJournalier> Pj=bourse.getPrixJournaliersAujourdhui();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		stats["Temps_GetPrixJournalierAujourdhui_µs"]+=duration.count();
		//stats pour la fct getActionDisponibleAujourdhui
		auto start = chrono::high_resolution_clock::now();
		stats["getActionDisponibleAujourdhui"]++;
		vector<string> Actions=bourse.getActionDisponibleAujourdhui();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		stats["Temps_GetActionDisponibleAujourdhui_µs"]+=duration.count();
		// les choix de transactions dans une meme journee
		while(1)
		{	//stats pour la fct choisirTransaction
		    stats["choisirTransaction"]++;
		    auto start = chrono::high_resolution_clock::now();
			Transaction T=trader.choisirTransaction(bourse ,portefeuille);
			auto stop = chrono::high_resolution_clock::now();
			auto duration =chrono::duration_cast<chrono::microseconds>(stop-start);
			stats["Temps_ChoisirTransaction_µs"]+=duration.count();
			const string& actionNom = T.getnomdAction();
				if(T.getTypeTx()==rienAFaire){
				    stats["nombreDRienAFaire"]++;
					break;
				}
				else if ((T.getTypeTx()==achat)&&(T.getqtedAction()>0)){
					stats["nombreDAchat"]++;
					bool found = appartientAction(T.getnomdAction(),Actions);
				    if (found&&(portefeuille.getSolde()>=bourse.getPrixAujourdhui(T.getnomdAction()))) {
						stats["getPrixAujourdhui(action)"]++;
					    action=T.getnomdAction();
					    qte=T.getqtedAction();
					    prix=bourse.getPrixAujourdhui(action);
					    portefeuille.achatTitre(action,qte,prix);
					}
				}
				else if ((T.getTypeTx()==vente)&&(T.getqtedAction()>0)){
					stats["nombreDVente"]++;
					for(int i=0;i<(portefeuille.titres).size();i++){
						if ((portefeuille.titres)[i].getNomAction() == actionNom){
							action=T.getnomdAction();
							qte=T.getqtedAction();
							prix=bourse.getLastPrixAction(action);
							stats["getLastPrixAction"]++;
							portefeuille.venteTitre(action,qte,prix);
						}
						//else
					}
				}
		}
		(bourse.dateAujourdhui).incrementerDate();
	}
}
#endif 
