#ifndef PORTEFEUILLE_H_INCLUDED
#define PORTEFEUILLE_H_INCLUDED
#include <iostream>
#include <vector>
#include "Bourse.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include "PrixJournalier.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Titre {
private:
    string nomAction;
    int Qte;
public:
    Titre(const string& nom, int quantite) : nomAction(nom), Qte(quantite) {}
    string getNomAction() const { return nomAction; }
    int getQte() const { return Qte; }
};

class Portefeuille {
private:
    double solde;
    vector<Titre> titres;
public:
    Portefeuille(double s) : solde(s) {}
	double getSolde() const { return solde; }
    vector<Titre> getTitre() const { return titres; }
	void ajouterTitre(const string& nomAction, int quantite) 
	{
        Titre titre(nomAction, quantite);
        titres.push_back(titre);
    }
    void retirerTitre(const string& nomAction,int quantite);/* {
        for (auto it = titres.begin(); it != titres.end(); ++it) {
            if (it->getNomAction() == nomAction) {
                titres.erase(it);
                break;
            }
        }
    }*/
    friend class Simulation;
    };
#endif
