capac#include "Stack.hpp"
#include <iostream>

//default constructor
//creates an empty stack with a max capacity fo 100 entries
//the top index is set to negative 1 so it is out of the stack
//top is unsigned, but in this case for the program it works with implicity
template<class T>
Stack<T>::Stack() : capacity(100), top(-1), items(new T[capacity]) {

}

//destructor
//destroys any new memory that has been allocated
template<class T>
Stack<T>::~Stack() {
	delete[] items;
}

//copy constructor
//sets the cpacity for the new stack as the capacity from the original stack
//sets the top of the stack to negative one
//goes through all items of the originial (rhs) stack and copies the, into the new stack
//increments top by one for each items of the stack
template<class T>
Stack<T>::Stack(const Stack& rhs){
	
	capacity = rhs.capacity;
	items = new T[capacity];
	top = -1;
	for (int i = 0; i < rhs.size(); i++) {
		items[i] = rhs.items[i];
		top++;
	}
}

//returns the size of the stack
//top is the index of the stack and as it grows top is incremented by one
//because the indexing for top starts at negative one the size is top plus one
template<class T>
size_t Stack<T>::size() const {
	return top + 1;
}

//returns if the stack is empty or not
//because in the default constructor top is set to negative one for an empty stack
//if the top index is equal to one then it returns true that the stack is empty
template<class T>
bool Stack<T>::isEmpty() const {
	return top == -1;
}

//pushes an new item on to the stack
//if the stack is at capacity create a new stack with double the capacity
template<class T>
bool Stack<T>::push(const T& newItem) {
	//if the stack is at capacity increase the capacity
	if ((top + 1) >= capacity) {
		//get address of old stack
		T* oldItems = items;
		//sets pointer for new stack
		items = new T[2 * capacity];
		//copies each item from the old stack to the new one
		for (int i = 0; i < capacity; i++) {
			items[i] = oldItems[i];
		}
		//deallocates the old stack
			delete[] oldItems;
			//resizes the capacity
			capacity = 2 * capacity;
	}
	//increments the stack size and index(top) and sets the item at the index to newItem
	items[++top] = newItem;
	return true;
}

//pops the top item off the top of the stack
//as long as the stack is not empty decrement the index, which gets rid of the last item to be entered to the stack
template<class T>
bool Stack<T>::pop() {
	if (!isEmpty()) {
		items[top--];
		return true;
	}
	else {
		return false;
	}
}

//returns the last item(top of stack) to be entered to the stack
//if the stack is not empty then return the item at the index top(last item to be pushed)
//if the bag is empty it throws an exception that the stack is out of range and there is nothing that can be peeked at
template<class T>
const T& Stack<T>::peek() const throw(std::range_error) {
	if (!isEmpty()) {
		return items[top];
	}
	else {
		try {
			throw std::range_error("Stack is out of range");
		}
			catch (const std::out_of_range& oor){
				std::cout << "Out of Range error: " << oor.what() << '\n';
			}
	}
}

//clears the stack and creates a new empty stack
//sets items to a new empty stack and sets the top to negative for index of an empty stack
template<class T>
void Stack<T>::clear() {
	items = new T[0];
	top = -1;
}