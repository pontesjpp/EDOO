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
        int totalItems();
        void printTable();
        void findDrink(string name);
        void removeName(string name);
        void rehashing();
        int ts = tableSize;
        float getloadFactor(int ts,int count);
        
    private:
        static const int tableSize = 10;
        struct item{
            string name;
            string drink;
            item* next;
        };  
        item* HashTable[tableSize];

}



;
