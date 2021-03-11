#include "Deque.hpp"


//Default constructor
//Creates an empty deque capable of holding 64 items consisting of any type of the users choice
//dynamically allocates an array to implement the deque
template<typename T>
Deque<T>::Deque() {
	N = 64;

	deque = new T[N];
}

//copy constructor
//creates a deep copy of the object that is passed to the constructor and copies the necessary parameters for a deque
//copies the parameters of the deque that exists already and passes them to the deque to be created
//utilizes the standard function that copies the contents of an array to the object to be created
template<typename T>
Deque<T>::Deque(const Deque<T>& x) {
	N = x.N;
	F = x.F;
	B = x.B;
	deque = N ? new T[N] : nullptr;
	std::copy(x.deque, x.deque + x.N, deque);
}

//copy assignment operator
//creates a deep copy of the object that is passed through the method and copies the necessary parameters
//to create a new deque object, utilizes the helper method swap that is instantiated below
//because it is pass by value there is no need to use the copy constructor
template<typename T>
Deque<T>& Deque<T>::operator=(Deque x) {
	swap(*this, x);

	return *this;
}

//swap method that acts as a helper method for the copy assignment operator
//utilizes the standard library function swap that swaps the contents from one object to the other
//and allows for the copy assignment operator to swap the contents of an already existing object and the copy
template<typename T>
void Deque<T>::swap(Deque<T>& x, Deque<T>& y) {
	std::swap(x.deque, y.deque);
	std::swap(x.F, y.F);
	std::swap(x.B, y.B);
	std::swap(x.N, y.N);
}

//destructor
//deallocates any memory that is allocated to create an object
//delets the object that was allocated earlier and sets it to null and allows the avoidance of memory leaks
template<typename T>
Deque<T>::~Deque() {
	delete[] deque;
	deque = nullptr;
}

//method that returns a boolean that relates if the deque that is instantiated is empty or not
//returns true if the front index of the array is equal to negative one denoting an empty deque, false otherwise
template<typename T>
bool Deque<T>::isEmpty() const noexcept {
	return (F == -1);
}

//adds an entry denoted by the paramter item to the front of the deque
//if the deque is full then the array must grow in order to allow more items to be added
//because it is a circular array implementation the fronty index needs to be denoted by different things
//if the deque is intially empty then the new index for the front should be zero
//if the index is zero then the index should wrap around the back of the array denoted by N -1
//if the index is anywhere else the index for the front should be decremented by one
template<typename T>
void Deque<T>::pushFront(const T & item) {
	
	if ((B + 1) % N == F)
	{
		T * oldArray = new T[2 * N];
		//deque = new T[2 * N];

		if (B <= F) {
			for (int i = B; i < F; i++) {
				oldArray[i] = deque[i];
			}
		}
		else {
			for (int i = B; i < N; i++) {
				oldArray[i] = deque[i];
			}
			for (int j = 0; j < B; j++) {
				oldArray[j + N] = deque[j];
			}
			B += N;
		}

		delete[] deque;
		deque = oldArray;
		N = 2 * N;
	}

	if (F == -1) {
		F = 0;
		B = 0;
	}
	else {
		if (F == 0) {
			F = N - 1;
		}
		else {
			F = F - 1;
		}
	}
	deque[F] = item;
}

//removes the entry at the front by getting rid of the current index for the front
//if the deque is empty it throws an exception because you cannot remove something from nothing
//if the front and back index are equla it menas there is only one item in the deque and the indexes should be negative one to denote an
//empty deque, else if the front is at the back of the deque then the new index should be zero, otherwise the index should be incremented by one
template<typename T>
void Deque<T>::popFront() {
	if (isEmpty()) {
		throw std::range_error("Queue is empty");
	}
	else {
		if (F == B) {
			F = -1;
			B = -1;
		}
		else {
			if (F == N - 1) {
				F = 0;
			}
			else {
				F = F + 1;
			}
		}
		//F = (F + 1) % (N + 1);
	}
}

//this method returns the item at the front of the deque
//throws an exception if the deque is empty because there is nothing to return
//else returnsthe item denoted by the front index
template<typename T>
T Deque<T>::front() const {
	if (isEmpty())
		throw std::range_error("Queue is empty");
	else
		return deque[F];
}

//adds an entry denoted by the parameter item to the back of the deque and uses the back index to do so
//if the deque is full then it needs to grow by double its size to allow for more entries
//if the deque is empty then the front and back indices should be the same and should be zero
//if the index is at the back of the deque then the new index should be zero and other than that the index should be incremented by one
//then the item is placed and denoted by the index B, representing the back index
template<typename T>
void Deque<T>::pushBack(const T & item) {
	if ((B + 1) % N == F)
	{
		T * oldArray = deque;
		deque = new T[2 * N];

		for (int i = 0; i < N; i++) {
			deque[i] = oldArray[i];
		}

		delete[] oldArray;
		N = 2 * N;
	}

	if (F == -1) {
		F = 0;
		B = 0;
	}
	else {
		if (B == N - 1) {
			B = 0;
		}
		else {
			B = B + 1;
		}
	}
	//B = (B + 1) % (N + 1);
	deque[B] = item;
}

//removes the item at the back of the deque, if not empty, if empty throw an exception
//if not empty use the back index to get rid of the item at the back, if the list has one item then the deque should become empty
//upon removing an item, denoted by the index negative one, if the ack is located at the index zero then the new index should wrap around the deque, denoted by N -1
//otherwise decrement the back index by one
template<typename T>
void Deque<T>::popBack() {
	if (isEmpty()) {
		throw std::range_error("Queue is empty");
	}
	else {
		if (F == B) {
			F = -1;
			B = -1;
		}
		else {
			if (B == 0) {
				B = N - 1;
			}
			else {
				B = B - 1;
			}
		}
		//B = (B + 1) % (N + 1);
	}
}

//returns the item at the back of the deque denoted by the back index, B
//if the deque is empty there is no item to return so it should throw an exception
//otherwise return the item on the deque at position B
template<typename T>
T Deque<T>::back() const {
	if (isEmpty()) {
		throw std::range_error("Queue is empty");
	}
	else{
		return deque[B];
	}
}