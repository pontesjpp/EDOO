#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"

using namespace std;

int main (int argc, char **argv) {
    MyHash hashy;
    string name;
    hashy.addItem("Paul", "Locha");
    hashy.addItem("Kim", "Iced Mocha");
    hashy.addItem("Emma", "Strawberry Smoothy");
    hashy.addItem("Annie", "Hot Chocolate");
    hashy.addItem("Sarah", "Passion Tea");
    hashy.addItem("Pepper", "Caramel Mocha");
    hashy.addItem("Mike", "Chai Tea");
    hashy.addItem("Steve", "Apple Cider");
    hashy.addItem("Bill", "Root Beer");
    hashy.addItem("Marie", "Skinny Latte");
    hashy.addItem("Susan", "Water");

    while (name!="exit")
    {
        cin>>name;
        hashy.findDrink(name);
    }
    

    return 0;
}
