#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>



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

int findForTest( node *root, int value, int *counterCompare ) {

	if ( root == NULL ) {
		return 0;
	}

	if ( root->key == value ) {
		return 1;
	}

	if ( value < root->key ) {
		(*counterCompare) += 1;
		return findForTest( root->left, value, counterCompare );
	} else {
		//(*counterCompare) += 1;
		return findForTest( root->right, value, counterCompare );
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

void descendArray(vector <int> *array, int size) {
	for (int i = 1; i <= size; i++) {
		array->push_back (size - i);
	}
}

void descendArrayAgain(vector <int> *array, int size) {
	for (int i = 1; i <= size; i++) {
		(*array)[i-1] =  (size - i);
	}
}

void randomPermutationArray(vector <int> *array, int size) {
	descendArray(array, size);
	random_shuffle(array->begin(), array->end());
}

void randomPermutationArrayAgain(vector <int> *array, int size) {
	descendArrayAgain(array, size);
	random_shuffle(array->begin(), array->end());
}

int main() {

	vector <int> *mainArray = new vector <int>;
	vector <int> *compareCount = new vector <int>;

	randomPermutationArray( mainArray, 1000 );

	int counterCompare;

	for (int i = 0; i < 1000; i++ ) {

		tree *newTree = new tree;
		newTree->root = NULL;

		randomPermutationArrayAgain( mainArray, 1000 );

		for ( int i = 1; i < 1000; i++ ) {

			insert( newTree, (*mainArray)[i] );

		}

		for (int i = 0; i < 100; i++) {
			counterCompare = 0;

			findForTest( newTree->root, std::rand() % 1000, &counterCompare );
			compareCount->push_back (counterCompare);
		}
		delete newTree;
	}

	ofstream myfile;
	myfile.open ("plot.txt");
	for (int i = 0; i < 100000; i++) {
		myfile << i << " " << (*compareCount)[i] << endl ;
	}
	myfile.close();
		
	system("gnuplot -p -e \"plot 'plot.txt' using 1:2 with dots\"");

	auto biggest = std::max_element(std::begin((*compareCount)), std::end((*compareCount)));
	std::cout << "Max number of compares: " << *biggest << endl;

	auto smallest = std::min_element(std::begin((*compareCount)), std::end((*compareCount)));
	std::cout << "Min number of compares: " << *smallest << endl;

	float avg = accumulate( (*compareCount).begin(), (*compareCount).end(), 0.0)/(*compareCount).size(); 
	std::cout << "Avg number of compares: " << avg << endl;

	delete mainArray;
	delete compareCount;	
}
