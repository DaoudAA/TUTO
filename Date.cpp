#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int jour;
    int mois;
    int annee;

public:
    Date(int d, int m, int y);
    Date(string ch);
    int getJour()const{return jour;}
    int getMois()const{return mois;}
    int getAnnee()const{return annee;}
    void IncrementerDate();
    friend ostream& operator<<(ostream& flux , const Date& D){
        flux<< D.jour << "/" << D.mois << "/" << D.annee <<endl;
        return flux;
    }
};

Date::Date(int d, int m, int y){
    if (y>0) annee=y;
    jour=-1;
    mois=-1;
    if (d>0)
    {
        if (d<=31 && (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)){
            jour=d;
            mois=m;
        }
        if (d<=30 && ( m==4 || m==6 || m==9 || m==11)){
            jour=d;
            mois=m;
        }
        if (d<=29 && m==2){
            if ((y%4)==0 && d<=29)
            {
                jour=d;
                mois=m;
            }
            else if ((y%4)!=0 && d<=28) {
                jour=d;
                mois=m;
            }
        }
    }
}

Date::Date(string ch){
    string ch1,ch2,ch3;
    ch1=ch.substr(0, ch.find('/'));
    jour = atoi(ch1.c_str());
    ch2=ch.erase(0, ch.find('/') + 1);
    ch2=ch.substr(0, ch.find('/'));
    mois= atoi(ch2.c_str());
    ch3=ch.erase(0, ch.find('/') + 1);
    annee = atoi(ch3.c_str());

    if (jour <= 0 || mois <= 0 || mois > 12) {
        jour= -1;
        mois= -1;
    }
    else if (mois == 2) {
        if (annee% 4 == 0 )
        {
            if (jour > 29)
            {
                jour = -1;
                mois = -1;
            }
        }
        else
        {
            if (jour > 28) {
                jour = -1;
                mois = -1;
            }
        }
    }
    else if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) {
        jour = -1;
        mois = -1;
    }
    else if (jour > 31) {
        jour = -1;
        mois = -1;
    }
}

/*void Date::IncrementerDate(){
	if( mois==4 || mois==6 || mois==9 || mois==11 ){
		if (jour==30) {
			jour=1 ;
			mois++;
		}
		else jour++;
	}
	if (mois==12){
		if (jour==31){
			jour=1;
			mois=1;
			annee++;
		}
		else jour++;
	}
	if (mois==1||mois==3||mois==5||mois==7||mois==8||mois==10){
		if (jour==31){
			jour=1;
			mois++;
		}
		else jour++;
	}
	if (mois==2 ){
		if (jour==29 && annee%4==0){
			jour=1;
			mois++;
		}
		if (jour==28 && annee%4!=0){
			jour=1;
			mois++;
		}
		else jour++;
	}
}*/
void Date::IncrementerDate()
{
	//test1
    if(((mois==1)||(mois==3)||(mois==5)||(mois==7)||(mois==8)||(mois==10))&&(jour==31))
    {
        jour=1;
        mois++;
    }
    //test2
    else if(((mois==4)||(mois==6)||(mois==9)||(mois==11))&&(jour==30))
    {
        jour=1;
        mois++;
    }
    //test3
    else if ((mois==12)&&(jour==31))
    {
        jour=1;
        mois=1;
       annee++;
    }

    else if (mois==2)
    {   //test4
		if((annee%4==0)&&(jour==29))
        {
            jour=1;
            mois++;
        }
        //test5
        else if((annee%4!=0)&&(jour==28))
        {
            jour=1;
            mois++;
        }
		else
			jour++;
    }
    //test6
    else
        jour++;


}

int main(){
Date d1("31/4/2015");
Date d2("29/2/2012");
Date d3("29/2/2013");
Date d4(40,1,2016);
Date d5(11,10,2012);
cout<<"Affichage :"<<endl;
cout<<"31/4/2015\t---->\t"<< d1 << endl ;
cout<<"29/2/2012\t---->\t"<< d2 << endl ;
cout<<"29/2/2013\t---->\t" << d3 << endl ;
cout<<"40/1/2016\t---->\t" << d4 << endl ;
cout<<"11/10/2012\t---->\t" << d5 << endl ;
cout<<"Test Date"<<endl;


//test1
    Date date1(31,01,2011);
    Date date2(31,03,2013);
    Date date3(31,05,2015);

//test2
    Date date4(30,04,2014);
    Date date5(30,06,2016);

//test3
    Date date6(31,12,2010);

//test4
    Date date7(28,02,2010);
//test5
    Date date8(28,02,2016);
    Date date9(29,02,2012);
//test6
	Date date10(12,03,2001);

//test0
    cout<<"test 0";
    if((d1.getJour()==-1)&&(d1.getMois()==-1)&&(d3.getJour()==-1)&&(d4.getJour()==-1))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test2
//test1
    cout<<"test 1";
    date1.IncrementerDate();
    date2.IncrementerDate();
    date3.IncrementerDate();
    if ( ((date1.getJour()==01)&&(date1.getMois()==02))&&((date2.getJour()==01)&&(date2.getMois()==04))&&((date3.getJour()==01)&&(date3.getMois()==06)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test2
    cout<<"test 2";
    date4.IncrementerDate();
    date5.IncrementerDate();
    if ( ((date4.getJour()==01)&&(date4.getMois()==05))&&((date5.getJour()==01)&&(date5.getMois()==07)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test3
    cout<<"test 3";
    date6.IncrementerDate();
    if ( ((date6.getJour()==01)&&(date6.getMois()==01)&&(date6.getAnnee()==2011)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test4
    cout<<"test 4";
    date7.IncrementerDate();
    if ( ((date7.getJour()==01)&&(date7.getMois()==03)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test5
    cout<<"test 5";
    date8.IncrementerDate();
    date9.IncrementerDate();
    if ( ((date8.getJour()==29)&&(date8.getMois()==02))&&((date9.getJour()==01)&&(date9.getMois()==03)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
    //cout<<"Date 8 :"<<date8.getJour()<<"/"<<date8.getMois()<<"/"<<date8.getAnnee()<<endl;
    //cout<<"Date 9 :" <<date9.getJour()<<"/"<<date9.getMois()<<"/"<<date9.getAnnee()<<endl;
//test6
    cout<<"test 6";
    date10.IncrementerDate();
    if ( ((date10.getJour()==13)&&(date10.getMois()==03)&&(date10.getAnnee()==2001)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
    return 0;
return 0;}
