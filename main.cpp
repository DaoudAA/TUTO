#include "Simulation.h"
#include "Date.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
int main(){
    string ch1;
    ch1="../prices_simple.csv";
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    map <string , long > statiktiks;
    /*Bourse * bourse=new BourseVector2(vPj);
    Trader * trader=new TraderAlea;
    
    double soldeInit=800;Simulation Sim(soldeInit);
    Date dateDebut(1,4,2013);
    Date dateFin(30,6,2013);
    
   statiktiks=Sim.executer(*bourse,*trader,dateDebut,dateFin,soldeInit);
    cout<< "Stats : "<<endl;
    for(auto elt : statiktiks){
        cout << elt.first << " : \t" <<  elt .second << endl ; 
    }*/
 int choix;
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Start a simulation" << endl;
        cout << "2. Read logs of previous simulations from file" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choix;

        switch (choix) {
            case 1: {
                int choixTrader=0, choixBourse=0;
                Date dateDebut(1,1,2010), dateFin(31,12,2016);
                string strader="";
                cout << "\n--- TRADERS ---" << endl;
                cout << "1. TraderAlea" << endl;
                cout << "2. TraderBollin1" << endl;
                cout << "3. TraderAlgo1" << endl;
                cout << "4. TraderReverseMean" << endl;
                cout << "Enter your choice (1-4): ";
                cin >> choixTrader;
                Trader * trader=NULL;
                switch (choixTrader) {
                    case 1:
                        trader = new TraderAlea;
                        strader="TraderAleatoire";
                        break;
                    case 2:
                        trader = new TraderBollin1;
                        strader="TraderBollinger";
                        break;
                    case 3:
                        trader = new TraderAlgo1;
                        strader="TraderAlgorithmique";
                        break;
                    case 4:
                        trader = new TraderReverseMean;
                        strader="TraderReverseMean";
                        break;
                    default:
                        cout << "Choix Invalid . Ressayer" << endl;
                        continue;
                }

                cout << "\n--- BOURSES ---" << endl;
                cout << "1. BourseDictNom" << endl;
                cout << "2. BourseDictDate" << endl;
                cout << "3. BourseVector" << endl;
                cout << "4. BourseVector2" << endl;
                //cout << "Entrer votre choix (1-4): ";
                cin >> choixBourse;
                Bourse * bourse=NULL;
                switch (choixBourse) {
                    case 1:
                        bourse = new BourseDictNom(vPj);
                        break;
                    case 2:
                        bourse = new BourseDictDate(vPj);
                        break;
                    case 3:
                        bourse = new BourseVector(vPj);
                        break;
                    case 4:
                        bourse = new BourseVector2(vPj);
                        break;
                default:
                        cout << "Choix Invalid . Ressayer" << endl;
                        continue;
                }
          /*      
            cout << "\nEntrer date debut de simulation (DD/MM/YYYY): ";
            string dateDStr;
            do {
                cin >> dateDStr;
                dateDebut = Date(dateDStr);
                if (dateDebut.getJour()==-1 || dateDebut.getMois()==-1) {
                    cout << "Date Invalide. Ressayer: ";
                }
            } while (dateDebut.getJour()==-1 || dateDebut.getMois()==-1);

            cout << "Entrer date fin de simulation (DD/MM/YYYY): ";
            string dateFStr;
            do {
                cin >> dateFStr;
                dateFin = Date(dateFStr);
                if (dateFin.getJour()==-1 || dateFin.getMois()==-1) {
                    cout << "Date Invalide. Ressayer: ";
                }
            } while (dateFin.getJour()==-1 || dateFin.getMois()==-1);
*/
            dateDebut = Date(1,1,2010);    
            dateFin = Date(1,4,2010);    
            double soldeInit=0;
            cout << "Enter Initial Balance: ";
            cin >> soldeInit;
            while(soldeInit <= 0){
                cout << "Initial Balance must be greater than 0. Please try again: ";
                cin >> soldeInit;
            }
           Simulation Sim(soldeInit);
           statiktiks = Sim.executer(*bourse, *trader, dateDebut, dateFin, soldeInit);
            cout << "\nStats:" << endl;
            for (auto it = statiktiks.begin(); it != statiktiks.end(); ++it) {
                cout << it->first << ": " << it->second << endl;
            }
            //ecriture dans logs 
            string fileName="../logs.txt";
            ofstream flot(fileName, ios::app); 
            if (!flot) {
                flot.open("logs.txt");
            }
            if (flot.tellp() == 0) {
                flot << "Date:\tTrader:\tMontant_de_depart:\tDate_depart:\tNombre_de_jours:\t%Gains" << endl; // Write the header line
            
            }
            auto now = chrono::system_clock::now();
            time_t time_now = chrono::system_clock::to_time_t(now);
            string strdate=ctime(&time_now);
            string strannee=ctime(&time_now);
            flot<<strdate.substr(0,10)<<strannee.substr(19,5)<<":\t"<<strader<<":\t"<<soldeInit<<":\t"<<dateDebut<<":\t"<<statiktiks["Nbr de Jours"]<<":\t"<<statiktiks["Taux_du_gain_en_%"]<< endl;
            flot.close(); 
            break;
        }
        case 2: {
            string ligne;
            string fileName="../logs.txt";
            ifstream flot(fileName);
            while(getline(flot,ligne)){
                cout << ligne << endl;
            }
            break;
        }
        case 3: {
            // Exit
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
} while (choix != 3);

    return 0 ;
}