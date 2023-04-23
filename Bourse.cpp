#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include "Bourse.h"

#include<vector>
#include<iostream>
#include<fstream>

using namespace std;
/*vector<PrixJournalier> BourseVector::getPrixJournaliersDAujourdhui(){
    vector<PrixJournalier>actions;
    BourseVector bv;
    if(bv.getDateFinRecherche()<dateFinRecherche){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,bv.getDateFinRecherche());
        for(unsigned int i=0;i<pj.size();i++)
            actions.push_back(pj[i]);
    }
    return actions;
}*/

vector<string> BourseVector::getActionDisponibleParDate(const Date &d)const{



    vector<string>actions;
    if(d<=dateAujourdhui){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
        for(unsigned int i=0;i<pj.size();i++)
        	if (!(appartientAction(pj[i].getNomAction(),actions)))
            	actions.push_back(pj[i].getNomAction());
    }
    return actions;
}
vector<PrixJournalier> BourseVector::getPrixJournaliersParDate( const Date &d)const{
    vector<PrixJournalier> prixJParDate;
    if(d<=dateAujourdhui){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
        for(unsigned int i=0;i<pj.size();i++)
        if(!(appartientPrixJournalier(pj[i],prixJParDate)))	
            	prixJParDate.push_back(pj[i]);
    }
    return prixJParDate;
}
void rechercheDichotomiqueVector(const Date d,const vector<PrixJournalier> liste,int le,int ri,int mi){
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

vector<string>BourseVector2::getActionDisponibleParDate(const Date &d)const{
    vector<string>actions;
    int i=0;
    while((d<=dateAujourdhui)&&(i<historique.size()))
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

vector<PrixJournalier>BourseVector2::getPrixJournaliersParDate(const Date &d)const{
    vector<PrixJournalier>prixJParDate;
    int i=0;
    while((d<=dateAujourdhui)&&(i<historique.size()))
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
BourseDict::BourseDict(vector<PrixJournalier>&vPJ, Date &d):Bourse(d)
	{	
		map<string, PrixJournalier> element;
		int i=0;
		while((i<vPJ.size())&&(vPJ[i].getDate()<d))
		{
			//element[vPJ[i].getNomAction()]=vPJ[i];
			historique[vPJ[i].getNomAction()].push_back(vPJ[i]);
			i++;	
		}
	}
	
	

map<string, vector<PrixJournalier> > BourseDict::getHistoriqueAction(string action)
{
	map<string, vector<PrixJournalier> > historiqueAction;
	int i=0;
	while(((historique[action])[i].getDate()<=dateAujourdhui)&&(i<historique[action].size()))
	{
		if(!(appartientPrixJournalier(historique[action][i],historiqueAction[action])))
			historiqueAction[action].push_back(historique[action][i]);
		i++;
	}
	return historiqueAction;
}
	
double Bourse::getPrixAujourdhui(string nomAction)
{
	int i=0;
	vector<string> actionsDisponibles = this->getActionDisponibleParDate(dateAujourdhui);
	if(appartientAction(nomAction,actionsDisponibles))
		while(i<(actionsDisponibles).size())
		{
			if(nomAction==(this->getPrixJournaliersAujourdhui()[i]).getNomAction())
				return (this->getPrixJournaliersAujourdhui()[i]).getPrix();
			i++;
		}
}


int main()
{
    string ch1;
    //PrixJournalier Pj;
    ch1="./prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
   // cout << vPj[20]<<endl;
	Date date(17,6,2015);
    BourseVector bourse(vPj,date);
    Date d(17,6,2015);
   /* vector<string>action=bourse.getActionDisponibleParDate(d);
    if(action.size()!=0)
    {   cout<<"action:"<<endl;
        for(unsigned int i=0;i<action.size();i++)
            cout<<action[i]<<" || ";
    }
    /vector<PrixJournalier>PJParDate=bourse.getPrixJournaliersAujourdhui();
    if(PJParDate.size()!=0)
    {
        cout<<endl<<"PJParDate:"<<endl;
        for(unsigned int i=0;i<PJParDate.size();i++)
        cout<<PJParDate[i]<<" || ";
    }*/
    BourseDict b1(vPj,date);
    vector<PrixJournalier>PJAction=b1.getHistoriqueAction("JCI")["JCI"];
        if(PJAction.size()!=0)
    {
        cout<<endl<<"PJParAction: JCI"<<endl;
        for(unsigned int i=0;i<PJAction.size();i++)
        cout<<PJAction[i]<<endl;
    }

    
    

    return 0;
}
