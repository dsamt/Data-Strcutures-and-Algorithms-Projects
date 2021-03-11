//
//  dNode.hpp
//
//
//  Created by Tam Chantem on 9/8/20.
//

#ifndef NODE_
#define NODE_

template<class T>

class dNode
{
public:
    dNode();
    dNode(const T& anItem);
    dNode(const T& anItem, dNode<T>* nextNodePtr, dNode<T>* prevNodePtr);
    void setItem(const T& anItem);
    void setNext(dNode<T>* nextNodePtr);
    void setPrev(dNode<T>* prevNodePtr);
    T getItem() const ;
    dNode<T>* getNext() const ;
    dNode<T>* getPrev() const ;
    void printNode() const;
    
private:
    T item;             // A data item
    dNode<T>* next;  // Pointer to next node
    dNode<T>* prev;  // Pointer to previous node

};

#include "dNode.txx"
#endif
