
#include <cassert>
#include <iostream>

using namespace std;


// Usar como base os prototipos
// de LinkedList vistos em aula

class Node
{
	friend class LinkedList;
public:
	Node()
	{
		val = -1;
		next = nullptr;
	}
	Node(int v)
	{
		val = v;
		next = nullptr;
	}
	~Node()=default;
	
private:
	int val;
	Node *next;
};


class LinkedList
{
	friend class Stack;
	friend class Deque;
public:
	LinkedList()
	{
		head = new Node();
		sz = 0;
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

LinkedList::~LinkedList()
{
	Node *cur = head;
	while (cur != nullptr) {
		Node *next = cur->next;
		delete cur;
		cur = next;
	}
}


Node *LinkedList::locate(int pos)
{
	Node *cur = head;
	int i = 0;
	while ( i < pos && cur->next != nullptr) {
		cur = cur->next;
		i++;
	}
	return cur;
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


class Stack
{
public:
	Stack() = default;
	~Stack() = default;
	void push (int val);
	int pop();
	int peek();
	int qtd();
private:
	LinkedList list;
	
};

void Stack::push(int val){
	list.prepend(val);
}

int Stack::pop(){
	assert(list.size()>0);
	return list.remove(0);
}

int Stack::peek(){
	assert(list.size()>0);
	return list[0];
}

int Stack::qtd(){
	return list.size();
}

class Deque
{
public:
	Deque() = default;
	~Deque() = default;
	void pushfrente (int val);
	void pushtras(int val);
	int poptras();
	int popfrente();
	int frente();
	int tras();
	int qtd();

private:
	LinkedList list;
};

void Deque::pushfrente(int val){
	list.prepend(val);
}

void Deque::pushtras(int val){
	list.append(val);
}

int Deque::poptras(){
	assert(list.size()>0);
	int tam = list.size();
	return list.remove(tam-1);
}

int Deque::popfrente(){
	assert(list.size()>0);
	return list.remove(0);
}

int Deque::frente(){
	assert(list.size()>0);
	return list[0];
}

int Deque::tras(){
	assert(list.size()>0);
	int tam = list.size();
	return list[tam-1];
}	

int Deque::qtd(){
	return list.size();
}

int main()
{
	string op;
	int next_car = 0;
	Stack t0;
	Deque t1;
	while (true) {
		cin >> op ;
		if (cin.eof()) break;
		if (op=="E0"){
			t0.push(next_car);
			next_car+=1;
		}
		if (op=="S0"){
			int out = t0.pop();
			cout<<out<<endl;
		}
		if (op=="E1E"){
			t1.pushfrente(next_car);
			next_car+=1;
		}
		if (op=="E1D"){
			t1.pushtras(next_car);
			next_car+=1;
		}
		if (op=="S1E"){
			int out = t1.popfrente();
			cout<<out<<endl;
		}
		if (op=="S1D"){
			int out = t1.poptras();
			cout<<out<<endl;
		}		
		if (op=="FIM"){
			int tam0= t0.qtd();
			int tam1= t1.qtd();
			cout<<tam0<<endl;
			cout<<tam1<<endl;
			cout<<"\n"<<endl;

		}
	}

}
