#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>

std::unordered_map<char, std::string> codes;
std::unordered_map<char, int> freq;

class Node {
public:
	char key;
	double freq;
	Node *left;
	Node *right;

	Node(char x, double y) {
		key = x;
		freq = y;
		left = NULL;
		right = NULL;
	}
	Node(double y) {
		freq = y;
		left = NULL;
		right = NULL;
	}
};

//to compare two frequencies
class myComparator {
public:
  bool operator() (Node *n1, Node *n2) {
    return n1->freq > n2->freq;
  }
};

//map each character to its code
void storeCodes(Node *root, std::string str) {
	if (root->key != '$') {
		codes.insert({root->key, str});
	}
	if (root->left != NULL)
  	storeCodes(root->left, str + "0"); 
  if (root->right != NULL)
		storeCodes(root->right, str + "1");
}

//encode the input string and return the binary code
std::string encode(std::string text) {
	std::string codedtext = "";
	for (int i = 0; i < text.size(); i++) {
		codedtext += codes.at(text[i]);
	}
	return codedtext;
}

//decode the binary string and return the decoded message
std::string decode(Node *root, std::string code) {
	std::string answer = "";
	Node *temp = root;
	for (int i = 0; i <= code.size(); i++) {
		if (temp->left == NULL && temp->right == NULL) {
			answer += temp->key;
			temp = root;
		}
		if (code[i] == '0') 
			temp = temp->left;
		else if (code[i] == '1')
			temp = temp->right;
	}
	return answer;
}

//read the file and store frequencies of each character
void readFile(std::string file) {
	std::ifstream inFile;
	inFile.open(file);
	if (!inFile) {
    std::cout << "Unable to open file";
    exit(1);
  }
	std::string word;
	double total = 0;
	freq.insert({' ', 0});
	while (inFile >> word) {
		for (int i = 0; i < word.size(); i++) {
			total++;
			//if key is not present
			if (freq.find(word[i]) == freq.end()) {
				freq.insert({word[i], 1});
			} else {
				//if key already exists
				freq.find(word[i])->second = freq.at(word[i]) + 1;
			}
		}
		freq.find(' ')->second = freq.at(' ') + 1;
	}
	inFile.close();
}

//generate the binary code tree
Node* Huffman() {
	//min heap help from https://www.geeksforgeeks.org/implement-min-heap-using-stl/
	std::priority_queue <Node*, std::vector<Node*>, myComparator> pq;
	for (std::unordered_map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++) {
        pq.push(new Node(v->first, v->second));
	}
	//huffman encoding help https://www.geeksforgeeks.org/huffman-decoding/?ref=lbp
	Node *left, *right, *top;
	while(pq.size() > 1) {
		left = pq.top();
		pq.pop();
		right = pq.top();
		pq.pop();
		top = new Node(left->freq + right->freq);
		top->left = left;
		top->right = right;
		pq.push(top);
	}
	Node *root = pq.top();
	pq.pop();
	return root;
}

int main() {
	readFile("kidsstory.txt");
	Node *root = Huffman();
	storeCodes(root, "");

	//testing the binary code tree by encoding then decoding a text input
	for(int i = 0; i < 6; i++)
		std::cout << "    ";
	std::cout << "Testing" << std::endl;
	for(int i = 0; i < 15; i++)
		std::cout << "----";
	std::cout << std::endl;
	std::string code1 = encode("using namespace std is considered bad practice.");
	std::cout << "Test 1: " << decode(root, code1) << std::endl;
	std::string code2 = encode("A binary code tree is a binary tree in which each non-leaf node has two edges such that the left edge is labeled zero and the right edge labeled one.");
	std::cout << "Test 2: " << decode(root, code2) << std::endl;
	std::string code3 = encode("(ab.c;d-E,f_gh:Ij.KlM?no.P-q,RstU_v-Wx_y;z)");
	std::cout << "Test 2: " << decode(root, code3) << std::endl;
}

