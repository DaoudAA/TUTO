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
    BourseVector(vector<PrixJournalier>&b,const Date &d):historique(b),dateFinRecherche(d){}
    vector<string> getActionDisponibleParDate(const Date &);
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &);

};
vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier>,const Date&);

#endif // BOURSE_H_INCLUDED
