#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "PrixJournalier.h"
#include "Date.h"
#include "PersistancePrixJournaliers.h"
#include<vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include<map>
#include<set>


using namespace std;


class Bourse{
	protected:
    Date dateAujourdhui;
public:
    void setDateaujourdhui(Date dd){ dateAujourdhui=dd;}
    
    virtual vector<PrixJournalier>getPrixJournaliersParDate ( const Date &)const = 0;
    virtual vector<string> getActionDisponibleParDate(const Date& ) const = 0;
	virtual vector<PrixJournalier>getHistoriqueAction(string)const = 0 ;
	vector<PrixJournalier>getPrixJournaliersAujourdhui()const{return getPrixJournaliersParDate(dateAujourdhui);}		
    vector<string>getActionDisponibleAujourdhui() const {return getActionDisponibleParDate(dateAujourdhui);}
	vector<PrixJournalier>getPrixJournaliersDispoAujourdhui(double solde)const;
	double getPrixAujourdhui(string);// ona utiliser cette fonction dans l simulation pour donner directement le prix d'une action 
	virtual double getLastPrixAction(string)const ;// il faut s'assurer que le vecteur provenant de gethistoriqueAction est trier par date
	virtual double getAvantDernierPrixDAction(string)const ; // est utilisee dans la partie du trader algorithique 1
    virtual ~Bourse(){};
    friend class Simulation;

};



class BourseVector:public Bourse{
private:
    vector<PrixJournalier>historique;

public:
    BourseVector(vector<PrixJournalier>&b):historique(b){}
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &)const;
    vector<string> getActionDisponibleParDate(const Date &)const;
    vector<PrixJournalier> getHistoriqueAction(string)const;
    ~BourseVector(){}

};
vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier>, const Date&);


class BourseVector2:public Bourse{
private:
	vector<PrixJournalier>historique;
public:
	BourseVector2(vector<PrixJournalier>&b):historique(b){}
    vector<PrixJournalier> getPrixJournaliersParDate(const Date&)const;
	vector<string> getActionDisponibleParDate(const Date&)const;
	vector<PrixJournalier> getHistoriqueAction(string)const;
    ~BourseVector2(){}
		
		
};
bool appartientAction (string nomAction,vector<string>& vecteurActions){
	//cout<<"AAACCCCCCCCCCCCCCCCCCCCC"<<endl ;
	if(vecteurActions.size()==0)return false;
	//cout<<"BBBBBBBBBBBBBBBBBBBBB"<<endl ;
	for(int i=0;i<vecteurActions.size();i++)
	{
		if(vecteurActions[i]==nomAction)
			return true;
	}
	return false;
}
bool appartientPrixJournalier (PrixJournalier pj,vector<PrixJournalier>& vecteurPrixJournalier);

//bourse vector
vector<string> BourseVector::getActionDisponibleParDate(const Date& d) const {
    static map<Date, vector<string>> cache;
    auto it = cache.find(d);
    if (it != cache.end()) {
        return it->second;
    }
    set<string> actions;
    if (d <= dateAujourdhui) {
        vector<PrixJournalier> pj = recherchePrixJournalier(historique, d);
        for (const auto& p : pj) {
            actions.insert(p.getNomAction());
        }
    }
    vector<string> res(actions.begin(), actions.end());
    cache[d] = res;
    return res;
}

/*vector<PrixJournalier> BourseVector::getPrixJournaliersParDate(const Date& d) const {
    static map<Date, vector<PrixJournalier>> cache;
    auto it = cache.find(d);
    if (it != cache.end()) {
        return it->second;
    }
    vector<PrixJournalier> pj;
    if (d <= dateAujourdhui) {
        vector<PrixJournalier> allPj = historique;
        int left = 0, right = allPj.size() - 1, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (allPj[mid].getDate() < d) {
                left = mid + 1;
            } else if (allPj[mid].getDate() > d) {
                right = mid - 1;
            } else {
                break;
            }
        }
        while (mid >= 0 && allPj[mid].getDate() == d) {
            pj.push_back(allPj[mid--]);
        }
        mid = (left + right) / 2;
        while (mid < allPj.size() && allPj[mid].getDate() == d) {
            pj.push_back(allPj[mid++]);
        }
    }
    cache[d] = pj;
    return pj;
}*/
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
/*vector<string> BourseVector::getActionDisponibleParDate(const Date &d)const{
	set<string> actions;
    if (d <= dateAujourdhui) {
        vector<PrixJournalier> pj = recherchePrixJournalier(historique, d);
        for (unsigned int i = 0; i < pj.size(); i++) {
            actions.insert(pj[i].getNomAction());
        }
    }
    return vector<string>(actions.begin(), actions.end());*/
	/*vector<string>actions;
	int i=0;
    if((d<=dateAujourdhui)&&(i<historique.size())){
        vector<PrixJournalier> pj=recherchePrixJournalier(historique,d);
		cout<<pj.size()<<endl;
        for(unsigned int i=0;i<pj.size();i++)
        	if (!(appartientAction(pj[i].getNomAction(),actions)))
            	actions.push_back(pj[i].getNomAction());
    }

    return actions;*/
//}
void rechercheDichotomiqueVector(const Date d,const vector<PrixJournalier> &liste,int le,int ri,int mi){
while(le<=ri){
		mi=(ri+le)/2;
        if(d<liste[mi].getDate()){
            ri=mi-1;
        }
        else if(d>liste[mi].getDate()){
            le=mi+1;
        }
        else break;
        }
}
vector<PrixJournalier>recherchePrixJournalier(vector<PrixJournalier> liste,const Date&d)
{
    int left=0;
    int right=liste.size()-1;
    int mid=(right+left)/2;
    if (!(liste[mid].getDate()==d)) {rechercheDichotomiqueVector(d,liste,left,right,mid);}
    vector<PrixJournalier>resultat;
    bool test=false;
    for(int i=left;i<=right && left<=right ;i++){
        if(d==liste[i].getDate()){
            resultat.push_back(liste[i]);}
        //    test=true;}
        //else if(test==true)
        //    break;
    }
    return resultat;
}
vector<PrixJournalier> BourseVector::getHistoriqueAction(string nomact) const{
    int i=0;
    vector<PrixJournalier> vectRes;
    while(historique[i].getDate()<=dateAujourdhui && i<historique.size()){
        if (historique[i].getNomAction()==nomact){
		vectRes.push_back(historique[i]);
		}	
        i++;
    }
return vectRes;
}


//bourse vector2 


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
    while((d<=dateAujourdhui)&&(i<historique.size())){
	    if(historique[i].getDate() <= d){
            if((historique[i].getDate()==d)){
			    if (!(appartientAction(historique[i].getNomAction(),actions)))
				    actions.push_back(historique[i].getNomAction());
            }
            i++;
		}
		else break ;    		
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

vector<PrixJournalier>Bourse::getPrixJournaliersDispoAujourdhui(double solde)const {
		vector<PrixJournalier> resultat;
		if ((solde<=0)||((this->getPrixJournaliersAujourdhui()).size()==0))return resultat;
		int i=0;
		while ((i<(this->getPrixJournaliersAujourdhui()).size())&&((this->getPrixJournaliersAujourdhui())[i].getPrix()<solde)){
			//if(!(appartientPrixJournalier((this->getPrixJournaliersAujourdhui())[i],resultat)))	
				resultat.push_back((this->getPrixJournaliersAujourdhui())[i]);
			i++;
		}
		return resultat;
}

//cond pour lastprix (vPJ[i].getDate()< dateAujourdhui)

double Bourse::getPrixAujourdhui(string nomAction){
	int i=0;
	vector<string> actionsDisponibles = this->getActionDisponibleAujourdhui();
	if(appartientAction(nomAction,actionsDisponibles)){
		while(i<(actionsDisponibles).size()){
			if(nomAction==(this->getPrixJournaliersAujourdhui()[i]).getNomAction())
				return (this->getPrixJournaliersAujourdhui()[i]).getPrix();
			i++;
		}
    }
//return -1;
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

class BourseDictNom:public Bourse{
private:
	map<string, vector<PrixJournalier> >  historique;
	
public:
	BourseDictNom(vector<PrixJournalier>&vPJ);
    vector<PrixJournalier> getPrixJournaliersParDate(const Date&)const;
	vector<string> getActionDisponibleParDate(const Date&)const;
	vector<PrixJournalier> getHistoriqueAction(string)const;
};

//BourseDictNom

BourseDictNom::BourseDictNom(vector<PrixJournalier> &vPJ){	
	int i=0;
	while(i<vPJ.size()){
		historique[vPJ[i].getNomAction()].push_back(vPJ[i]);
		i++;	
	}
}
 
vector<PrixJournalier> BourseDictNom::getHistoriqueAction(string action)const
{
	vector<PrixJournalier> historiquedAction;
	/*while((historique[action])[i].getDate()<=dateAujourdhui){
		if(!(appartientPrixJournalier(historique[action][i],historiquedAction)))
			historiquedAction.push_back(historique[action][i]);
		i++;
	}*/
	for(map<string, vector<PrixJournalier> >::const_iterator it = historique.begin();it!=historique.end();++it){
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


class BourseDictDate:public Bourse{
    map< Date , vector<PrixJournalier> > historique ;
    public:
    BourseDictDate( vector<PrixJournalier> & ); 
    vector<PrixJournalier> getPrixJournaliersParDate(const Date &)const;   
    vector<string> getActionDisponibleParDate(const Date &)const ;
    vector<PrixJournalier> getHistoriqueAction(string)const;
};
 
BourseDictDate::BourseDictDate(vector<PrixJournalier> &vPJ){	
	int i=0;
	while(i<vPJ.size()){
		historique[vPJ[i].getDate()].push_back(vPJ[i]);
		i++;	
	}
} 
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



double Bourse::getLastPrixAction(string nomAct)const{
    vector<PrixJournalier> vectHistoria=this->getHistoriqueAction(nomAct);
    return vectHistoria[vectHistoria.size()-1].getPrix();
}
double Bourse::getAvantDernierPrixDAction(string nomAct) const {
    vector<PrixJournalier> vectHistoria=this->getHistoriqueAction(nomAct);
    return vectHistoria[vectHistoria.size()-2].getPrix();
}	


#endif // BOURSE_H_INCLUDED
