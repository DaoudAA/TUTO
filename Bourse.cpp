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

//bourse vector
/*vector<PrixJournalier> BourseVector::getPrixJournaliersParDate( const Date &d)const{
    vector<PrixJournalier> prixJParDate;
    if(d<=dateAujourdhui){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
        for(unsigned int i=0;i<pj.size();i++)
        if(!(appartientPrixJournalier(pj[i],prixJParDate)))	
            	prixJParDate.push_back(pj[i]);
    }
    return prixJParDate;
}
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
void rechercheDichotomiqueVector(const Date d,const vector<PrixJournalier> &liste,int le,int ri,int mi){
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
vector<PrixJournalier> BourseVector::getHistoriqueAction(string nomact) const{
    int i=0;
    vector<PrixJournalier> vectRes;
    while(historique[i].getDate()<dateAujourdhui && i<historique.size()){
        if (historique[i].getNomAction()==nomact) vectRes.push_back(historique[i]);
        i++;
    }
return vectRes;
}*/
//bourse vector2 
/*
vector<PrixJournalier>BourseVector2::getPrixJournaliersParDate(const Date &d)const{
    vector<PrixJournalier>prixJParDate;
    int i=0;
    while((d<=dateAujourdhui))//date a chercher respecte regle ud jeu 
	{ 
		while(historique[i].getDate()<= d){
            
            if (historique[i].getDate()==d){
            
			    if(!(appartientPrixJournalier(historique[i],prixJParDate)))//cond redondance
				    {
                        prixJParDate.push_back(historique[i]);}
			}
            i++;
        }
        return prixJParDate;
		if (i==historique.size()) break;   		
	}
    return prixJParDate;
	
}
vector<string>BourseVector2::getActionDisponibleParDate(const Date &d)const{
    vector<string>actions;
    int i=0;
    while((d<=dateAujourdhui)&&(i<historique.size()))
	{
	    if(historique[i].getDate() <= d){
            if((historique[i].getDate()==d)){
			    if (!(appartientAction(historique[i].getNomAction(),actions)))
				    actions.push_back(historique[i].getNomAction());
            }
            i++;
		}
		return actions;   		
	}
    return actions;
	
}
vector<PrixJournalier> BourseVector2::getHistoriqueAction(string nomact) const{
    int i=0;
    vector<PrixJournalier> vectRes;
    while(historique[i].getDate()<=dateAujourdhui && i<historique.size()){
        if (historique[i].getNomAction()==nomact) vectRes.push_back(historique[i]);
        i++;
    }
 return vectRes;
}
*///verif redondance 
/*bool appartientAction (string nomAction,vector<string>& vecteurActions){
	if(vecteurActions.size()==0)return false;
	for(int i=0;i<vecteurActions.size();i++)
	{
		if(vecteurActions[i]==nomAction)
			return true;
	}
	return false;
}*/


//dispo aujourdhui 


	

//BourseDictNom

/*BourseDictNom::BourseDictNom(vector<PrixJournalier> &vPJ){	
	int i=0;
	while(i<vPJ.size()){
		historique[vPJ[i].getNomAction()].push_back(vPJ[i]);
		i++;	
	}
}*/
 
/*vector<PrixJournalier> BourseDictNom::getHistoriqueAction(string action)const
{
	vector<PrixJournalier> historiquedAction;
	while((historique[action])[i].getDate()<=dateAujourdhui){
		if(!(appartientPrixJournalier(historique[action][i],historiquedAction)))
			historiquedAction.push_back(historique[action][i]);
		i++;
	}*/
	/*for(map<string, vector<PrixJournalier> >::const_iterator it = historique.begin();it!=historique.end();++it){
		const string& key = it->first;
		const vector<PrixJournalier>&vPJ=it->second;
		if(key==action){		
			for(int i=0;i<vPJ.size();i++){			
				if(vPJ[i].getDate()<=dateAujourdhui)
					historiquedAction.push_back(vPJ[i]);
				else
					break;
			}
			break;
		}			
	}
	
	
	return historiquedAction;
}
	

	

 vector<PrixJournalier> BourseDictNom::getPrixJournaliersParDate(const Date&date)const
{
	vector<PrixJournalier> resultat;
	int i=0;
	if (date<=dateAujourdhui){
		for(map<string, vector<PrixJournalier> >::const_iterator it = historique.begin();it!=historique.end();++it){
			//const string& key = it->first;
			const vector<PrixJournalier>&vPJ=it->second;
			i=0;
			while(vPJ[i].getDate()<date)
				i++;
			if(vPJ[i].getDate()==date)
				if(!appartientPrixJournalier(vPJ[i],resultat) )
					resultat.push_back(vPJ[i]);			
	  	}
	}
	return resultat;	
}




vector<string> BourseDictNom::getActionDisponibleParDate(const Date&date)const{
	vector<string> resultat;
	int i=0;
	if (date<=dateAujourdhui){
		for(map<string, vector<PrixJournalier> >::const_iterator it = historique.begin();it!=historique.end();++it){
			//const string& key = it->first;
			const vector<PrixJournalier>&vPJ=it->second;
			i=0;
			while(vPJ[i].getDate()<date)
				i++;
			if(vPJ[i].getDate()==date)
				if(!appartientAction(vPJ[i].getNomAction(),resultat) )
					resultat.push_back(vPJ[i].getNomAction());			
	  	}
	}	
	return resultat;
}
*/
//vector<PrixJournalier> BourseDictDate::getHistoriqueAction(string action)
//Bourse Dictionnaire Date 

/*
vector<PrixJournalier> BourseDictDate::getPrixJournaliersParDate(const Date &dateAChercher)const {
    vector<PrixJournalier> vectRes;// const auto elt :historique[dateCopie]
   // const Date d1=dateAChercher;
   // Date dateCopie=d1;
    if (dateAChercher>dateAujourdhui) return vectRes;
    if(historique.find(dateAChercher) != historique.end()){
    for(const auto elt:historique.at(dateAChercher)){
        vectRes.push_back(elt);
        }
    }
    return vectRes;
}

vector<string> BourseDictDate::getActionDisponibleParDate(const Date &dateAChercher)const  {
     vector<string> vectResStr; 
    if (dateAChercher>dateAujourdhui) return vectResStr;
    if(historique.find(dateAChercher)!=historique.end()){
        for(auto it:historique.at(dateAChercher)){
                vectResStr.push_back(it.getNomAction()) ;
            }
    }
    return vectResStr;
}

vector<PrixJournalier> BourseDictDate::getHistoriqueAction(string nomact)const{
    vector<PrixJournalier> vectRes;
    for(auto elt : historique ){
        if(elt.first>dateAujourdhui) return vectRes;
        for (unsigned int i=0;i<elt.second.size();i++){
        if ((elt.second[i]).getNomAction()==nomact){vectRes.push_back(elt.second[i]);}
        }
    }
    return vectRes;
}

*/


int main()
{
    string ch1;
    //PrixJournalier Pj;
    ch1="../prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    //cout << vPj[20]<<endl;
	//Date date(17,6,2015);
   // BourseVector bourse(vPj);
    Date date(1,04,2010);//HOG
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
    Bourse * b1=new BourseVector(vPj);
    //BourseVector2 b1=BourseVector2(vPj);
    b1->setDateaujourdhui(date);
    cout << "0" <<endl;
    vector<PrixJournalier>PJAction=(*b1).getPrixJournaliersDispoAujourdhui(1000.0);
    //vector<string>PJAction=(*b1).getActionDisponibleAujourdhui();
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
