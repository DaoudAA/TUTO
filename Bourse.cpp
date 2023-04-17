#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include "Bourse.h"
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;
vector<PrixJournalier> BourseVector::getPrixJournaliersDAujourdhui(){
    vector<PrixJournalier>actions;
    BourseVector bv;
    if(bv.getDateFinRecherche()<dateFinRecherche){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,bv.getDateFinRecherche());
        for(unsigned int i=0;i<pj.size();i++)
            actions.push_back(pj[i]);
    }
    return actions;
}
vector<string>BourseVector::getActionDisponibleParDate(const Date &d){
    vector<string>actions;
    if(d<dateFinRecherche){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
        for(unsigned int i=0;i<pj.size();i++)
            actions.push_back(pj[i].getNomAction());
    }
    return actions;
}
vector<PrixJournalier> BourseVector::getPrixJournaliersParDate(const Date &d){
    vector<PrixJournalier> prixJParDate;
    if(d<dateFinRecherche){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
        for(unsigned int i=0;i<pj.size();i++)
            prixJParDate.push_back(pj[i]);
    }
    return prixJParDate;
}
void rechercheDichotomiqueVector(Date d,const vector<PrixJournalier> liste,int le,int ri,int mi){
while(le<=ri){
        if(d<liste[mi].getDate()){
            ri=mi-1;
            mi=(ri+le)/2;
        }
        else if(d>liste[mi].getDate()){
            le=mi+1;
            mi=(ri+le)/2;
        }
        else break;
        }
}

vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier> liste,const Date&d)
{
    int left=0;
    int right=liste.size()-1;
    int mid=(right+left)/2;
    rechercheDichotomiqueVector(d,liste,left,right,mid);
    vector<PrixJournalier>resultat;
    bool test=false;
    for(int i=left;i<=right;i++){
        if(d==liste[i].getDate()){
            resultat.push_back(liste[i]);
            test=true;}
        else if(test==true)
            break;
    }
    return resultat;
}


int main()
{
    string ch1;
    //PrixJournalier Pj;
    ch1="F:/Cpp/GitProjects/Tradesim/TradingSimulator/prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    cout << vPj[20]<<endl;
	const Date date(1,3,2010);
    BourseVector bourse(vPj,date);
    const Date d(2,2,2010);
    vector<string>action=bourse.getActionDisponibleParDate(d);
    if(action.size()!=0)
    {   cout<<"action:"<<endl;
        for(unsigned int i=0;i<action.size();i++)
            cout<<action[i]<<" || ";
    }
    vector<PrixJournalier>PJParDate=bourse.getPrixJournaliersParDate(d);
    if(PJParDate.size()!=0)
    {
        cout<<endl<<"PJParDate:"<<endl;
        for(unsigned int i=0;i<PJParDate.size();i++)
        cout<<PJParDate[i]<<" || ";
    }
    return 0;

}
