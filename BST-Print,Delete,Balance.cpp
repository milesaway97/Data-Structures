#include <iostream>
#include <math.h>

class BSTNode {
public:
	int el;
	BSTNode *left,*right;

	BSTNode() {left = right = NULL;}
	BSTNode(int e){
		el = e;
		left = right = NULL;
	}
};

class BST {
public:
	BSTNode *root;
	BSTNode *top;
	int level = 0;
	int nodes = 0;

	BST(){ root = NULL; }
	~BST(){ delete(root); root = NULL; }
	bool isEmpty() { return root == NULL; }
	
	BSTNode* search(int el) {
		BSTNode *current = root;
		while (current != NULL) {
			if (el == current->el) {
				return current;
			} else if (el < current->el) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		return current;
	}

	BSTNode* searchParent(int el) {
		BSTNode *current = root;
		BSTNode *prev = NULL;
		while (current != NULL) {
			if (el == current->el) {
				return prev;
			} else if (el < current->el) {
				prev = current;
				current = current->left;
			} else {
				prev = current;
				current = current->right;
			}
		}
		return current;
	}

	void insert(int el) {
		BSTNode *temp = root, *prev = NULL;
		while (temp != NULL) {
			prev = temp;
			if (el < temp->el) {
				temp = temp->left;
			} else {
				temp = temp->right;
			}
		}
		if (root == NULL) {
			root = new BSTNode(el);
		} else if (el < prev->el) {
				prev->left = new BSTNode(el);
		} else {
			prev->right = new BSTNode(el);
		}
		nodes++;
	}

	void printTree(BSTNode* node) {
		if (node == NULL) {
			return;
		}
		for (int i = 0; i < level; i++) {
			std::cout << "     ";
		}
		std::cout << node->el << std::endl;
		if (node->left == NULL && node->right == NULL) {
			level--;
			return;
		}
		if (node->right != NULL) {
			level++;
			printTree(node->right);
		}
		if (node->left != NULL) {
			level++;
			printTree(node->left);
		}
		level--;
	}

	void remove(BSTNode* parent, BSTNode* child) {
		if (parent->left == child) {
			parent->left = NULL;
		} else if (parent->right == child) {
			parent->right = NULL;
		}
	}

	void Delete(int el) {
		BSTNode *node = search(el);
		BSTNode *parent = searchParent(el);
		if (node->left == NULL && node->right == NULL) {
			remove(parent, node);
		} else if (node->left != NULL && node->right != NULL) {
			BSTNode *smallest = node->right;
			while (smallest->left != NULL) {
				smallest = smallest->left;
			}
			int copy = smallest->el;
			Delete(smallest->el);
			node->el = copy;
		} else {
			BSTNode *child;
			if (node->left != NULL) {
				child = node->left;
			} else if (node->right != NULL) {
				child = node->right;
			}
			remove(parent, node);
			if (child->el < parent->el) {
				parent->left = child;
			} else {
				parent->right = child;
			}
		}
	}

	void DeleteByMerging(int el) {
		BSTNode *node = search(el);
		BSTNode *parent = searchParent(el);
		if (node->left != NULL && node->right != NULL) {
			BSTNode *rightmost = node->left;
			while (rightmost->right != NULL) {
				rightmost = rightmost->right;
			}
			rightmost->right = node->right;
			
			if (node->left->el < parent->el) {
				parent->left = node->left;
			} else {
				parent->right = node->left;
			}
		} else {
			Delete(el);
		}
	}

	void backbone() {
		top = root;
		BSTNode *current = root;
		BSTNode *prev = NULL;
		while (current != NULL) {
			if (current->left != NULL) {
				if (prev != NULL) {
					prev->right = current->left;
				}
				BSTNode *child = current->left;
				BSTNode *temp = current;
				current->left = child->right;
				child->right = temp;
				current = child;
				top = child;
			} else {
				prev = current;
				current = current->right;
			}
		}
	}

	void perfect() {
		int log = log2(nodes + 1);
		int m = pow(2, floor(log)) - 1;
		for (int i = 0; i < (nodes - m); i++) {

		} 
		while (m > 1) {
			m = m / 2;
			for (int i = 0; i < m; i++) {

			}
		}
	}

	void DSW() {
		backbone();
		perfect();
	}
};

BST* buildTree() {
	BST* tree = new BST();
	tree->insert(5);
	tree->insert(2);
	tree->insert(12);
	tree->insert(1);
	tree->insert(9);
	tree->insert(3);
	tree->insert(21);
	tree->insert(19);
	tree->insert(25);
	return tree;
}

int main() {
	BST* tree1 = buildTree();
	tree1->printTree(tree1->root);
	tree1->level = 0;
	tree1->Delete(12);
	std::cout << "\nDeleted 12 the simple way:\n" << std::endl;
	tree1->printTree(tree1->root);
	
	BST* tree2 = buildTree();
	tree2->DeleteByMerging(12);
	std::cout << "\nDeleted 12 by merging:\n" << std::endl;
	tree2->printTree(tree2->root);

	BST* tree3 = buildTree();
	std::cout << "\nBalanced BST:\n" << std::endl;
	tree3->DSW();

}