#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"

using namespace std;

MyHash::MyHash()
{
    for (int i=0; i<tableSize; i++)
    {
        HashTable[i] = new item;
        HashTable[i]->name = "empty";
        HashTable[i]->drink = "empty";
        HashTable[i]->next = NULL;
    }
}

MyHash::~MyHash()

{
    for (int i=0; i<tableSize; i++)
    {
        item* Ptr = HashTable[i];
        while (Ptr->next != NULL)
        {
            item* delPtr = Ptr;
            Ptr = Ptr->next;
            delete delPtr;
        }
    }
}

void MyHash::addItem(string name, string drink){
    int index = Hash(name);

    if (HashTable[index]->name == "empty")
    {
        HashTable[index]->name = name;
        HashTable[index]->drink = drink;
    }
    else
    {
        item* Ptr = HashTable[index];
        item* n = new item;
        n->name = name;
        n->drink = drink;
        n->next = NULL;

        while (Ptr->next != NULL)
        {
            Ptr = Ptr->next;
        }
        Ptr->next = n;
    }
}

int MyHash::numberOfItemsInIndex(int index)
{
    int count = 0;

    if (HashTable[index]->name == "empty")
    {
        return count;
    }
    else
    {
        count++;
        item* Ptr = HashTable[index];
        while (Ptr->next != NULL)
        {
            count++;
            Ptr = Ptr->next;
        }
    }
    return count;
}

void MyHash::printTable() {
    int number;
    for (int i = 0; i < tableSize; i++)
    {
        number = numberOfItemsInIndex(i);
        if (HashTable[i]->name=="empty"){
            cout << "-----------------\n";
            cout << "index[" << i << "] is empty" << endl;
            continue;
        }
        else {
            int count =0;
            item* cur = HashTable[i];
            cout << "-----------------\n"<<endl;
            cout << "index = " << i << "/" << count <<endl;
            cout << HashTable[i]->name << endl;
            cout << HashTable[i]->drink << endl;
            while (cur->next != NULL) {
                count++;
                cout << "index = " << i << "/" << count <<endl;
                cout << cur->name << endl;
                cout << cur->drink << endl;
                cur = cur->next;
            }
        cout << "# of items = " << number << endl;
        }
    }

}





int MyHash::Hash(string key)
{
    int hash = 0;
    int index;

    for (int i = 0; i < key.length(); i++)
    {
        hash = (hash + (int)key[i]);
    }

    index = (hash*17) % tableSize;

    return index;
}

void MyHash::findDrink(string name){
    int index = Hash(name);
    bool foundName = false;
    string drink;

    item* Ptr = HashTable[index];
    while (Ptr != NULL)
    {
        if (Ptr->name == name)
        {
            foundName = true;
            drink = Ptr->drink;
            break;
        }
        Ptr = Ptr->next;
    }
    if (foundName == true)
    {
        cout << "Favorite drink = " << drink << endl;
    }
    else
    {
        cout << name << "'s info was not found in the Hash Table\n";
    }
}

void MyHash::removeName(string name)
{
    int index = Hash(name);

    item* delPtr;
    item* P1;
    item* P2;

    // Case 0 - bucket is empty
    if (HashTable[index]->name == "empty" && HashTable[index]->drink == "empty")
    {
        cout << name << " was not found in the Hash Table\n";
    }

    // Case 1 - only 1 item contained in bucket and that item has matching name
    else if (HashTable[index]->name == name && HashTable[index]->next == NULL)
    {
        HashTable[index]->name = "empty";
        HashTable[index]->drink = "empty";

        cout << name << " was removed from the Hash Table\n";
    }

    // Case 2 - match is located in the first item in the bucket but there are more items in the bucket
    else if (HashTable[index]->name == name)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;

        cout << name << " was removed from the Hash Table\n";
    }

    // Case 3 - bucket contains items but first item is not a match
    else
    {
        P1 = HashTable[index]->next;
        P2 = HashTable[index];

        while (P1 != NULL && P1->name != name)
        {
            P2 = P1;
            P1 = P1->next;
        }
        // Case 3.1 - no match
        if (P1 == NULL)
        {
            cout << name << " was not found in the Hash Table\n";
        }
        // Case 3.2 - match is found
        else
        {
            delPtr = P1;
            P1 = P1->next;
            P2->next = P1;

            delete delPtr;
            cout << name << " was removed from the Hash Table\n";
        }
    }
}
