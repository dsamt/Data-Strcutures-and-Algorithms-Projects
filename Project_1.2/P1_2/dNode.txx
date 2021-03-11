#include "dNode.hpp"

template<class T>
void dNode<T>::printNode() const
{
    std::cout << "Current Node: " << item << std::endl;

    if(next != nullptr)
    {
        std::cout << "Next Node: " << next->getItem() << std::endl;
    }
    else
    {
        std::cout << "Next Node: NULL " << std::endl;
    }

    if(prev != nullptr)
    {
        std::cout << "Next Node: " << prev->getItem() << std::endl;
    }
    else
    {
        std::cout << "Next Node: NULL " << std::endl;
    }
}
//default constrcutor for node class
//creates a default node, which contains an item and a null pointer
template<class T>
dNode<T>::dNode() : next(nullptr) {

}

//paramterized constructor for node class
//creates a node with an item and a pointer, the pointer has a next and previous parameters
template<class T>
dNode<T>::dNode(const T& anItem) : item(anItem), next(nullptr), prev(nullptr) {

}

//paramterized constructor for node class
//creates a node with an item and intializes the parameters for the next and previous pointers
template<class T>
dNode<T>::dNode(const T& anItem, dNode<T>* nextNodePtr, dNode<T>* prevNodePtr) : item(anItem), next(nextNodePtr), prev(prevNodePtr) {

}

//method that sets the item for a given node and does not return anything just intializes an item for a node
template<class T>
void dNode<T>::setItem(const T& anItem) {
	item = anItem;
}

//sets the pointer to the next item for the current node
template<class T>
void dNode<T>::setNext(dNode<T>* nextNodePtr) {
	next = nextNodePtr;
}

//sets the pointer to the previous item for the current node 
template<class T>
void dNode<T>::setPrev(dNode<T>* prevNodePtr) {
	prev = prevNodePtr;
}

//method to access the private data member item and allows the user to return that value
template<class T>
T dNode<T>::getItem() const {
	return item;
}

//method to access the private data member next and allows the user to return that value

template<class T>
dNode<T>* dNode<T>::getNext() const {
	return next;
}

//method to access the private data member prev and allows the user to return that value
template<class T>
dNode<T>* dNode<T>::getPrev() const {
	return prev;
}