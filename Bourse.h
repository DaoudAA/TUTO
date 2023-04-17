#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include<vector>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class BourseVector{
private:
    vector<PrixJournalier>historique;
    const Date dateFinRecherche;

public:
    BourseVector(){};
    BourseVector(vector<PrixJournalier>&b,const Date &d):historique(b),dateFinRecherche(d){};
    vector<string> getActionDisponibleParDate(const Date &);
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &);
    vector<PrixJournalier> getPrixJournaliersDAujourdhui();
    Date getDateFinRecherche()const{return dateFinRecherche;}

};
vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier>,const Date&);
/*set fi 3oudh vector w set connait si il existe redondances ou non  pushback->insert */
#endif // BOURSE_H_INCLUDED
