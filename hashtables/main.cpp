#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"

using namespace std;

int main (int argc, char **argv) {
    MyHash hashObj;
    cout << "Paul => " << hashObj.Hash("Paul") << endl;
    return 0;
}