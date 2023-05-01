#include <iostream>
#include <string>
#include <cstdlib>
#include"Date.h"
using namespace std;
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



Date date2(31,03,2013);
Date date3(31,05,2015);
Date date5(30,06,2016);
Date date8(28,02,2016);
Date date10(12,03,2001);
    
    Date date1(31,01,2011);
    Date date4(30,04,2014);
    Date date6(31,12,2010);
    Date date7(28,02,2010);
    Date date9(29,02,2012);

    TestDate test1("fin du mois de 31 jours");
    cout<<test1.getTitre()<<":\t";
    test1.verif(date1,Date(1,2,2011));
    cout<<test1.getFlag();

    TestDate test2("fin du mois de 30 jours");
    cout<<endl<<test2.getTitre()<<":\t";
    test2.verif(date4,Date(1,5,2014));
    cout<<test2.getFlag();

    TestDate test3("fin d'annnee");
    cout<<endl<<test3.getTitre()<<":\t";
    test3.verif(date6,Date(1,1,2011));
    cout<<test3.getFlag();

    TestDate test4("mois 2-annee non bisextile");
    cout<<endl<<test4.getTitre()<<":\t";
    test4.verif(date7,Date(1,3,2010));
    cout<<test4.getFlag();

    TestDate test5("mois 2-annee bisextile");
    cout<<endl<<test5.getTitre()<<":\t";
    test5.verif(date9,Date(1,3,2012));
    cout<<test5.getFlag();


return 0;}
