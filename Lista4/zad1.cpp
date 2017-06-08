#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//TODO dodać sprawdzenie NULLi w mainie

typedef struct node {

	int key;
	node *left;
	node *right;
	node *parent;

} node;

typedef struct tree {

	node *root;

} tree;

void inOrder( node *root ) {

//	if ( root == NULL ) {
//		cout << " " << endl;
//	}	
// TODO it will be needed to carry out this case in main

	if ( root->right != NULL ) {
		inOrder( root->right );
	}

	cout << root->key << " ";

	if ( root->left != NULL ){
		inOrder( root->left );
	}

}

void inOrderGood( node *root ) {

	if ( root != NULL ) {
		inOrderGood( root->left );
		cout << root->key << " ";
		inOrderGood( root->right );
	}

}

int find( node *root, int value ) {

	if ( root == NULL ) {
		return 0;
	}

	if ( root->key == value ) {
		return 1;
	}

	if ( value < root->key ) {
		return find( root->left, value );
	} else {
		return find( root->right, value);
	}
}

node* findWithPointer( node *root, int value ) {

	if ( root == NULL ) {
		return NULL;
	}

	if ( root->key == value ) {
		return root;
	}

	if ( value < root->key ) {
		return findWithPointer( root->left, value );
	} else {
		return findWithPointer( root->right, value);
	}
}

int minTree( node *root ) {

	while ( root->left != NULL ) {
		root = root->left;
	}

	return root->key;

}

node* minTreeWithPointer( node *root ) {

	while ( root->left != NULL ) {
		root = root->left;
	}

	return root;

}

int maxTree( node *root ) {

	while ( root->right != NULL ) {
		root = root->right;
	}

	return root->key;

}

void insert( tree *tree, int value ) {

	node *actualParent = NULL;
	node *actualNode = tree->root;

	while ( actualNode != NULL ) {

		actualParent = actualNode;
		
		if ( value < actualNode->key ) {
			actualNode = actualNode->left;
		} else {
			actualNode = actualNode->right;
		}

	}

	if ( actualParent == NULL ) { // empty tree
		tree->root = new node;
		tree->root->key = value;
		tree->root->parent = NULL;
		tree->root->left = NULL;
		tree->root->right = NULL;
	} else if ( value < actualParent->key ) {
		actualParent->left = new node;
		actualParent->left->parent = actualParent;
		actualParent->left->key = value;
		actualParent->left->left = NULL;
		actualParent->left->right = NULL;
	} else {
		actualParent->right = new node;
		actualParent->right->parent = actualParent;
		actualParent->right->key = value;
		actualParent->right->left = NULL;
		actualParent->right->right = NULL;
	}

}

void transplant( tree *tree, node *nodeToDelete, node *nodeToInsert ) {

	if (nodeToDelete->parent == NULL) {
		tree->root = nodeToInsert;
	} else if ( nodeToDelete == nodeToDelete->parent->left ) {
		nodeToDelete->parent->left = nodeToInsert;
	} else {
		nodeToDelete->parent->right = nodeToInsert;
	}

	if ( nodeToInsert != NULL ) {
		nodeToInsert->parent = nodeToDelete->parent;
	}
}

void treeDelete( tree *tree, int value ) {

	node *nodeDelete = findWithPointer( tree->root, value );

	if ( nodeDelete == NULL ) {
		return; // there is no such a node
	}

	if ( nodeDelete->left == NULL ) {
		transplant( tree, nodeDelete, nodeDelete->right );
	} else if ( nodeDelete->right == NULL ) {
		transplant( tree, nodeDelete, nodeDelete->left );
	} else {
		node *var = minTreeWithPointer(nodeDelete->right);

		if ( var->parent != nodeDelete ) {
			transplant(tree, var, var->right);
			var->right = nodeDelete->right;
			var->right->parent = var;
		}
	
		transplant( tree, nodeDelete, var);
		var->left = nodeDelete->left;
		var->left->parent = var;
	}

}

int main() {

	tree *newTree = new tree;

//	for (int i = 0; i < 100; i++) {
//		insert (newTree, i);
//	}

//	inOrder(newTree->root) ;

//	cout << "\n min: " << minTree(newTree->root) << ", max: " << maxTree(newTree->root) << ", find(50): " << find(newTree->root, 50) << ", find(500): " << find(newTree->root, 500) << endl;

//	delete newTree;

	string line; // store current line, next it will be parsed
	string lineToParse;
	string instruction;
	int howMany; // store first value from file - how many rows are in a file
	int argument; // store argument for those functions that require one

	ifstream myfile ("data.txt");

	if (myfile.is_open()){

		getline (myfile, line);
		   
		howMany = stoi(line);

		for (int i = 0; i < howMany; i++) {

			getline (myfile, line);
			istringstream ssLine(line);

			getline( ssLine, lineToParse, ' ' );

			instruction = lineToParse.c_str();
//			cout << instruction << " ";

			if (instruction == "insert" || instruction == "delete" || instruction == "find" ) {

				getline( ssLine, lineToParse, ' ' );
				argument = stoi(lineToParse.c_str());
//				cout << argument;
			}

			if (instruction == "insert") {
				insert(newTree, argument);
			} else if (instruction == "delete") {
				treeDelete(newTree, argument);
				//cout << "abc" << endl;
			} else if (instruction == "find") {
				cout << find(newTree->root, argument) << endl;
			} else if (instruction == "min") {
				if (newTree->root == NULL) {
					cout << endl;
				} else {
					cout << minTree(newTree->root) << endl;
				}
			} else if (instruction == "max") {
				if (newTree->root == NULL) {
					cout << endl;
				} else {
					cout << maxTree(newTree->root) << endl;
				}
			} else if (instruction == "inorder") {
				if (newTree->root == NULL) {
					cout << endl;
				} else {
					inOrderGood(newTree->root);
					cout << endl;
				}
				
			} else {
				cout << "Error: invalid operation!" << endl;
			}
		}
	}

//  else cout << "Unable to open file"; 

//	istringstream iss("This is a string");
//	string s;
//	while ( getline( iss, s, ' ' ) ) {
//	printf( "`%s'\n", s.c_str() );
//	}

}
