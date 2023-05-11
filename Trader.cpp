#include "Trader.h"
#include "Bourse.h"
#include <iostream>
using namespace std ;
int main() {
    string ch1;
ch1="../prices_simple.csv";
vector<PrixJournalier> vPj;
PersistancePrixJournaliers ppj;
vPj=ppj.lirePrixJournaliersDUnFichier(ch1);

Date date(4,1,2010);
Bourse * b1 = new BourseVector(vPj);
b1->setDateaujourdhui(date);
    Portefeuille portefeuille(1000); // Start with 1000 EUR
    cout<<portefeuille.getSolde() << endl;
 
    // Use TraderAlea
    std::cout << "Using TraderManuel:" << std::endl;
    TraderManuel TraderManuel;
    TraderManuel.choisirTransaction(*b1, portefeuille);
   /* std::cout << "Transaction type: " << transactionAlea.getTypeTx() << std::endl;
    std::cout << "Transaction name: " << transactionAlea.getnomdAction() << std::endl;
    std::cout << "Transaction quantity: " << transactionAlea.getqtedAction() << std::endl;*/
/*
    // Use TraderAlgo1
    std::cout << "Using TraderAlgo1:" << std::endl;
    TraderAlgo1 traderAlgo1;
    Transaction transactionAlgo1 = traderAlgo1.choisirTransaction(*b1, portefeuille);
    std::cout << "Transaction type: " << transactionAlgo1.getTypeTx() << std::endl;
    std::cout << "Transaction name: " << transactionAlgo1.getnomdAction() << std::endl;
    std::cout << "Transaction quantity: " << transactionAlgo1.getqtedAction() << std::endl;

    // Use Traderbollin
/*  std::cout << "Using TraderBollin:" << std::endl;
    TraderBollin1 traderBollin;
    Transaction transactionAlgo2 = traderBollin.choisirTransaction(*b1, portefeuille);
    std::cout << "Transaction type: " << transactionAlgo2.getTypeTx() << std::endl;
    std::cout << "Transaction name: " << transactionAlgo2.getnomdAction() << std::endl;
    std::cout << "Transaction quantity: " << transactionAlgo2.getqtedAction() << std::endl;
   */ return 0;
}