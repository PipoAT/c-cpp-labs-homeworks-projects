// Andrew Pipo
// CS2028C Extra Credit Lab

#include<iostream>
#include<stdlib.h>

// Instructions: on lines 157, 167, and 177, edit the Arrays to desired contents and then
// run program


using namespace std; // standard library

class node {
public:
	string key; // key for the left and right nodes for below functionality
	node* left, * right;

	bool operator <= (node n) {
		return key <= n.key;
	}
	bool operator >= (node n) {
		return key >= n.key;
	}
	bool operator == (node n) {
		return key == n.key;
	}
	bool operator < (node n) {
		return key < n.key;
	}
};

class BinarySearchTree {
private:
	node* root;
	// insert functionality
	node* insert(node* Node, node* newNode)
	{
		if (Node == NULL) return newNode; // return if NULL

		if (newNode->key < Node->key)
			Node->left = insert(Node->left, newNode);
		else if (newNode->key > Node->key)
			Node->right = insert(Node->right, newNode);

		return Node;
	}
	// find functionality
	node* findmin(node* tree) {
		while (tree->left) {
			tree = tree->left;
		}
		return tree;
	}
	// delete node functionality
	node* deletenode(node* tree, string key) {
		node* temp;
		if (!tree)return NULL; // return NULL
		else if (tree->key < key)tree->right = deletenode(tree->right, key);
		else if (tree->key > key)tree->left = deletenode(tree->left, key);
		else if (tree->key == key) {
			if (!tree->left) {
				temp = tree->right;
				delete(tree);
				return temp;
			}
			if (!tree->right) {
				temp = tree->left;
				delete(tree);
				return temp;
			}
			temp = findmin(tree->right);
			tree->key = temp->key;
			deletenode(tree->right, temp->key);
		}
		else
			cout << "key not found\n";


		return tree;
	}
	// search functionality
	node* search(node* Node, string key)
	{

		if (Node == NULL || Node->key == key)
			return Node;

		if (Node->key < key)
			return search(Node->right, key);

		return search(Node->left, key);
	}
	// size functionality
	int size(node* Node) {
		if (!Node)return 0;
		return 1 + size(Node->left) + size(Node->right);
	}
	// increasing order
	void inorder(node* Node, string& arr) {
		if (!Node)return;
		inorder(Node->left, arr);
		arr += Node->key + "\n";
		inorder(Node->right, arr);
	}
	// decreasing order
	void DecOrder(node* Node, string& arr) {
		if (!Node)return;
		DecOrder(Node->right, arr);
		arr += Node->key + "\n";
		DecOrder(Node->left, arr);


	}


public:
	BinarySearchTree() { // sets root as NULL
		root = NULL;
	}

	void Insert(string item)
	{
		node* temp = new node;
		temp->key = item;
		temp->left = NULL;
		temp->right = NULL;
		root = insert(root, temp);
	}

	void Remove(string item) {
		root = deletenode(root, item);
	}

	node* find(string item) {
		return search(root, item);
	}
	int Size() {
		return size(root);
	}
	string GetAllAscending() {
		string arr = "";
		inorder(root, arr);
		return arr;
	}
	string GetAllDescending() {
		string arr = "";
		DecOrder(root, arr);
		return arr;
	}

};


int main()

// Set of preset array "test cases" below that can be modified to highlight the functionality of the program

{
	
	BinarySearchTree bst1;
	string arr1[] = {"Ending", "Start", "End"}; // modify array if wanted
	for (int i = 0; i < size(arr1); i++) {
		bst1.Insert(arr1[i]);
	}

	cout << bst1.Size() << "\n"; // returns the size, and the ascending and descending orders of the array
	cout << bst1.GetAllAscending() << "\n"; // calls and prints
	cout << bst1.GetAllDescending() << "\n"; // calls and prints

	BinarySearchTree bst2;
	string arr2[] = { "Cars", "Monsters" ,"The Incredibles", "Wall-E" }; // modify array if wanted
	for (int i = 0; i < size(arr2); i++) {
		bst2.Insert(arr2[i]);
	}

	cout << bst2.Size() << "\n"; // same operations as bst1
	cout << bst2.GetAllAscending() << "\n";
	cout << bst2.GetAllDescending() << "\n";

	BinarySearchTree bst3;
	string arr3[] = { "Halloween", "A Nightmare On Elm Street", "Hocus Pocus", "Beetlejuice", "Nightmare"}; // modify array if wanted
	for (int i = 0; i < size(arr3); i++) {
		bst3.Insert(arr3[i]);
	}

	cout << bst3.Size() << "\n"; // same operations as bst1 and bst2
	cout << bst3.GetAllAscending() << "\n";
	cout << bst3.GetAllDescending() << "\n";

	return 0;
}