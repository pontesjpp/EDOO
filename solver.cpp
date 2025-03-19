#include <iostream>
#include <fstream>

#include "cemetery.hpp" 

int main() {
    int M, L;
    cin >> M >> L;
    Cemetery cemetery(M, L);
    string command;
    while (cin >> command && command != "END") {
        if (command == "ADD") {
            key_t key;
            cin >> key;
            location_t location = cemetery.add(key);
            cout << location.floor << "." << location.grave << endl;
        } else if (command == "REM") {
            key_t key;
            cin >> key;
            location_t location = cemetery.del(key);
            if (location.floor==-1 && location.grave==-1){
                cout<< "?.?"<< endl;
            }
            else {
                cout << location.floor << "." << location.grave << endl;
            }
        } else if (command == "QRY") {
            key_t key;
            cin >> key;
            location_t location = cemetery.qry(key);
            if (location.floor==-1 && location.grave== -1){
                cout<< "?.?"<< endl;
            }
            else {
                cout << location.floor << "." << location.grave << endl;
            }
        } 
    }
    return 0;
}
