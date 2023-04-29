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
using namespace std;
class Simulation{
private:
//	const Date debut;
//	const Date fin;
	double budget;
	void modifierSoldePortefeuille(Portefeuille& portefeuille, double nouveauSolde) {}
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
	while(bourse.dateAujourdhui<dateFin)
	{
		//dans une meme journée
		vector<PrixJournalier> Pj=bourse.getPrixJournaliersAujourdhui();
		vector<string> Actions=bourse.getActionDisponibleAujourdhui();
		// les choix de transactions dans une meme journée
		while(1)
		{	
			Transaction T=trader.choisirTransaction(bourse ,portefeuille);
			const string& actionNom = T.getnomdAction();
				if(T.getTypeTx()==rienAFaire)
					break;
				else if ((T.getTypeTx()==achat)&&(T.getqtedAction()>0))
				{	bool found = appartientAction(T.getnomdAction(),Actions);
					/*for (int i=0;i<Actions.size();i++) {
						action= Actions[i];
						if (action == T.getnomdAction()) {
    						found = true;
   							break;
    					}
					}*/
					//
				if (found&&(portefeuille.getSolde()>=bourse.getPrixAujourdhui(T.getnomdAction()))) {
					action=T.getnomdAction();
					qte=T.getqtedAction();
					prix=bourse.getPrixAujourdhui(action);
					portefeuille.achatTitre(action,qte,prix);}
				}
				else if ((T.getTypeTx()==vente)&&(T.getqtedAction()>0))
				//for (auto titre : portefeuille.titres){
				for(int i=0;i<(portefeuille.titres).size();i++){
					if ((portefeuille.titres)[i].getNomAction() == actionNom){
						action=T.getnomdAction();
						qte=T.getqtedAction();
						prix=bourse.getPrixAujourdhui(action);
						portefeuille.venteTitre(action,qte,prix);
					}
					//else
				}
		}
		(bourse.dateAujourdhui).incrementerDate();
	}
}
#endif 
