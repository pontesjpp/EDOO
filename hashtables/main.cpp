#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"

using namespace std;

int main (int argc, char **argv) {
    MyHash hashy;
    string name;
    string drink;
    while (name != "exit")
    {
        cout << "Enter name: ";
        cin >> name;
        if (name != "exit")
        {
            cout << "Enter drink: ";
            cin >> drink;
            hashy.addItem(name, drink);
        }
    }
    int ts = hashy.ts;
    int count = hashy.totalItems();
    float lf = (float) count/ts;
    cout << "The actual table size is "<< ts << endl;
    cout << "The count of items is "<< count << endl;
    cout << "The actual load factor is "<< lf << endl;
    
    return 0;
}
