#include <iostream>
#include <fstream>
#include <list>

class BSTNode {
public:
	std::string word;
	std::list<int> pages;
	BSTNode *left,*right;

	BSTNode() {left = right = NULL;}
	BSTNode(std::string w){
		word = w;
		left = right = NULL;
	}
	BSTNode(std::string w, int line){
		word = w;
		left = right = NULL;
		pages.push_back(line);
	}
};

class BST {
protected:
	BSTNode *root;
public:
	BST(){ root = NULL; }
	~BST(){ delete(root); root = NULL; }
	bool isEmpty() { return root == NULL; }
	
	BSTNode* search(std::string word) {
		BSTNode *current = root;
		while (current != NULL) {
			if (word == current->word) {
				return current;
			} else if (word[0] < current->word[0]) {
				current = current->left;
			} else if (word[0] == current->word[0]) {
				if (word[1] < current->word[1]) {
					current = current->left;
				} else {
					current = current->right;
				}
			} else {
				current = current->right;
			}
		}
		return current;
	}

	std::list<int> getPages(std::string word) {
		BSTNode *p = search(word);
		return p->pages;
	}

	void insert(std::string word, int line) {
		BSTNode *temp = root, *prev = NULL;
		while (temp != NULL) {
			prev = temp;
			if (word[0] < temp->word[0]) {
				temp = temp->left;
			} else if (word[0] == temp->word[0]) {
				if (word.size() > 1 && temp->word.size() > 1) {
					if (word[1] < temp->word[1]) {
						temp = temp->left;
					} else {
						temp = temp->right;
					}
				} else {
					temp = temp->left;
				}
			} else {
				temp = temp->right;
			}
		}
		if (root == NULL) {
			root = new BSTNode(word, line);
		} else if (word[0] < prev->word[0]) {
				prev->left = new BSTNode(word, line);
		} else if (word[0] == prev->word[0]) {
			if (word.size() > 1 && prev->word.size() > 1) {
				if (word[1] < prev->word[1]) {
					prev->left = new BSTNode(word, line);
				} else {
					prev->right = new BSTNode(word, line);
				}
			} else {
				prev->left = new BSTNode(word, line);
			}
		} else {
			prev->right = new BSTNode(word, line);
		}
	}
};

//read the file and insert each new word into the BST or update the page number
void readFile(BST *tree, std::string file) {
	std::cout<<"reading file..."<<std::endl;
	std::ifstream inFile(file);
	if (!inFile) {
    std::cout << "Unable to open file";
    exit(1);
  }
	std::string line;
	std::string word;
	int line_Num = 0;
	while (std::getline(inFile, line)) {
		line_Num++;
		//make the line lowercase
		for (int i = 0; i < line.size(); i++) {
			line[i] = tolower(line[i]);
		}
		//remove punctuation from the line besides space
		for (int i = 0; i < line.size(); i++) {
			if ((line[i] < 97 || line[i] > 122) && line[i] != ' ') {
				line.erase(i--, 1);
			}
    }
		for (int i = 0; i < line.size(); i++) {
			if (line[i] != ' ') {
				word += line[i];
			} else if (line[i] == ' ' || i == line.size() - 1) {
				BSTNode *node = tree->search(word);
				if (node == NULL) {
					tree->insert(word, line_Num);
				} else {
					node->pages.push_back(line_Num);
				}
				word = "";
			}
		}
	}
	inFile.close();
}

int main() {
	BST *tree = new BST();
	readFile(tree, "MobyDick.txt");	
	std::string word = "";
	do {
		std::cout << "Input a word to search or -1 to quit: ";
		std::cin >> word;
		if (word != "-1") {
			BSTNode *node = tree->search(word);
			if (node != NULL) {
				std::list list = tree->getPages(word);
				std::cout << word << " occurs on line(s) ";
				for (int i: list) {
					std::cout << i << " "; 
				}
				std::cout << std::endl;
			} else {
				std::cout << "That word does not occur." << std::endl;
			}
		}
	} while (word != "-1");
	std::cout << "done." << std::endl;
}