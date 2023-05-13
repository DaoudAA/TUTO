#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include "Bourse.h"
#include<vector>
#include<iostream>
#include<fstream>
#include <chrono>

using namespace std;
int main()
{
    /*string ch1;
    ch1="../prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    Date date(4,1,2010);
    Date Da(8,1,2010);
    Bourse * b1=new BourseVector(vPj);
    b1->setDateaujourdhui(date);
    long long tempss=0;
    cout<<"b1-> date "<<b1->getDateAujourdhui()<<endl;
    cout<<"date "<<date <<endl;
    while ((b1->getDateAujourdhui())<=Da){
    //cout << "0" <<endl;
    auto start = chrono::high_resolution_clock::now();
    vector<PrixJournalier>PJAction=(*b1).getPrixJournaliersAujourdhui();
	auto stop = chrono::high_resolution_clock::now();
	auto duration =chrono::duration_cast<chrono::microseconds>(stop-start);
	tempss+=duration.count();
    cout <<"size = "<< PJAction.size() << endl; 
    if(PJAction.size()==0){date.incrementerDate();
    cout<<"Jour Suivant "<<date<<endl;
    b1->setDateaujourdhui(date);continue;}
    //vector<string>PJActionen=(*b1).getActionDisponibleParDate(date);
    //cout << PJActionen.size()<<endl;
    //for (auto elt :PJAction){cout << elt <<endl;}
        //if(PJAction.size()!=0){
        //cout<<endl<<"PJParAction: JCI"<<endl;
        //    for(unsigned int i=0;i<PJAction.size();i++)
        //    cout<<PJAction[i]<<endl;
      //  }
    date.incrementerDate();
    cout<<"Jour Suivant "<<date<<endl;
    b1->setDateaujourdhui(date);
    }
    cout << "temps duree pour le get pj  " <<tempss << endl;
    //double p=(*b1).getPrixAujourdhui("NBL",b1->getActionDisponibleAujourdhui());
    //cout << p << endl; */
    return 0;
}
