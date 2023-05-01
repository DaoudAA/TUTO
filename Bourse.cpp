#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include "Bourse.h"
#include<vector>
#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    string ch1;
    ch1="../prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    Date date(1,04,2010);
    Bourse * b1=new BourseVector(vPj);
    b1->setDateaujourdhui(date);
    cout << "0" <<endl;
    vector<PrixJournalier>PJAction=(*b1).getPrixJournaliersDispoAujourdhui(1000.0);
    cout <<"size = "<< PJAction.size() << endl; 
            if(PJAction.size()!=0)
    {
        cout<<endl<<"PJParAction: JCI"<<endl;
        for(unsigned int i=0;i<PJAction.size();i++)
        cout<<PJAction[i]<<endl;
    }
    double p=(*b1).getPrixAujourdhui("NBL",b1->getActionDisponibleAujourdhui());
    cout << p << endl; 
    return 0;
}
