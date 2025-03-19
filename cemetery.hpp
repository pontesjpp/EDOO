#include <iostream> 
#include <fstream>
#include <vector>
#include <algorithm>

using key_t = int;  // DO NOT CHANGE THIS

struct grave_t {    // DO NOT CHANGE THIS 
    bool deleted;   // soft-deleted marker (tombstone)
    key_t key;     
};

struct location_t { // DO NOT CHANGE THIS 
    int floor;  // floor number 0,1,2..., M-1
    int grave;  // grave position within the floor 0,1,2,..., L-1
};

using namespace std;

class Cemetery {
private:
    int M; //floors
    int L; //graves per floor
    vector<vector<grave_t>> cemetery;
    int hash(key_t key);
    void fullCemetery();

public:
    Cemetery(int floors, int gravesPerFloor);
    ~Cemetery();
    bool has(key_t key);
    location_t add(key_t key);
    location_t del(key_t key);
    location_t qry(key_t key);
};


// ADD IMPLEMENTATION CODE

Cemetery::Cemetery(int floors, int gravesPerFloor) {
    M = floors;
    L = gravesPerFloor;
    cemetery.resize(M);
    for (int i = 0; i < M; i++) {
        cemetery[i].resize(L);
        for (int j = 0; j < L; j++) {
            cemetery[i][j].deleted = false;
            cemetery[i][j].key = 100000;
        }
    }
} 

Cemetery::~Cemetery() {
    //nothing to do here
}

int Cemetery::hash(key_t key) {
    return key % M;
}

location_t Cemetery::add(key_t key){
    int floor = hash(key);
    int count = 0;
    while (cemetery[floor][count].key != 100000 && count < L) {
        count++;
    }
    if (count == L) {
        fullCemetery();
        floor = hash(key);
    }
    count = 0;
    while (cemetery[floor][count].key != 100000 && count < L) {
        count++;
    }

    cemetery[floor][count].key = key;
    cemetery[floor][count].deleted = false;
    sort(cemetery[floor].begin(), cemetery[floor].end(), [](grave_t a, grave_t b) {
        return a.key < b.key;
    });

    location_t location;
    location.floor = floor;
    for (int i= 0; i<L; i++){
        if (cemetery[floor][i].key == key){
            location.grave = i;
            break;
        }
    }

    return location;

}

void Cemetery::fullCemetery() {
    M = (M * 2) + 1;
    L = L*2;
    vector<vector<grave_t>> newCemetery(M);
    for (int i = 0; i < M; i++) {
        newCemetery[i].resize(L);
        for (int j = 0; j < L; j++) {
            newCemetery[i][j].deleted = false;
            newCemetery[i][j].key = 100000;
        }
    }

    for (int l = 0; l < M / 2; l++) {
        for (int j = 0; j < L/ 2; j++) {
            if (cemetery[l][j].deleted || cemetery[l][j].key==100000) {
                continue;
            }
            else {
                int newHash = (cemetery[l][j].key) % M;
                int count = 0;
                while (newCemetery[newHash][count].key != 100000 && count < L) {
                    count++;
                }
                newCemetery[newHash][count] = cemetery[l][j];
                count = 0;
                
            }
        }
    }

    cemetery = newCemetery;
}

bool Cemetery::has(key_t key){
    int floor = hash(key);
    for (int i = 0; i < cemetery[floor].size(); i++) {
        if (cemetery[floor][i].key == key && !cemetery[floor][i].deleted) {
            return true;
        }
    }
    return false;
}

location_t Cemetery::del(key_t key) {
    bool cont = has(key);
    location_t location {100000,100000};
    if (cont == false) {
        return location;
    }
    else {
        int floor = hash (key);
        for (int i = 0; i<L;i++){
            if (cemetery[floor][i].key == key && !cemetery[floor][i].deleted){
                cemetery[floor][i].deleted = true;
                location.floor = floor;
                location.grave = i;
                return location;
            }
        }
        return location;
    }
    
}

location_t Cemetery::qry(key_t key){
    bool cont = has(key);
    location_t location {100000,100000};
    if (cont == false) {
        return location;
    }
    else {
        int floor = hash (key);
        for (int i = 0; i<L;i++){
            if (cemetery[floor][i].key == key && !cemetery[floor][i].deleted){
                location.floor = floor;
                location.grave = i;
                return location;
            }
        }
        return location;
    }
}