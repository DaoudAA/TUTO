#include <iostream>
#include <string>
#include <cstdlib>
#include"Date.h"
using namespace std;
//constructeurs

//void Test::verif(Date dateDonnee, Date dateJuste,string message )


<<<<<<< HEAD
//operateurs de surcharge
 bool operator==(Date const&d1, Date const&d2)
 {
     bool test=false;
     if (d1.getJour()==d2.getJour())
        if(d1.getMois()==d2.getMois())
            if(d1.getAnnee()==d2.getAnnee())
                test=true ;
     return test;
 }

 bool operator <(Date const& date1, Date const& date2)
{
    if(date1.getAnnee()<date2.getAnnee())
        return true;
    else if(date1.getAnnee()==date2.getAnnee()){
            if(date1.getMois()<date2.getMois())
                return true;
            else if(date1.getMois()==date2.getMois())
                    if(date1.getJour()<date2.getJour())
                        return true;

    }

    return false;
}
 bool operator >(Date & date1, Date & date2)
{
    if(date1.getAnnee()>date2.getAnnee())
        return true;
    else if(date1.getAnnee()==date2.getAnnee()){
            if(date1.getMois()>date2.getMois())
                return true;
            else if(date1.getMois()==date2.getMois())
                    if(date1.getJour()>date2.getJour())
                        return true;

    }

    return false;
}

=======

/*Class Test{
    public:
        Verif(DateG,DateAttente,Flag)
};
Test::Verif{}*/

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
    date1.incrementerDate();
    date2.incrementerDate();
    date3.incrementerDate();
    if ( ((date1.getJour()==01)&&(date1.getMois()==02))&&((date2.getJour()==01)&&(date2.getMois()==04))&&((date3.getJour()==01)&&(date3.getMois()==06)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test2
    cout<<"test 2";
    date4.incrementerDate();
    date5.incrementerDate();
    if ( ((date4.getJour()==01)&&(date4.getMois()==05))&&((date5.getJour()==01)&&(date5.getMois()==07)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test3
    cout<<"test 3";
    date6.incrementerDate();
    if ( ((date6.getJour()==01)&&(date6.getMois()==01)&&(date6.getAnnee()==2011)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test4
    cout<<"test 4";
    date7.incrementerDate();
    if ( ((date7.getJour()==01)&&(date7.getMois()==03)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
//test5
    cout<<"test 5";
    date8.incrementerDate();
    date9.incrementerDate();
    if ( ((date8.getJour()==29)&&(date8.getMois()==02))&&((date9.getJour()==01)&&(date9.getMois()==03)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
    //cout<<"Date 8 :"<<date8.getJour()<<"/"<<date8.getMois()<<"/"<<date8.getAnnee()<<endl;
    //cout<<"Date 9 :" <<date9.getJour()<<"/"<<date9.getMois()<<"/"<<date9.getAnnee()<<endl;
//test6
    cout<<"test 6";
    date10.incrementerDate();
    if ( ((date10.getJour()==13)&&(date10.getMois()==03)&&(date10.getAnnee()==2001)))
        cout<<"\tSuccee"<<endl;
    else
        cout<<"\tEchec"<<endl;
    return 0;
return 0;}
>>>>>>> 2831a0ca7d58c3c5eb2148cc552470ac322788cc
