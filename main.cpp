#include "Simulation.h"
#include "Date.h"
#include <iostream>
int main(){
    string ch1;
    ch1="../prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    Bourse * bourse=new BourseVector2(vPj);
    Trader * trader=new TraderBollin1;
    map <string , long > statiktiks;
    double soldeInit=800;
    Date dateDebut(1,4,2010);
    Date dateFin(30,4,2010);
    Simulation Sim(soldeInit);
   statiktiks=Sim.executer(*bourse,*trader,dateDebut,dateFin,soldeInit);
    cout<< "Stats : "<<endl;
    for(auto elt : statiktiks){
        cout << elt.first << " : \t" <<  elt .second << endl ; 
    }
    return 0 ;
}