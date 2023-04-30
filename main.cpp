#include "Simulation.h"
#include "Date.h"
#include <iostream>
int main(){
    string ch1;
    ch1="../prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    Bourse * bourse=new BourseVector(vPj);
    //cout << (*bourse).getHistoriqueAction("LVLT")[0]<<endl ; 
    Trader * trader=new TraderBollin1;
    map <string , long > statiktiks;
    double soldeInit=800;
    Date dateDebut(4,1,2010);
    Date dateFin(5,1,2010);
    /*do {
        cout << "Solde Initial : "<< endl; 
        cin >> soldeInit ;
    }while (soldeInit<0) ;*/
    Simulation Sim(soldeInit);
    /*do {
        cout << "date Debut : "<< endl; 
        cin >> dateDebut ;
    }while (dateDebut>Date(31,12,2016));
    do {
        cout << "date Fin : "<< endl; 
        cin >> dateFin ;
    }while ((dateFin<dateDebut )&&(dateFin<Date(1,1,2010))) ;*/
    
    /*for (Date d=dateDebut;d<dateFin;d.incrementerDate()){
        TestDate test
        cout << d;
         }*/
   statiktiks=Sim.executer(*bourse,*trader,dateDebut,dateFin,soldeInit);
    cout<< "Stats : "<<endl;
    for(auto elt : statiktiks){
        cout << elt.first << " : \t" <<  elt .second << endl ; 
    }
    return 0 ;
}
