#ifndef TREAP_BST_HPP
#define TREAP_BST_HPP

#include <random>
#include <iostream>

#include "abstract_bst.hpp"

template <typename KeyType, typename ValueType>
class TreapBST : public AbstractBST<KeyType, ValueType>
{
public:
	/** Default contructor. */
	TreapBST();

	/** Copy constructor. */
	TreapBST(const TreapBST &x);

	/** Copy-assignment. */
	TreapBST &operator=(TreapBST x);

	/** Destructor. */
	~TreapBST();

	bool empty();

	/** Search for key.
	If found is true, returns the value associated with that key.
	If found is false, returns a default constructed ValueType. */
	ValueType search(const KeyType &key, bool &found);

	/* Insert value into the BST with unique key.
	 thows std::logic_error if key is already in the tree. */
	void insert(const KeyType &key, const ValueType &value);

	/* Remove value from the BST with key.
	 Do nothing if there is no such key in the BST.
	 throws std::logic_error if empty. */
	void remove(const KeyType &key);

	/** Get the height of the treap. */
	std::size_t height();
	
	//used for debugging
	//void print();


private:
	/* Random number generator. */
	std::mt19937 rndgen;

	/* Node struct with key, data, random priority, and parent, left child, and right child pointers. */
	template <typename K, typename V>
	struct Node
	{
		K key;
		V data;
		std::mt19937::result_type priority;
		Node* parent;
		Node* childl;
		Node* childr;

		Node(const K& k, const V& d, Node* p = nullptr)
			: key(k)
			, data(d)
			, parent(p)
			, childl(nullptr)
			, childr(nullptr)
		{
			priority = rand() % 100;
		}
	};

	// You may add private member variables/methods as needed.
	//defining the variable root node for use htroughout the program
	Node<KeyType, ValueType>* root;

	//method that rotates a treap right in order to hold max-heap properties
	TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* rotateRight(Node<KeyType, ValueType>* subtree);

	//method that rotates a treap left in order to hold max-heap properties
	TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* rotateLeft(Node<KeyType, ValueType>* subtree);

	//used for debugging
	//void inOrder(Node<KeyType, ValueType>* subTree);

	//helper method for the insert method
	TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* insert(Node <KeyType, ValueType>* subtree, const KeyType &key, const ValueType &value);

	//helper method for the remove method
	TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* deleteNode(Node<KeyType, ValueType>* subtree, const KeyType &key);

	//helper method for the copy constructor
	TreapBST<KeyType, ValueType>::Node<KeyType, ValueType>* copyTreap(const Node<KeyType, ValueType>* subtree);

	//helper method for the destructor
	void destroyTreap(Node<KeyType, ValueType>* subtree);

	//helper method for the height() method
	std::size_t heightHelper(Node<KeyType, ValueType>* subtree);

	//helper method for the copy assignment operator
	void swap(TreapBST<KeyType, ValueType>& x, TreapBST<KeyType, ValueType>& y);

	//used for debugging
	//void inorderPrint(Node<KeyType, ValueType>* subtree);
};

#include "treap_bst.txx"

#endif // TREAP_BST_HPP
