#include "dLinkedList.hpp"
#include "dNode.hpp"
#include <iostream>

template<class T>
void dLinkedList<T>::printList() const
{
    std::cout << "Printing out content of list of size: " << itemCount << std::endl;
    std::cout << "The items are: " << "\t";

    dNode<T>* curPtr = headPtr;
    int counter = 0;
    while ((curPtr != nullptr) && (counter < itemCount))
    {
        std::cout << curPtr->getItem() << "\t";
        curPtr = curPtr->getNext();
        counter++;
    }
    std::cout << std::endl;
}

template<class T>
void dLinkedList<T>::printReverseList() const
{
    std::cout << "Printing out (in reverse) content of list with size: " << itemCount << std::endl;
    std::cout << "The items are: " << "\t";
    
    dNode<T>* curPtr = tailPtr;
    int counter = 0;
    while ((curPtr != nullptr) && (counter < itemCount))
    {
        std::cout << curPtr->getItem() << "\t";
        curPtr = curPtr->getPrev();
        counter++;
    }
    std::cout << std::endl;
}

//default constrcutor for linked list class
//creates an empty list with head pointer being null and no items
template<class T>
dLinkedList<T>::dLinkedList() : headPtr(nullptr), itemCount(0) {
}

//destrcutor
//deletes any temporary nodes created in order to deallocate memory that was used for those nodes
template<class T>
dLinkedList<T>::~dLinkedList() {
	clear();
}

//copy constructor
//creates a deep copy of a list that is created
template<class T>
dLinkedList<T>::dLinkedList(const dLinkedList<T>& aList) {
	itemCount = aList.itemCount;
	dNode<T>* origChainPtr = aList.headPtr;
	//cheack if list is mepty and if so set head pointer to null
	if (origChainPtr == nullptr) {
		headPtr = nullptr;
	}
	//if list isnt empty create a node for the head pointer and copy all nodes that may follow
	else {
		headPtr = new dNode<T>(origChainPtr->getItem(), origChainPtr->getNext(), origChainPtr->getPrev());
		origChainPtr = origChainPtr->getNext();

		dNode<T>* newChainPtr = headPtr;
		while (origChainPtr != nullptr) {
			dNode<T>* newNodePtr = new dNode<T>(origChainPtr->getItem(), origChainPtr->getNext(), origChainPtr->getPrev());
			newChainPtr->setNext(newNodePtr);

			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr = nullptr;
	}
}

//returns the size of the list by accessing the private data member itemCount and allows the user to access that value
template<class T>
int dLinkedList<T>::getCurrentSize() const {
	return itemCount;
}

//checks to see if the list is empty and returns true if the item count for the list is zero
template<class T>
bool dLinkedList<T>::isEmpty() const {
	return itemCount == 0;
}

//adds a new element to the list and returns true if possible
//first creates a new node and sets the item to be added for the new node
//then sets the next pointer for the new node and allows headpointer to be equal to that
template <class T>
bool dLinkedList<T>::add(const T& newEntry) {
	dNode<T>* newNodePtr = new dNode<T>();
	newNodePtr->setItem(newEntry);
	newNodePtr->setNext(headPtr);
	headPtr = newNodePtr;
	itemCount++;

	return true;
}

//removes a nn entry from the list and returns true if possible
//first checks if the list is empty if not returns false
//if list is not empty sets the item of the node to be deleted and sets thehead pointer to that as well
//then deletes the node and deallocates the memory and decreases the size of the list by one
template<class T>
bool dLinkedList<T>::remove(const T& anEntry) {
	dNode<T>* entryNodePtr = getPointerTo(anEntry);

	if (entryNodePtr == nullptr) {
		return false;
	}
	else {
		entryNodePtr->setItem(headPtr->getItem());
		entryNodePtr = headPtr;
		headPtr = headPtr->getNext();
		delete entryNodePtr;
		entryNodePtr = nullptr;
	}
	itemCount--;
	return true;
}

//clears the entries of the list and is used for the destructor
//while the list still has entries remove each entry one by one and deallocate the memory used
//sets the size to zero once all items have been deleted
template<class T>
void dLinkedList<T>::clear() {
	dNode<T>* nodeToDeletePtr = nullptr;

	while (headPtr != nullptr) {
		nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;

	}

	itemCount = 0;
}

//gets the number of times that an entry appears in the list
//starts at the head and works its way through the whole list and every time the entry being searched for appears increase the counter
//returns the number of value of the counter
template<class T>
int dLinkedList<T>::getFrequencyOf(const T& anEntry) const {
	int frequency = 0;
	int counter = 0;
	dNode<T>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount)) {
		if (anEntry == curPtr->getItem()) {
			frequency++;
		}

		counter++;
			curPtr = curPtr->getNext();
	}
	return frequency;
}

//gets the pointer for a certain target
//if able to find the target set the flag to true and returns the pointer for the target
//keeps going through the list until the target is found
template<class T>
dNode<T>* dLinkedList<T>::getPointerTo(const T& target) const{
	bool found = false;
	dNode<T>* curPtr = headPtr;
	while (!found && (curPtr != nullptr)) {
		if (target == curPtr->getItem()) {
			found = true;
		}
		else {
			curPtr = curPtr->getNext();
		}
	}
	return curPtr;
}

//checks if the list contains a certain value
//returns true if the specified entry has a pointer to a target and is not null
template<class T>
bool dLinkedList<T>::contains(const T& anEntry) const {
	return (getPointerTo(anEntry) != nullptr);
}

//similar to the add method inserst an entry, but at a specified location in the list
//returns true if able to do so
//takes index and antry as paramters and for a specified index adds either to the front, the back, or somehwere in the middle
//for any index at 0 adds to teh front
//for any index greater than the number of items, adds to the back
//for an index in the middle goes through all the nodes in the list and when it hits the index it adds the new pointer at that point
template<class T>
bool dLinkedList<T>::insertAt(const T& newEntry, const int index) {
	dNode<T>* currPtr = headPtr;
	dNode<T>* newNode = new dNode<T>();
	
	newNode->setItem(newEntry);
	if (index == 0) {
		addFront(newEntry);
	}
	else if (index + 1 > itemCount) {
		addBack(newEntry);
	}
	else {
		for (int i = 0; i < index - 1; i++) {
			currPtr = currPtr->getNext();
		}
		newNode->setNext(currPtr->getNext());
		newNode->getNext()->setPrev(newNode);
		currPtr->setNext(newNode);
		newNode->setPrev(currPtr);
		itemCount++;
	}
	return true;
	}

//similar to the remove method deletes an entry, but at a specified location on the list
//returns false if index is out of bounds or the list is empty
//goes through the list until the specified location and removes the entry at that location
template<class T>
bool dLinkedList<T>::removeAt(const int index) {
	if (headPtr == nullptr || index < 0) {
		return false;
	}
	else {
		dNode<T>* currPtr = headPtr;
		for (int i = 0; i < index; i++) {
			currPtr = currPtr->getNext();
		}
		remove(currPtr->getItem());
	}
	return true;
}
//replaces an entry with a user desired entry at a speciifed location
//if you remove at the specified location then insert the new entry at that location
//uses the removeAt and insertAt methods to do so and returns true if possible, false otherwise
template<class T>
bool dLinkedList<T>::replace(const int index, const T& newEntry) {
	if (removeAt(index)) {
		return insertAt(newEntry, index);
		return true;
	}
	else
		return false;
}

//returns the index of a given entry
//goes through all the entries in the list until it finds the entry desired and keeps tack of which element it is with a flag
//returns that flag, which represents where the entry was found
template<class T>
int dLinkedList<T>::getIndex(const T& anEntry) const {
	dNode<T>* currPtr = headPtr;
	int r = 0;

	for (int i = 0; i <= itemCount - 1; i++) {
		if (anEntry == currPtr->getItem()) {
			r = i;
			i = itemCount;
			
		}
		else {
			r = -1;
		}
		currPtr = currPtr->getNext();
	}
	return r;
}

//returns an item at the desired location given by an index
//goes through the list starting at the head until it hits the index and returns what item was at the node for the index
template<class T>
T dLinkedList<T>::getItem(const int index) const {
	dNode<T>* currPtr = headPtr;
	for (int i = 0; i <= itemCount - 1; i++) {
		if (i == index) {
			return currPtr->getItem();
		}
		
		else if (index > (itemCount - 1) || index < 0) {
			std::cout << "Invalid index to getItem()" << std::endl;
			T itemT = T();
			return itemT;
		}
		
		currPtr = currPtr->getNext();
	}
}

//same as add method
//adds a new entry to the list and because the add method was written to add an entry to the front this method does the same
template<class T>
bool dLinkedList<T>::addFront(const T& newEntry) {
	dNode<T>* newNodePtr = new dNode<T>();
	newNodePtr->setItem(newEntry);
	newNodePtr->setNext(headPtr);
	headPtr = newNodePtr;
	itemCount++;

	return true;
}

//adds an entry to the back of the list
//takes anew node and sets the item for the new node as the entry given
//if the list is empty set the tail and head pointers to the new node and set the previous to null
//if not empty it goes through all the entries to the list until it hits the ned and adds theentry there and sets the tail pointer
template<class T>
bool dLinkedList<T>::addBack(const T& newEntry) {
	dNode<T>* newNodePtr = new dNode<T>();
	tailPtr = headPtr;

	newNodePtr->setItem(newEntry);
	newNodePtr->setNext(nullptr);

	if (headPtr == nullptr) {
		newNodePtr->setPrev(nullptr);
		headPtr = newNodePtr;
		tailPtr = newNodePtr;
	}
	else {
		while (tailPtr->getNext() != nullptr) {
			tailPtr = tailPtr->getNext();
		}

		tailPtr->setNext(newNodePtr);

		newNodePtr->setPrev(tailPtr);
		tailPtr = newNodePtr;
	}
	itemCount++;

	return true;
}

//returns the head pointer that is set by the addFront() method
template<class T>
dNode<T>* dLinkedList<T>::getHead() const {
	return headPtr;
}

//returns the tail pointer that is set by the addBack() method
template<class T>
dNode<T>* dLinkedList<T>::getTail() const {
	return tailPtr;
}
