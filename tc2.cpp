#include <iostream>
#include <vector>
#include <string>
#include "list.hpp"

using namespace std;

int main() {
    int nCases;
    cin >> nCases;
    for (int caseNo = 0; caseNo < nCases; caseNo++) {
        // Inicializa uma lista de estruturas SQ (inicialmente apenas uma fila vazia na posição 0)
        vector<SQ<int>*> sqList;
        sqList.push_back(new SQ<int>(QUEUE)); // Fila vazia na posição 0

        string op;
        while (cin >> op && op != "END") {
            if (op == "ADD") {
                int i, v;
                cin >> i >> v;
                if (i < sqList.size()) {
                    sqList[i]->push(v); // Adiciona o valor na estrutura da posição i
                }
            } else if (op == "DEL") {
                int i;
                cin >> i;
                if (i < sqList.size() && sqList[i]->size() > 0) {
                    sqList[i]->pop(); // Remove um elemento da estrutura da posição i
                }
            } else if (op == "SPL") {
                int i;
                cin >> i;
                if (i < sqList.size() && sqList[i]->size() >= 2) {
                    // Divide a estrutura da posição i em duas
                    SQ<int>* newSQ = sqList[i]->split();
                    sqList.insert(sqList.begin() + i + 1, newSQ); // Insere a nova estrutura na posição i+1
                }
            } else if (op == "MER") {
                int i, j;
                cin >> i >> j;
                if (i < sqList.size() && j < sqList.size() && i != j) {
                    // Mescla as estruturas das posições i e j
                    sqList[i]->merge(sqList[j]);
                    sqList.erase(sqList.begin() + j); // Remove a estrutura da posição j
                }
            } else if (op == "TRA") {
                int i;
                cin >> i;
                if (i < sqList.size()) {
                    // Transforma a estrutura da posição i entre pilha e fila
                    sqList[i]->transform();
                }
            }
        }

        // Imprime o resultado para o caso de teste atual
        cout << "caso " << caseNo << ":";
        for (size_t k = 0; k < sqList.size(); k++) {
            if (sqList[k]->size() > 0) {
                cout << " " << sqList[k]->peek(); // Imprime o elemento no topo/frente
            } else {
                cout << " ?"; // Imprime '?' se a estrutura estiver vazia
            }
        }
        cout << endl;

        // Limpa a memória alocada para as estruturas
        for (auto sq : sqList) {
            delete sq;
        }
    }
    return 0;
}
