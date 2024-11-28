#include <iostream>
#include "cl.h"
using namespace std;

int main() {
    unsigned p = 0 , t = 0, ch = 0 , k = 0;
    bool fl = false;
    CL cluster;
    do {
        cout << "please, enter number of processe in cluster: ";
        cin >> p;
        cout << "please, enter maximum tact limit: ";
        cin >> t;
        cout << "please, enter the chance of generating a new task in cluster: ";
        cin >> ch;
        cout << "please, enter how many tasks will appear every tact: ";
        cin >> k;
        fl = false;
        try {
            CL c(p, t, ch);
            cluster = c;
        }
        catch (char* e) {
            cout << e << endl << "Please, try again\n\n";
            fl = true;
        }
    } while (fl == true);

    printStatistic(cluster.Simulation(k));
   return 0;
}
