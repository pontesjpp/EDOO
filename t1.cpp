#pragma once

#include <cassert>
#include <iostream>
#include <stdexcept>

// -----------------------------------------------------------------
// DECLARACOES DOS TAD
// -----------------------------------------------------------------

//
// Classe abstrata/Interface para listas
//
template <typename T>
class List {
public:
    virtual ~List() {}
    int size() const { return sz; } // retorna o tamanho da lista
    virtual T &operator[](int pos) = 0;  // retorna o elemento da posicao pos
    virtual void insert(int pos, T val) = 0; // insere val na posicao pos
    void append(T val) { insert(sz, val); } // adiciona ao final
    void prepend(T val) { insert(0, val); } // adiciona no inicio
    virtual T remove(int pos) = 0; // remove e retorna o elemento da posicao pos
protected:
    int sz{0}; // tamanho da lista
};

//
// Lista encadeada
//
template <typename T>
class LinkedList : public List<T> {
    // Tipo no da lista encadeada
    struct Node {
        explicit Node(T v, Node *nxt = nullptr) : val{v}, next{nxt} {}
        explicit Node(Node *nxt = nullptr) : next{nxt} {}
        ~Node() {}

        T val;
        Node *next;
    };

public:
    LinkedList() : head{nullptr} {}
    ~LinkedList() {
        while (head != nullptr) {
            Node *to_die = head;
            head = head->next;
            delete to_die;
        }
		this->sz=0;
    }

    // Métodos da interface List
    T &operator[](int pos) override {
        assert(pos >= 0 && pos < this->sz);
        Node *cursor = locate(pos);
        return cursor->val;
    }

    void insert(int pos, T val) override {
        assert(pos >= 0 && pos <= this->sz); // Verifica se a posição é válida

        if (pos == 0) {
            head = new Node(val, head); // Cria um novo nó com o valor val e aponta para o nó head
        } else {
            Node *prev = locate(pos - 1); // Localiza o nó anterior à posição pos
            assert(prev != nullptr); // Segurança extra para evitar acesso nulo
            prev->next = new Node(val, prev->next); // Cria um novo nó com o valor val e aponta para o nó seguinte ao nó prev
        }

        this->sz++; // Incrementa o tamanho da lista
    }

    T remove(int pos) override {
        assert(pos >= 0 && pos < this->sz);
        Node *to_die;
        if (pos == 0) {
            to_die = head;
            head = head->next;
        } else {
            Node *prev = locate(pos - 1);
            to_die = prev->next;
            prev->next = to_die->next;
        }
        T ret = to_die->val;
        delete to_die;
        this->sz--;
        return ret;
    }

    // Métodos adicionais

    // Concatena a lista other ao final desta lista
    // Os elementos devem ser removidos de other
    // mas a lista other nao deve ser destruida
    void merge(LinkedList<T> *other) {
        if (other == nullptr || other->head == nullptr) {
            return; // Se 'other' estiver vazia ou for nula, não há nada para mesclar
        }

        if (head == nullptr) {
            head = other->head;
        } else {
            Node *cur = head;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = other->head;
        }

        this->sz += other->sz;
        other->head = nullptr;
        other->sz = 0;
    }

    // Divide a lista em duas metades.
    // Esta lista fica com os primeiros floor(n/2) elementos.
    // Os restantes elementos sao colocados numa nova lista
    // retornada pelo metodo.
    LinkedList<T> *split() {
        if (this->sz < 2) {
            return new LinkedList<T>(); // Retorna uma lista vazia se não puder dividir
        }

        int mid = this->sz / 2;
        Node *cur = locate(mid - 1); // Pega o nó antes do ponto de divisão

        LinkedList<T> *new_list = new LinkedList<T>();
        new_list->head = cur->next;
        new_list->sz = this->sz - mid;

        cur->next = nullptr; // Desconectar a segunda metade da original
        this->sz = mid;

        return new_list;
    }

private:
    Node *locate(int pos) {
        if (pos < 0 || pos >= this->sz) {
            return nullptr;
        }
        Node *cur = head;
        for (int i = 0; i < pos; ++i) {
            cur = cur->next;
        }
        return cur;
    } // localiza o no da posicao pos

    Node *head;
};

//
// Tipos de SQ
//
enum TYPE {
    STACK = 0, // Pilha
    QUEUE = 1  // Fila
};

//
// Classe para representar objetos que podem ser pilha ou fila
//
template <typename T>
class SQ {
public:
    SQ(TYPE t) : type{t}, list{new LinkedList<T>()} {}
    ~SQ() { delete list; }

    TYPE Type() const { return type; } // retorna o tipo da SQ (vide enum TYPE)
    int size() { return list->size(); } // retorna o numero de elementos na SQ

    const T &peek() {
        if (list->size() == 0) {
            throw std::out_of_range("SQ is empty.");
        }
        return (*list)[0];
    } // retorna uma referencia para o elemento no topo/frente da pilha/fila

    void push(T val) {
        if (type == STACK) {
            list->prepend(val);
        } else if (type == QUEUE) {
            list->append(val);
        }
    } // empilha/enfileira

    T pop() {
        if (type == STACK) {
            return list->remove(0);
        } else if (type == QUEUE) {
            return list->remove(0);
        } else {
			throw std::out_of_range("Cannot pop from an empty SQ.");
		}
		
    } // desempilha/desenfileira

    void transform() {
        if (type == STACK) {
            type = QUEUE;
        } else if (type == QUEUE) {
            type = STACK;
        }
    } // transforma de pilha para fila ou vice versa

    // Divide como no enunciado:
    // os primeiros floor(n/2) elementos permanecem nesta SQ
    // e os demais sao retornados numa nova SQ
    SQ<T> *split() {
        LinkedList<T> *new_list = list->split();
        SQ<T> *new_sq = new SQ<T>(type);
        new_sq->list = new_list;
        return new_sq;
    }

    void merge(SQ<T> *other) {
        if (other == nullptr || other->list == nullptr) {
            return;
        }
        list->merge(other->list);
    }

private:
    TYPE type;
    LinkedList<T> *list;
};
