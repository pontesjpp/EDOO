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






int MyHash::Hash(string key)
{
    int hash = 0;
    int index;

    for (int i = 0; i < key.length(); i++)
    {
        hash = (hash + (int)key[i]);
    }

    index = hash % tableSize;

    return index;
}