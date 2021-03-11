#include "treap_bst.hpp"

#include <algorithm>
#include <stack>
#include <stdexcept>

//default constructor
//creates a default Treap, which is an empty treap and does so by setting the root to null pointer, which implies there are no nodes that are storing anything
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST() : root(nullptr)
{
  std::random_device rd;
  rndgen.seed(rd());
}

//copy constructor
//creates a deep copy of the object that is passed through the function
//the objects root that is passed through the function used to call the helper method copyTreap that copies all the nodes of the object that is passed starting with the root node
//and then sets the root of the new treap that is being cretaed and all the nodes that follow are set as well
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST(const TreapBST &x) {
	root = copyTreap(x.root);
}

//copy assignement operator
//creates a deep copy by using the copy-swap idium and does so by passing the object that is the paramter of the function to the helper functrion
//which swaps the roots of the object that is passed to the object that is to be created and returns the newly created object, whcih is a copy of the treap that is passed through
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>& TreapBST<KeyType, ValueType>::operator=(TreapBST x) {
	swap(*this, x);

	return *this;
}

//destructor
//frees any memory that is allocated throughout the program and does so by calling the helper function destroyTreap, which deletes all the nodes of the treap
//starting with the root that is passed through the destroyTreap function
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::~TreapBST() {
	destroyTreap(root);
}

//returns a boolean that is true if the treap is empty and false otherwise
//an empty treap is denoted by the root being equal to null pointer as the default constructor displays, if there are no nodes in the treap the root will be a nullptr
template <typename KeyType, typename ValueType>
bool TreapBST<KeyType, ValueType>::empty() {
	return root == nullptr;
}

//a function to search for a node based on the given key and returns two things implicitly
//if the key that is passed through is in the treap the boolean that is passed by reference will be set to true and can be used to tell if the key is in the treap already
//the function also returns the data of the node for the given key if that key is found in the treap, if the key is not found in the treap found is set to false and returns a default ValueType
template <typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::search(const KeyType &key, bool &found) {
	Node<KeyType, ValueType>* ptrNext = root;
	found = false;

	while (ptrNext != nullptr) {
		if (ptrNext == nullptr) {
			found = false;
		}
		else if (ptrNext->key == key) {
			found = true;
			break;
		}
		else if (ptrNext->key > key) {
			ptrNext = ptrNext->childl;
		}
		else if (ptrNext->key < key) {
			ptrNext = ptrNext->childr;
		}
	}
	
	if (found) {
		return ptrNext->data;
	}
	else {
		return ValueType();
	}
}

//a method that inserts a node based on a given key and a priority that is generated randomly the value is just a number that is associated with the node that is inserted
//first the method makes sure the key that is being referenced is unique and does not exist in the treap already and if it does it throws a logic error
//if the key is unique then the root is set by calling the helper insert method that recursively inserts a node starting with the root node and setting all subsequent children nodes
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
	bool flag;
	search(key, flag);
	if (flag == true) {
		throw std::logic_error("key already exists");
	}
	else{
		root = insert(root, key, value);
	}
	
	
}

//remove method that deletes a node based on the given key
//if the treap is empty an exception is thrown because you cannot remove from an empty treap
//if not empty the root node is set by calling the remove helper method that recursively removes a node and sets the root node that is passed thrugh and all the subsequent children nodes
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::remove(const KeyType &key) {

	if (empty()) {
		throw std::logic_error("Cannot remove from empty treap");
	}
	else {
		root = deleteNode(root, key);
	}
		
}

//returns the height of the treap, does so by calling the helper method heightHelper
//which is a method that recursively calls itself to set the height based on the max hight for the treap(further explanation seen at that method)
template <typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType>::height() {
	return heightHelper(root);
}

//helper method for inserting and removing nodes in order to keep the max-heap in check
//descriptions for when these methods are used can be seen at the helper methods for remove and insert
//rotates the treap right around the node that is passed through and sets the subsequent children
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* TreapBST<KeyType, ValueType>::rotateRight(Node<KeyType, ValueType>* subtree) {
	//initialzes a node to be returned as the new node fter rotation
	Node<KeyType, ValueType>* p = subtree->childl;

	//performs rotation
	subtree->childl = p->childr;
	p->childr = subtree;

	//returns the new root
	return p;
}

//helper method for inserting and removing nodes in order to keep the max-heap in check
//descriptions for when these methods are used can be seen at the helper methods for remove and insert
//rotates the treap left around the node that is passed through and sets the subsequent children
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* TreapBST<KeyType, ValueType>::rotateLeft(Node<KeyType, ValueType>* subtree) {
	//initialzes a node to be returned as the new node fter rotation
	Node<KeyType, ValueType>* q = subtree->childr;

	//performs rotation
	subtree->childr = q->childl;
	q->childl = subtree;

	//returns the new root
	return q;
} 

//helper method for the method that inserts a node based on a given key
//recursive function that sets the children of the node passed through. first based on the binary search tree properties and then
//inserts based on a priority that is generated randomly by the node's struct and if the max-heap priority is violated the treap is rotated by calling the rotate methods
//at the proper times, returns the node that is being inserted after is is operated on and the insert method sets that as the root
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* TreapBST<KeyType, ValueType>::insert(Node <KeyType, ValueType>* subtree, const KeyType &key, const ValueType &value) {
	if (subtree == nullptr) {
		return new Node<KeyType, ValueType>(key, value);
	}
	
	if (key < subtree->key) {
		subtree->childl = insert(subtree->childl, key, value);
		if (subtree->childl->priority > subtree->priority) {
			subtree = rotateRight(subtree);
		}
	}
	else {
		subtree->childr = insert(subtree->childr, key, value);
		if (subtree->childr->priority > subtree->priority) {
			subtree = rotateLeft(subtree);
		}
	}
	return subtree;
}

//helper method for the prior method that removes a node from the treap
//recursively calls itself in order to set the subsequent children of the node that is passed through the function
//if the node passed through is null it returns that node 
//if the BST properties are not held up the treap is reordered so they are and the same goes for the heap priority porperties
//the node that is then set by teh subsequent if statements is returned and the node is delted by the remove method above setting the root equal to the node returned
//and the treap holds up all its properties, while getting rid of a single node denoted by its key
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* TreapBST<KeyType, ValueType>::deleteNode(Node<KeyType, ValueType>* subtree, const KeyType &key) {

	if (subtree == nullptr) {
		return subtree;
	}

	if (key < subtree->key) {
		subtree->childl = deleteNode(subtree->childl, key);
	}
	else if (key > subtree->key) {
		subtree->childr = deleteNode(subtree->childr, key);
	}
	else if (subtree->childl == nullptr) {
		Node<KeyType, ValueType>* temp = subtree->childr;
		delete subtree;
		subtree = temp;
	}
	else if (subtree->childr == nullptr) {
		Node<KeyType, ValueType>* temp = subtree->childl;
		delete subtree;
		subtree = temp;
	}
	else if (subtree->childl->priority < subtree->childr->priority) {
		subtree = rotateLeft(subtree);
		subtree->childl = deleteNode(subtree->childl, key);
	}
	else {
		subtree = rotateRight(subtree);
		subtree->childr = deleteNode(subtree->childr, key);
	}
	return subtree;
}

//helper method for the copy constructor
//takes in a node as the paramter for the function, usually the root node and sets all the subsequent children nodes for the new node that is created
//this new node is returned after the function uses recursion to set all its children which is used in order to create the copy of the entire treap that needs to be copied
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* TreapBST<KeyType, ValueType>::copyTreap(const Node<KeyType, ValueType>* subtree) {
	Node<KeyType, ValueType>* ptr = nullptr;

	if (subtree != nullptr) {
		ptr = new Node<KeyType, ValueType>(subtree->key, subtree->data);

		ptr->childl = copyTreap(subtree->childl);
		ptr->childr = copyTreap(subtree->childr);
	}
	return ptr;
}

//helper method for the destructor that deletes all the nodes for a given treap denoted by the root that is passed through the function
//destructor calls this function that goes through all the nodes starting wth the node and then its subsequent children nodes and deletes them one by one
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::destroyTreap(Node<KeyType, ValueType>* subtree) {
	if (subtree != nullptr) {
		destroyTreap(subtree->childl);
		destroyTreap(subtree->childr);
		delete subtree;
	}
}

//helper method for the method above that returns the height of the treap
//the root is passed through the sunction and then recursion is used to get the max height of the children of the node that is passed through
//if the treap is empty then the height is zero, and otherwise 1 is denoted for the current levela nd adds the recursive result of going through all the nodes
template <typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType>::heightHelper(Node<KeyType, ValueType>* subtree) {
	if (subtree == nullptr) {
		return 0;
	}
	else {
		return 1 + std::max(heightHelper(subtree->childl), heightHelper(subtree->childr));
	}
}

//helper method for the copy assignment operator
//uses the standard swap function to swap the roots of the twp objects that are passed by reference to the fucntion
//creates a swap of the roots, which can be used to copy the proper paramters for the copy assignment opertor to create a deep copy
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::swap(TreapBST<KeyType, ValueType>& x, TreapBST<KeyType, ValueType>& y) {
	std::swap(x.root, y.root);
}

//methods that were used to debug the treap when writing the program that just prints the details of the treap
/*
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::print() {
	//printTreap(root);
	inorderPrint(root);
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::inorderPrint(Node<KeyType, ValueType>* subtree)
{
	if (subtree)
	{
		inorderPrint(subtree->childl);
		std::cout << "key: " << subtree->key << " | priority: %d "
			<< subtree->priority;
		if (subtree->childl)
			std::cout << " | left child: " << subtree->childl->key;
		if (subtree->childr)
			std::cout << " | right child: " << subtree->childr->key;
		std::cout << std::endl;
		inorderPrint(subtree->childr);
	}
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::inOrder(Node<KeyType, ValueType>* subTree) {
	if (subTree != nullptr) {
		inOrder(subTree->childl);
		std::cout << "data: " << subTree->data << " pri: " << subTree->priority << " " << "key: " << subTree->key << " ";
		inOrder(subTree->childr);
	}
}
*/