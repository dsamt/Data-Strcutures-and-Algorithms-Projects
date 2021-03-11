#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "abstract_deque.hpp"

template <typename T>
class Deque : public AbstractDeque<T>
{
public:
	//Default constructor
	Deque();

	//Copy constructor
	Deque(const Deque<T>& x);

	//Copy assignment operator
	Deque<T>& operator=(Deque x);

	//Destructor
	virtual ~Deque();

	/** Returns true if the deque is empty, else false
	*/
	bool isEmpty() const noexcept;

	/** Add item to the front of the deque
  * may throw std::bad_alloc
  */
	void pushFront(const T & item);

	/** Remove the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
	void popFront();

	/** Returns the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
	T front() const;

	/** Add item to the back of the deque
   * may throw std::bad_alloc
   */
	void pushBack(const T & item);

	/** Remove the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
	void popBack();

	/** Returns the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
	T back() const;

private:
	//index for the front if the deque intially set to negative one for an empty deque
	int F = -1;
	//index for the front if the deque intially set to negative one for an empty deque
	unsigned int B = 0;
	//variable used to set the size of the array initially set to 64 in default constructor
	unsigned int N;
	//class object that instantiates a deque of type T using a circular array
	T * deque;
	//helper method for the copy assignment operator and is used to swap parameters of two different objects
	void swap(Deque<T>& x, Deque<T>& y);
};

#include "Deque.txx"
#endif
