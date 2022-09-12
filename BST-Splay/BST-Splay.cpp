#include "Splay.h"

int main() {
	int c;
	std::cout << "Enter 1 for splay or 2 for semi-splay: ";
	std::cin >> c;
	int data;
	BST *userTree = new BST();
	do {
		std::cout << "Enter the next node value(int) or -1 to quit: ";
		std::cin >> data;
		userTree->insert(data);
		if (c == 1)
			std::cout << "Before Splay:" << std::endl;
		else
			std::cout << "Before Semi-Splay:" << std::endl;
		userTree->getRoot()->print(0);
		BSTNode *temp = userTree->search(data);
		if (c == 1) 
			userTree->Splay(temp);
		else
			userTree->semi_Splay(temp);
		if (c == 1)
			std::cout << "After Splay:" << std::endl;
		else
			std::cout << "After Semi-Splay:" << std::endl;
		userTree->getRoot()->print(0);
	} while (data != -1);
	std::cout << "done.";
}