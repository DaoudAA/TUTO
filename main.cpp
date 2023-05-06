#include "Simulation.h"
#include "Date.h"
#include <iostream>
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
                Date dateDebut(1,1,2010), dateFin(1,2,2010);
                
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
                        break;
                    case 2:
                        trader = new TraderBollin1;
                        break;
                    case 3:
                        trader = new TraderAlgo1;
                        break;
                    case 4:
                        trader = new TraderReverseMean;
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
                            // Prompt user for simulation start and end dates
            cout << "\nEntrer date debut de simulation (DD/MM/YYYY): ";
            string dateDStr;
            cin >> dateDStr;
            dateDebut = Date(dateDStr);
            cout << dateDebut << endl; 
            if (dateDebut.getJour()==-1 || dateDebut.getMois()==-1) {
                cout << "Date Invalide . Ressayer" << endl;
                continue;
            }
            cout << "Entrer date fin de simulation  (DD/MM/YYYY): ";
            string dateFStr;
            cin >> dateFStr;
            dateFin = Date(dateFStr);
            cout<<dateFin<<endl ; 
            if (dateFin.getJour()==-1 || dateFin.getMois()==-1) {
                 cout << "Date Invalide . Ressayer" << endl;
                continue;
            }
            double soldeInit=0;
            cout << "Enter Initial Balance: ";
            cin >> soldeInit;
            while(soldeInit <= 0){
                cout << "Initial Balance must be greater than 0. Please try again: ";
                cin >> soldeInit;
            }
           Simulation Sim(soldeInit);
           statiktiks = Sim.executer(*bourse, *trader, dateDebut, dateFin, soldeInit);

            // Print out statistics
            cout << "\nStats:" << endl;
            for (auto it = statiktiks.begin(); it != statiktiks.end(); ++it) {
                cout << it->first << ": " << it->second << endl;
            }

            break;
        }
        case 2: {
            // Read logs of previous simulations from file*/
            /*string fileName;
            cout << "Enter file name: ";
            cin >> fileName;
            PersistanceSimulation ps;
            vector<SimulationLog> logs = ps.lireFichier(fileName);
            for (auto log : logs) {
                cout << log << endl;
            }*/
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