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
            cemetery[i][j].deleted = true;
            cemetery[i][j].key = -1;
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
  if (!cemetery[hash(key)][L-1].deleted || cemetery[hash(key)][L-1].key != -1) {
    fullCemetery();
  }
  
  int floor = hash(key);
  location_t loc = {floor, -1};
  grave_t grave = {false, key};
  
  for (int j = 0; j < L; j++) {
    if(grave.key == key) {
      loc.grave = j;
    }
    
    if (cemetery[floor][j].key == -1) {
      cemetery[floor][j] = grave;
      break;
    }
    else if(cemetery[floor][j].key > grave.key) {
      grave_t temp = cemetery[floor][j];
      cemetery[floor][j] = grave;
      grave = temp;
    }
  }
  
  return loc;

}

void Cemetery::fullCemetery() {  //aumenta o tamanho do cemitério
    int newM = 2 * M + 1;
    int newL = 2 * L;
    vector<key_t> keys;
    
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < L; j++) {
        if (!cemetery[i][j].deleted && cemetery[i][j].key != -1) {
          keys.push_back(cemetery[i][j].key);
        }
      }
    }
    
    M = newM;
    L = newL;
    cemetery.assign(M, vector<grave_t>(L, {true, -1}));
    
    for (key_t key : keys) {
      add(key);
    }
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
    location_t location {-1,-1};
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
    location_t location {-1,-1};
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
