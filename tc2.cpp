#include <iostream>
#include <string>
#include "list.hpp"

using namespace std;

// Estrutura para representar um nó na lista encadeada de SQ
struct SQNode {
    SQ<int>* sq;
    SQNode* next;

    SQNode(SQ<int>* s, SQNode* nxt = nullptr) : sq(s), next(nxt) {}
    ~SQNode() { delete sq; }
};

int main() {
    int nCases;
    cin >> nCases;
    for (int caseNo = 0; caseNo < nCases; caseNo++) {
        // Inicializa a lista encadeada com uma fila vazia na posição 0
        SQNode* head = new SQNode(new SQ<int>(QUEUE));
        SQNode* tail = head;

        string op;
        while (cin >> op && op != "END") {
            if (op == "ADD") {
                int i, v;
                cin >> i >> v;
                SQNode* current = head;
                for (int idx = 0; idx < i && current != nullptr; idx++) {
                    current = current->next;
                }
                if (current != nullptr && current->sq != nullptr) {
                    current->sq->push(v); // Adiciona o valor na estrutura da posição i
                }
            } else if (op == "DEL") {
                int i;
                cin >> i;
                SQNode* current = head;
                for (int idx = 0; idx < i && current != nullptr; idx++) {
                    current = current->next;
                }
                if (current != nullptr && current->sq != nullptr && current->sq->size() > 0) {
                    current->sq->pop(); // Remove um elemento da estrutura da posição i
                }
            } else if (op == "SPL") {
                int i;
                cin >> i;
                SQNode* current = head;
                for (int idx = 0; idx < i && current != nullptr; idx++) {
                    current = current->next;
                }
                if (current != nullptr && current->sq != nullptr && current->sq->size() >= 2) {
                    // Divide a estrutura da posição i em duas
                    SQ<int>* newSQ = current->sq->split();
                    if (newSQ != nullptr) {
                        SQNode* newNode = new SQNode(newSQ, current->next);
                        current->next = newNode;
                        if (current == tail) {
                            tail = newNode;
                        }
                    }
                }
            } else if (op == "MER") {
                int i, j;
                cin >> i >> j;
                SQNode* nodeI = head;
                SQNode* nodeJ = head;
                for (int idx = 0; idx < i && nodeI != nullptr; idx++) {
                    nodeI = nodeI->next;
                }
                for (int idx = 0; idx < j && nodeJ != nullptr; idx++) {
                    nodeJ = nodeJ->next;
                }
                if (nodeI != nullptr && nodeJ != nullptr && nodeI->sq != nullptr && nodeJ->sq != nullptr && i != j) {
                    // Mescla as estruturas das posições i e j
                    nodeI->sq->merge(nodeJ->sq);
                    // Remove o nó j da lista encadeada
                    SQNode* prevJ = head;
                    while (prevJ != nullptr && prevJ->next != nodeJ) {
                        prevJ = prevJ->next;
                    }
                    if (prevJ != nullptr) {
                        prevJ->next = nodeJ->next;
                        if (nodeJ == tail) {
                            tail = prevJ;
                        }
                        delete nodeJ;
                    }
                }
            } else if (op == "TRA") {
                int i;
                cin >> i;
                SQNode* current = head;
                for (int idx = 0; idx < i && current != nullptr; idx++) {
                    current = current->next;
                }
                if (current != nullptr && current->sq != nullptr) {
                    // Transforma a estrutura da posição i entre pilha e fila
                    current->sq->transform();
                }
            }
        }

        // Imprime o resultado para o caso de teste atual
        cout << "caso " << caseNo << ":";
        SQNode* current = head;
        while (current != nullptr) {
            if (current->sq != nullptr && current->sq->size() > 0) {
                cout << " " << current->sq->peek(); // Imprime o elemento no topo/frente
            } else {
                cout << " ?"; // Imprime '?' se a estrutura estiver vazia
            }
            current = current->next;
        }
        cout << endl;

        // Limpa a memória alocada para as estruturas
        while (head != nullptr) {
            SQNode* toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }
    return 0;
}
