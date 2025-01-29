#include <cassert>
#include <iostream>

using namespace std;


class Node
{
	friend class LinkedList; // declara linkedlist como classe amiga, liberando o acesso a variaveis privadas
public:
	Node() //começa a lista com -1 como valor inicial e next como null
	{
		val = -1;
		next = nullptr;
	}
	Node(int v) // construtor que inicia a lista com um inteiro v e next como null
	{
		val = v;
		next = nullptr;
	}
	~Node() // destrutor chamado automaticamente assim q um obj eh deletado, imprimindo no terminal o int val que foi deletado
	{
		cout << "deleting " << val << endl;
	}
private:
	int val; // valor inteiro e ponteiro do prox no que so pode ser acessado na classe Node ou LinkedList(friendclass)
	Node *next; // caso next == nulo esse nó é o ultimo da lista encadeada.
}; 


class LinkedList
{
public:
	LinkedList()
	{
		head = new Node(); // inicia o no sentinela inicial
		sz = 0; // inicia a variavel sz como 0
	};
	~LinkedList();
	int size()
	{
		return sz;
	}
	int operator[](int pos);
	void insert(int pos, int val);
	void append(int val);
	void prepend(int val);
	int remove(int pos);
private:
	Node *locate(int pos);
	Node *head;
	int sz;
};

LinkedList::~LinkedList() // funcao criada para destruir a lista, percorrendo todos os nós e excluindo
{
	Node *cur = head; // inicializa um ponteiro para nó chamado cur e atribui head a ele
	while (cur != nullptr) {
		Node *next = cur->next; // inicializa umn ponteiro para nó next, onde será atribuido o valor do próximo nó
		delete cur; // deleta o nó que está no cursor
		cur = next; // atribui o nó de next ao cursor
	}
}


Node *LinkedList::locate(int pos) // a função locate que faz parte de linkedlist retorna um ponteiro para nó, e tem como argumento um inteiro pos
{
	Node *cur = head; // inicializa o cursor
	int i = 0;
	while ( i < pos && cur->next != nullptr) { // enquanto i for menor que pos e o próximo nó não for nulo
		cur = cur->next; //cursor vai virar o próximo nó
		i++; // adiciona 1 a variavel i
	}
	return cur; // retorna o nó que está na posicão pos
}

int LinkedList::operator[](int pos)
{
	assert(pos < sz);
	return locate(pos)->next->val;
}


void LinkedList::insert(int pos, int val)
{
	assert(pos <= sz);
	Node *cur = locate(pos);
	Node *new_node = new Node(val);
	new_node->next = cur->next;
	cur->next = new_node;
	sz++;
}

void LinkedList::append(int val)
{
	return insert(sz, val);
}

void LinkedList::prepend(int val)
{
	return insert(0, val);
}


int LinkedList::remove(int pos)
{
	assert (pos < sz);
	Node *cur = locate(pos);
	Node *to_die = cur->next;
	cur->next = to_die->next;
	int ret = to_die->val;
	delete to_die;
	sz--;
	return ret;
}


int main()
{
	LinkedList list;

	size_t n = 1 << 4;
	for (int i = 0; i < n; i++) {
		list.append(2 * i);
	}
	for (int i = 0; i < list.size(); i++) {
		cout << "list[" << i << "]= " << list[i] << endl;
	}
	cout << endl;
	size_t half = n / 2;
	for (int i = 0; i < half; i++) {
		list.remove(i);
	}
	for (int i = 0; i < list.size(); i++) {
		cout << "list[" << i << "]= " << list[i] << endl;
	}
	cout << endl;
	for (int i = 0; i < half; i++) {
		list.insert(2 * i, 4 * i);
	}
	for (int i = 0; i < list.size(); i++) {
		cout << "list[" << i << "]= " << list[i] << endl;
	}
	cout << endl;

	cout << "size = " << list.size();
}
