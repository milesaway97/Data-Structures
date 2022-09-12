#include <fstream>
#include <vector>
#include <iostream>
#include <locale>
using namespace std;

class TextNode {
public:
  string first;
	string second;
  TextNode *next;
	TextNode *prev;
    
  TextNode(string one, string two) {
    first = one;
		second = two;
    next = NULL;
		prev = NULL;
  }
};

class TextList {
private:
	int size;
  TextNode *head;
  TextNode *tail;
    
public:
  TextList() {
		size = 0;
    head = NULL;
    tail = NULL;
  }
	//inserts strings one and two at the head of the list
  void insertHead(string one, string two) {
    TextNode *newNode = new TextNode(one, two);
		if (tail == NULL) {
      tail = newNode;
    }
    newNode->next = head;
    head = newNode;
		size ++;
  }
	//inserts one and two at the tail of the list
  void insertTail(string one, string two) {
    TextNode *newNode = new TextNode(one, two);
		if (tail == NULL) {
			tail = newNode;
			head = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
			size ++;
		}
  }
	//returns a node equal to node at position i
  TextNode* getNode(int i) {
    TextNode *current = head;
    for (int j = 0; j < i; j++) {
			current = current->next;
    }
		return current;
  }
	void swapWithPrev(int i) {
		if (i != 0 && i != (getSize() - 1)) {
			TextNode *temp = head->next;
			TextNode *prev = head;
			for (int j = 0; j < i - 1; j++) {
				temp = temp->next;
				prev = prev->next;
			}
			prev->next = temp->next;
			temp->next = temp->next->next;
			prev->next->next = temp;
		}
	}
	//get the size of the list
	int getSize() {
		return size;
	}
};

void textSearch() {
	ifstream inFile;
	inFile.open("kidsstory.txt");
	if (!inFile) {
    cout << "Unable to open file";
    exit(1);
  }
	ifstream stopFile;
	stopFile.open("stopwords.txt");
	if (!stopFile) {
    cout << "Unable to open file";
    exit(1);
  }

	//input all words in stopwords.txt into a vector
	vector<string> stopwords;
	string stop;
	while (stopFile >> stop) {
		stopwords.push_back(stop);
	}
	stopFile.close();

	cout << "Reading File..." << endl;

	//input valid words in MobyDick.txt into a vector
	vector<string> words;
	string word;
	while (inFile >> word) {
		//make the word lowercase
		for (int i = 0; i < word.size(); i++) {
			word[i] = tolower(word[i]);
		}
		//remove punctuation from the word
		for (int i = 0; i < word.length(); i++) {
			if (word[i] < 97 || word[i] > 122) {
				word.erase(i--, 1);
			}
    }
		//if the word is not a stop word, input it into the vector
		bool notastop = true;
		for (int i = 0; i < stopwords.size(); i++) {
			if (word == stopwords.at(i))
				notastop = false;
		}
		if (notastop)
			words.push_back(word);
	}
	inFile.close();

	cout << "Constructing Linked List..." << endl;

	//construct the linked list of word pairs
	TextList list = TextList();
	for (int i = 0; i < words.size() - 1; i++) {
		bool found = false;
		//search list to see if current word pair exists in list
		if (list.getSize() == 0) {
			list.insertTail(words.at(i), words.at(i + 1));
		} else {
			TextNode *current;
			for (int j = 0; j < list.getSize(); j++) {
					current = list.getNode(j);
					//if this word pair already exists in list, swap it with its predecessor
					if (current->first == words.at(i) && current->second == words.at(i + 1)) {
						found = true;
						list.swapWithPrev(j);
						break;
					}	
			}
			//if the word pair doesn't exist yet, add it to tail of the list
			if (!found) {
				list.insertTail(words.at(i), words.at(i + 1));
			}
		}
	}

	cout << "Linked List size= " << list.getSize() << endl;
	
	//user inputs a word, outputs the 3 most common nodes starting with that word
	string input;
	while (input != "z") {
		cout << "Enter a word to search, or 'z' to quit: ";
		cin >> input;
		if (input != "z") {
			cout << endl << "Recommendations: " << endl;
			TextNode *current;
			int count = 0;
			for (int i = 0; i < list.getSize() && count < 3; i++) {
				current = list.getNode(i);
				if (input == current->first) {
					cout << current->first << " " << current->second << ", ";
					count++;
				}
			}
			//user selects a recommendation, and the list is updated
			if (count != 0) {
				cout << endl << "Select a recommendation: ";
				string rec1, rec2;
				cin >> rec1 >> rec2;
				for (int i = 0; i < list.getSize(); i++) {
					current = list.getNode(i);
					if (rec1 == current->first && rec2 == current->second) {
						list.swapWithPrev(i);
						cout << "Node '" << rec1 << " " << rec2 << "' has been updated." << endl;
						break;
					}
				}
			}
		}
	}
	cout << "Done!" << endl;
}

int main() {
	textSearch();
}