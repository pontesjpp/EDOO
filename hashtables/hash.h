#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;



class MyHash{
    public:
        MyHash();
        ~MyHash();
        int Hash(string key);
        void addItem (string name, string drink);
        int numberOfItemsInIndex(int index);
        void printTable();
        void findDrink(string name);
        void removeName(string name);
        
    private:
        static const int tableSize = 40;
        struct item{
            string name;
            string drink;
            item* next;
        };  
        item* HashTable[tableSize];

}



;
