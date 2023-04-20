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
	 void modifierSoldePortefeuille(Portefeuille& portefeuille, double nouveauSolde) {
    }
public:
	//Simulation(const Date d1, const Date d2, double b):debut(d1),fin(d2),budget(b){}
	Simulation( double b):budget(b){}
	static void executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double soldeInit);
	
};

 void Simulation::executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double soldeInit)
{
	Portefeuille portefeuille(soldeInit);
	bourse.dateAujourdhui=dateDebut;
	string action;
	int qte;
	double prix;
	while(bourse.dateAujourdhui<dateFin)
	{
		
		trader.choisirTransaction(bourse,portefeuille);		
		while(1)
		{	
				if((trader.choisirTransaction(bourse,portefeuille)).getTypeTx()==rienAFaire)
					break;
				else if ((trader.choisirTransaction(bourse,portefeuille)).getTypeTx()==achat)
				{
					action=trader.choisirTransaction(bourse,portefeuille).getnomdAction();
					qte=trader.choisirTransaction(bourse,portefeuille).getqtedAction();
					prix=bourse.getPrixAujourdhui(action);
					portefeuille.solde-=qte*prix;
					portefeuille.ajouterTitre(action,qte);
					
				}
				else if ((trader.choisirTransaction(bourse,portefeuille)).getTypeTx()==vente)
				{
					action=trader.choisirTransaction(bourse,portefeuille).getnomdAction();
					qte=trader.choisirTransaction(bourse,portefeuille).getqtedAction();
					prix=bourse.getPrixAujourdhui(action);
					portefeuille.solde+=qte*prix;
					portefeuille.retirerTitre(action,qte);
				}
		}
		
		
		
		(bourse.dateAujourdhui).incrementerDate();
	}
	
	
	
}






















#endif 
