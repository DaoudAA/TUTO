#ifndef PORTEFEUILLE_H_INCLUDED
#define PORTEFEUILLE_H_INCLUDED
#include <iostream>
#include "Bourse.h"
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
    friend ostream& operator<<(ostream& ,const Titre&);
};

    bool operator==(const Titre& a, const Titre& b){
        if (a.nomAction == b.nomAction) return true;
        return false;
    }
    ostream& operator<<(ostream&flux ,const Titre&t){
        flux<<"Nom de l'action:\t"<<t.nomAction<<"\t\t"<<"Quantite:\t"<<t.Qte<<endl;
        return flux;
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
    vector<string>getNomAction()const;
    int findTitre(string)const;
    friend class Simulation;
    };
	void Portefeuille::achatTitre(const string& nomAction, int quantite,double prix) { 
        unsigned int i=0;
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
    void Portefeuille::venteTitre(const string& nomAction,int quantite,double prix){
        unsigned int i=0;
        while ( i !=titres.size()){
            if (nomAction == titres[i].nomAction){
                if (quantite<=titres[i].Qte){
                    titres.erase(titres.begin()+i);
                    break;
                }
                titres[i].Qte-=quantite;
            }
            i++;
        }
        solde+=quantite*prix;
    }   
    vector<string>Portefeuille::getNomAction()const{
        vector<string>resultat;
        for(unsigned int i=0; i<titres.size();i++){
            if(!appartientAction(titres[i].getNomAction(),resultat))
                resultat.push_back(titres[i].getNomAction());
        }
        return resultat;
    }
    int Portefeuille::findTitre(string nom)const{
        for(unsigned int i=0;i<titres.size();i++){
            if(titres[i].getNomAction()==nom)
                return i;
        }
        return -1;
    }
#endif
