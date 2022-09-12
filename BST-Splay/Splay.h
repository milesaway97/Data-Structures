#include <iostream>

class BSTNode {
private:
	int el;
	BSTNode *left, *right, *parent;

public:
	BSTNode(int x) {
		el = x;
		left = right = parent = NULL;
	}
	BSTNode(int x, BSTNode *p) {    
		el = x;    
		parent = p;    
		left = right = NULL;  
	}
	int getEl() {
		return el;
	}
	BSTNode* getLeft() {
		return left;
	}
	BSTNode* getRight() {
		return right;
	}
	BSTNode* getPar() {
		return parent;
	}
	void setLeft(BSTNode* node) {
		left = node;
	}
	void setRight(BSTNode* node) {
		right = node;
	}
	void setParent(BSTNode* node) {
		parent = node;
	}
	void printhelper(int indent, int i) {
		if(i > 5)
			return;
		// if(parent != NULL) {
		// 	if(parent->left == this)
		// 		std::cout << "L ";
		// 	else if(parent->right == this)
		// 		std::cout << "R ";
		// }
		std::cout << el << std::endl;   
		indent++; i++; 
		if (right != NULL) {      
			for (int i = 0; i < indent ; i++ ) 
				std::cout << "\t";      
			right->printhelper(indent, i);    
		}    
		if (left != NULL) {      
			for (int i = 0; i < indent ; i++ ) 
				std::cout << "\t";      
			left->printhelper(indent, i);    
		} 
	}
	void print(int indent) {
     printhelper(indent, 0);
	}
};

class BST {
private:
	BSTNode *root;

public:
	BST(){ root = NULL; }
	BST(BSTNode* r) {
		root = r;
	}

	BSTNode* getRoot() {
		return root;
	}
	
	BSTNode* search(int el) {
		BSTNode *current = root;
		while (current != NULL) {
			if (el == current->getEl()) {
				return current;
			} else if (el < current->getEl()) {
				current = current->getLeft();
			} else {
				current = current->getRight();
			}
		}
		return current;
	}

	void insert(int el) {
		BSTNode *temp = root, *prev = NULL;
		while (temp != NULL) {
			prev = temp;
			if (el < temp->getEl()) {
				temp = temp->getLeft();
			} else {
				temp = temp->getRight();
			}
		}
		if (root == NULL) {
			root = new BSTNode(el);
		} else if (el < prev->getEl()) {
				prev->setLeft(new BSTNode(el, prev));
		} else {
			prev->setRight(new BSTNode(el, prev));
		}
	}

	void rotateRight(BSTNode *Ch) {    
//std::cout << "rotating right: " << Ch->getEl() << std::endl;
		if (Ch == root) {
			BSTNode *leftchild = Ch->getLeft();
			if (leftchild->getRight() != NULL) {
				Ch->setLeft(leftchild->getRight());
			} else {
				Ch->setLeft(NULL);
			}
			leftchild->setRight(Ch);
			Ch->setParent(leftchild);
			leftchild->setParent(NULL);
			root = leftchild;
//root->print(0);
			return;
		}	
		BSTNode *Par = Ch->getPar();
		if (Par != root ) {      
			BSTNode *Gr = Ch->getPar()->getPar();
			//Gr becomes Ch's parent      
			Gr->setRight(Ch);      
			Ch->setParent(Gr);      
			if (Ch->getRight() != NULL) {      
				// right child of Ch (Q) becomes left child of Par        
				Par->setLeft(Ch->getRight());        
				Ch->getRight()->setParent(Par); 
				//only works when Q is not null      
			} else {        
				Par->setLeft(NULL);      
			}      
			//Ch acquires Par as its right child      
			Ch->setRight(Par);      
			Par->setParent(Ch); 
			Par->setRight(NULL);  
//root->print(0); 
		} else {      
			if (Ch->getRight() != NULL) {      
				// right child of Ch (Q) becomes left child of Pa        
				Par->setLeft(Ch->getRight());        
				Ch->getRight()->setParent(Par); 
				//only works when Q is not null      
			} else {        
				Par->setLeft(NULL);      
			}      
			//Ch acquires Par as its right child      
			Ch->setRight(Par);      
			Par->setParent(Ch);    
			if (Par->getRight() == Ch)
				Par->setRight(NULL);			  
			root = Ch;
//root->print(0);
		}   
	}  

	void rotateLeft(BSTNode *Ch) {    
//std::cout << "rotating left: " << Ch->getEl() << std::endl;		
		if (Ch == root) {
			BSTNode *rightchild = Ch->getRight();
			if (rightchild->getLeft() != NULL) {
				Ch->setRight(rightchild->getLeft());
			} else {
				Ch->setRight(NULL);
			}
			rightchild->setLeft(Ch);
			Ch->setParent(rightchild);
			rightchild->setParent(NULL);
			root = rightchild;
//root->print(0);
			return;
		} 
		BSTNode *Par = Ch->getPar();
		if (Par != root ) {      
			BSTNode *Gr = Ch->getPar()->getPar();
			//Gr becomes Ch's parent      
			Gr->setLeft(Ch);      
			Ch->setParent(Gr);      
			if (Ch->getLeft() != NULL) {      
				// left child of Ch (Q) becomes right child of Par        
				Par->setRight(Ch->getLeft());        
				Ch->getLeft()->setParent(Par); 
				//only works when Q is not null      
			} else {        
				Par->setRight(NULL);      
			}      
			//Ch acquires Par as its left child      
			Ch->setLeft(Par);      
			Par->setParent(Ch);
			Par->setLeft(NULL);  
//root->print(0);
		} else {      
			if (Ch->getLeft() != NULL) {      
				// left child of Ch (Q) becomes right child of Pa        
				Par->setRight(Ch->getLeft());        
				Ch->getLeft()->setParent(Par); 
				//only works when Q is not null      
			} else {        
				Par->setRight(NULL);      
			}      
			//Ch acquires Par as its left child      
			Ch->setLeft(Par);      
			Par->setParent(Ch);  
			if (Par->getLeft() == Ch) 
				Par->setLeft(NULL);			   
			root = Ch;
//root->print(0);
		}   
	} 

	void Splay(BSTNode *temp) {
		if (temp == root) {
			return;
		}
		int i = 0;
		while(temp->getPar() != NULL) {
			if( i > 3)
				return;
			i++;
			//if temp is a child of root
			if (root->getLeft()==temp || root->getRight()==temp) {
				if (root->getLeft()==temp) {  //if temp is left child of root
					rotateRight(root); 
				} else if (root->getRight()==temp) { //else if temp is right child of root
					rotateLeft(root);  
				}
			} else {   //if temp is lower in tree
				BSTNode *father = temp->getPar();
				BSTNode *grandfather = temp->getPar()->getPar();
				if (grandfather->getLeft() == father) {  //if father is left child
					if(father->getLeft() == temp) {   //if temp is left child of father
						rotateRight(grandfather);   //zig-zig
						rotateRight(father);        
					} else if ( father->getRight() == temp ) {  //if temp is right child of father
						rotateLeft(father);    //zig-zag
						rotateRight(grandfather);
					}
				}
				if (grandfather->getRight() == father) {  //if father is right child
					if(father->getRight() == temp) {	//if temp is right child of father
						rotateLeft(grandfather);	//zag-zag
						rotateLeft(father);
					} else if (father->getLeft() == temp) {  //if temp is left child of father
						rotateRight(father);	//zag-zig
						rotateLeft(grandfather);
					}
				}
			}
		}
	}

	void semi_Splay(BSTNode *temp) {
		if (temp == root) {
			return;
		}
		int i = 0;
		while(temp->getPar() != NULL) {
			if( i > 3)
				return;
			i++;
			//if temp is a child of root
			if (root->getLeft()==temp || root->getRight()==temp) {
				if (root->getLeft()==temp) {  //if temp is left child of root
					rotateRight(root); 
				} else if (root->getRight()==temp) { //else if temp is right child of root
					rotateLeft(root);  
				}
			} else {   //if temp is lower in tree
				BSTNode *father = temp->getPar();
				BSTNode *grandfather = temp->getPar()->getPar();
				if (grandfather->getLeft() == father) {  //if father is left child
					if(father->getLeft() == temp) {   //if temp is left child of father
						rotateRight(grandfather);   //zig-zig
						temp = father;
					} else if ( father->getRight() == temp ) {  //if temp is right child of father
						rotateLeft(father);    //zig-zag
						rotateRight(grandfather);
					}
				}
				if (grandfather->getRight() == father) {  //if father is right child
					if(father->getRight() == temp) {	//if temp is right child of father
						rotateLeft(grandfather);	//zag-zag
						temp = father;
					} else if (father->getLeft() == temp) {  //if temp is left child of father
						rotateRight(father);	//zag-zig
						rotateLeft(grandfather);
					}
				}
			}
		}
	}
};