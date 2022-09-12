#include <fstream>
#include <vector>
#include <iostream>
#include <locale>
using namespace std;

template<class T>
class Node {
public:
  T data;
  Node *next;
	Node *prev;
    
  Node(T x) {
    data = x;
    next = NULL;
		prev = NULL;
  }
};

template<class T>
class MyList {
private:
  Node<T> *head;
  Node<T> *tail;
    
public:
  MyList() {
    head = NULL;
    tail = NULL;
  }
	//inserts x at the head of the list
  void insertHead(T x) {
    Node<T> *newNode = new Node<T>(x);
		if (tail == NULL) {
      tail = newNode;
    }
    newNode->next = head;
    head = newNode;
  }
	//get the value of the element at the position i of the list
  void get(int i) {
    Node<T> *current = head;
    for (int j = 0; j <= i; j++) {
      cout << current->data << " ";
			current = current->next;
    }
  }
};

template<class T>
class Inversion {
private:
  Node<T> *head;
  Node<T> *P;
	Node<T> *Q;
	int P_pos;
    
public:
  Inversion() {
    head = NULL;
    P = NULL;
		Q = NULL;
		P_pos = 0;
  }
	//inserts x at the head of the list
  void insertHead(T x) {
    Node<T> *newNode = new Node<T>(x);
    newNode->next = head;
    head = newNode;
  }
	//get the value of the element at the position i of the list
  void get(int i) {
		if (P == NULL) {
			P = head;
			Q = head->next;
			head->next = NULL;
		}
		Node<T> *temp = new Node<T>(0);
    if (i == P_pos) {
			cout << P->data << " ";
		} else if (i > P_pos) {
				while (P_pos < i) {
					cout << P->data << " ";
					temp = Q;
					Q = Q->next;
					temp->next = P;
					P = temp;
					P_pos ++;
				}
				cout << P->data << " ";
    } else {
				while (P_pos > i) {
					cout << P->data << " ";
					temp = P;
					P = P->next;
					temp->next = Q;
					Q = temp;
					P_pos --;
				}
				cout << P->data << " ";
		}
  }
};

template<class T>
class Doubly {
private:
  Node<T> *head;
  Node<T> *tail;
	double length = 0;
    
public:
  Doubly() {
    head = NULL;
    tail = NULL;
  }
	//inserts x at the head of the list
  void insertHead(T x) {
    Node<T> *newNode = new Node<T>(x);
		if (tail == NULL) {
      tail = newNode;
    }
    newNode->next = head;
		if (head != NULL) {
			head->prev = newNode;
		}
    head = newNode;
		length ++;
  }
	//get the value of the element at the position i of the list
  void get(int i) {
		if (i <= length/2) {
			Node<T> *current = head;
    	for (int j = 0; j <= i; j++) {
      	cout << current->data << " ";
				current = current->next;
    	}
		} else if (i > length/2) {
			Node<T> *current = tail;
    	for (int j = length - i; j > 0; j--) {
      	cout << current->data << " ";
				current = current->prev;
    	}
		}
  }
};

template<class T>
class Circular {
private:
  Node<T> *tail;
	int length = 0;
    
public:
  Circular() {
    tail = NULL;
  }
	//inserts x at the tail of the list
  void insertTail(T x) {
    Node<T> *newNode = new Node<T>(x);
		if (tail == NULL) {
      tail = newNode;
			tail->next = tail;
    } else {
			newNode->next = tail->next;
			tail->next = newNode;
			tail = tail->next;
		}
		length ++;
  }
	//get the value of the element at the position i of the list
  void get(int i) {
    Node<T> *current = tail;
		if (i == length - 1) {
			cout << current->data;
		} else {
			for (int j = 0; j <= i + 1; j++) {
				cout << current->data << " ";
				current = current->next;
			}
		}
  }
};

int main() {	
	MyList<int> singly = MyList<int>();
	singly.insertHead(567);
	singly.insertHead(456);
	singly.insertHead(345);
	singly.insertHead(234);
	singly.insertHead(123);
	cout << "Singly Linked List:" << endl;
	cout << "List: { 123 234 345 456 567 }" << endl;
	cout <<"Order: { 4 1 0 3 2 }" << endl;
	cout <<"Output: " << endl;
	singly.get(4);
	cout << endl;
	singly.get(1);
	cout << endl;
	singly.get(0);
	cout << endl;
	singly.get(3);
	cout << endl;
	singly.get(2);
	cout << endl << endl;

	Inversion<int> inversion = Inversion<int>();
	inversion.insertHead(567);
	inversion.insertHead(456);
	inversion.insertHead(345);
	inversion.insertHead(234);
	inversion.insertHead(123);
	cout << "Inversion:" << endl;
	cout << "List: { 123 234 345 456 567 }" << endl;
	cout <<"Order: { 4 1 0 3 2 }" << endl;
	cout <<"Output: " << endl;
	inversion.get(4);
	cout << endl;
	inversion.get(1);
	cout << endl;
	inversion.get(0);
	cout << endl;
	inversion.get(3);
	cout << endl;
	inversion.get(2);
	cout << endl << endl;

	Doubly<int> doubly = Doubly<int>();
	doubly.insertHead(567);
	doubly.insertHead(456);
	doubly.insertHead(345);
	doubly.insertHead(234);
	doubly.insertHead(123);
	cout << "Doubly Linked List:" << endl;
	cout << "List: { 123 234 345 456 567 }" << endl;
	cout <<"Order: { 4 1 0 3 2 }" << endl;
	cout <<"Output: " << endl;
	doubly.get(4);
	cout << endl;
	doubly.get(1);
	cout << endl;
	doubly.get(0);
	cout << endl;
	doubly.get(3);
	cout << endl;
	doubly.get(2);
	cout << endl << endl;

	Circular<int> circular = Circular<int>();
	circular.insertTail(123);
	circular.insertTail(234);
	circular.insertTail(345);
	circular.insertTail(456);
	circular.insertTail(567);
	cout << "Circular List:" << endl;
	cout << "List: { 123 234 345 456 567 }" << endl;
	cout <<"Order: { 4 1 0 3 2 }" << endl;
	cout <<"Output: " << endl;
	circular.get(4);
	cout << endl;
	circular.get(1);
	cout << endl;
	circular.get(0);
	cout << endl;
	circular.get(3);
	cout << endl;
	circular.get(2);
	cout << endl << endl;
}