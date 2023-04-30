#ifndef PORTEFEUILLE_H_INCLUDED
#define PORTEFEUILLE_H_INCLUDED
#include <iostream>
#include <vector>
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
    friend class Portefeuille;
    friend bool operator==(const Titre& a, const Titre& b);
};

    bool operator==(const Titre& a, const Titre& b){
        if (a.nomAction == b.nomAction) return true;
        return false;
    }



class Portefeuille {
private:
    double solde;
    vector<Titre> titres;
    void achatTitre(const string& nomAction, int quantite,double prix) ;
    void venteTitre(const string& nomAction,int quantite,double prix);
public:
    
    Portefeuille(double s) : solde(s) {}
	double getSolde() const { return solde; }
    vector<Titre> getTitre() const { return titres; }
    friend class Simulation;
    };
	void Portefeuille::achatTitre(const string& nomAction, int quantite,double prix) 
	{   unsigned int i=0;
        while ( i <titres.size()){
            if (nomAction==titres[i].nomAction){
                (titres[i].Qte)+=quantite;
                break;
            }
            i++;
        }
        if (i==titres.size()){
            Titre titre(nomAction, quantite);
            titres.push_back(titre);
        }
        solde-=quantite*prix;
    }
    void Portefeuille::venteTitre(const string& nomAction,int quantite,double prix)
 	{
        unsigned int i=0;
        while ( i !=titres.size()){
            if (nomAction == titres[i].nomAction){
                if (quantite==titres[i].Qte){
                    titres.erase(titres.begin()+i);
                    break;
                }
                titres[i].Qte-=quantite;
            }
            i++;
        }
        solde+=quantite*prix;
    }   
    /* {
        for (auto it = titres.begin(); it != titres.end(); ++it) {
            if (it->getNomAction() == nomAction) {
                titres.erase(it);
                break;
            }
        }
    }*/

#endif
