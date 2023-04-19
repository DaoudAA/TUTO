#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include "Bourse.h"
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;
vector<string>BourseVector::getActionDisponibleParDate(const Date &d){
    vector<string>actions;
    if(d<dateAujourdhui){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
        for(unsigned int i=0;i<pj.size();i++)
        	if (!(appartientAction(pj[i].getNomAction(),actions)))
            	actions.push_back(pj[i].getNomAction());
    }
    return actions;
}
vector<PrixJournalier> BourseVector::getPrixJournaliersParDate(const Date &d){
    vector<PrixJournalier> prixJParDate;
    if(d<dateAujourdhui){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
        for(unsigned int i=0;i<pj.size();i++)
        if(!(appartientPrixJournalier(pj[i],prixJParDate)))	
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

vector<string>BourseVector2::getActionDisponibleParDate(const Date &d){
    vector<string>actions;
    int i=0;
    while((d<dateAujourdhui)&&(i<historique.size()))
	{
		while((historique[i].getDate()==d)&&(i<historique.size()))
		{
			if (!(appartientAction(historique[i].getNomAction(),actions)))
				actions.push_back(historique[i].getNomAction());
			i++;
		}
		if(historique[i].getDate()>d)
			return actions;   		
	}
    return actions;
	
}

bool appartientAction (string nomAction,vector<string>& vecteurActions){
	if(vecteurActions.size()==0)return false;
	for(int i=0;i<vecteurActions.size();i++)
	{
		if(vecteurActions[i]==nomAction)
			return true;
	}
	return false;
}

vector<PrixJournalier>BourseVector2::getPrixJournaliersParDate(const Date &d){
    vector<PrixJournalier>prixJParDate;
    int i=0;
    while((d<dateAujourdhui)&&(i<historique.size()))
	{
		while((historique[i].getDate()==d)&&(i<historique.size()))
		{
			if(!(appartientPrixJournalier(historique[i],prixJParDate)))
				prixJParDate.push_back(historique[i]);
			i++;
		}
		if(historique[i].getDate()>d)
			return prixJParDate;   		
	}
    return prixJParDate;
	
}
bool appartientPrixJournalier (PrixJournalier pj,vector<PrixJournalier>& vecteurPrixJournalier){
	if(vecteurPrixJournalier.size()==0)return false;
	for(int i=0;i<vecteurPrixJournalier.size();i++)
	{
		if(vecteurPrixJournalier[i]==pj)
			return true;
	}
	return false;
}
vector<PrixJournalier>Bourse::getPrixJournaliersDispoAujourdhui(double solde)
	{
		vector<PrixJournalier>resultat;
		if ((solde<0)||((this->getPrixJournaliersAujourdhui()).size()==0))return resultat;
		int i=0;
		while ((i<(this->getPrixJournaliersAujourdhui()).size())&&((this->getPrixJournaliersAujourdhui())[i].getPrix()<solde))
		{
			if(!(appartientPrixJournalier((this->getPrixJournaliersAujourdhui())[i],resultat)))	
				resultat.push_back((this->getPrixJournaliersAujourdhui())[i]);
			i++;
		}
		return resultat;
	}

int main()
{

    string ch1;
    //PrixJournalier Pj;
    ch1="./prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
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
