#include "Tape.hpp"

//default constructor for tape class
//intialzes a tape with an index of -1, which also means the size is zero
Tape::Tape() : index(-1) {

}

//paramaterized constructor
//adds the strings from the vector v to a linked list that is initialized as a private data member
//increases the index to represent what cell the strings are added to
Tape::Tape(std::vector<std::string> v) {

	index = -1;
	for (int i = 0; i < v.size(); i++) {
		tape.addBack(v[i]);
		index++;
	}
}

//copy constructor
//creates a deep copy of the tape toCopy
Tape::Tape(const Tape &toCopy) {
	//if the list is empty so is the copy
	tape.clear();
	if (toCopy.isEmpty()) {
		tape.clear();
	}
	//the list that has been previously intialized is copied into by the tape toCopy's list it cell by cell
	else {
		index = -1;
		for (int i = 0; i < toCopy.getSize(); i++) {
			index++;
			tape.addBack(toCopy.tape.getItem(i));
		}
	}
	
}

//deallocates any memory that was created
Tape::~Tape() {
	clear();
}

//returns the size of the list, which correlates to the size of the tape directly
int Tape::getSize() const {
	return tape.getCurrentSize();
}

//returns the index based on the size 
//if it is empty the index is set to negative 1
//if not the current index of the cell is returned
int Tape::getIndex() const {
	if (tape.getCurrentSize() == 0) {
		return -1;
	}
	else {
		return index;
	}
}

//sets the contents of a tape that is directly taken from the conents of an already defined tape
void Tape::setTape(Tape toCopy) {
	//if the tape to be copied is empty so is the copy
	if (toCopy.isEmpty()) {
		tape.clear();
	}
	//if not empty each cell is copied from toCopy into the current tape that is being set
	else {
		for (int i = 0; i < toCopy.getSize(); i++) {
			index++;
			//std::cout << toCopy.getSize() << std::endl;
			tape.add(toCopy.readSymbol());
			toCopy.moveLeft();
		}
	}
	
}

//returns a boolen reflecting if the tape is empty based on size
bool Tape::isEmpty() const {
	return tape.getCurrentSize() == 0;
}

//if the current cell is not the end then increase the index by one to reflect moving to the right
//if at the end return false
bool Tape::moveRight() {
	if (getIndex() < tape.getCurrentSize() - 1) {
		index++;
		return true;
	}
	else {
		return false;
	}
}

//if the current cell is not the beginning of the tape decrease the index by one to reflect moving left
//if at the beginning of te tape retirn false
bool Tape::moveLeft() {
	if (getIndex() > 0) {
		index--;
		return true;
	}
	else {
		return false;
	}
}

//if the tape is not empty writes a blank string to the current cell denoted by the index
//uses the dlinkedlist method replace to place an entry at the given index
//if empty return false
bool Tape::writeBlank() {
	if (index != -1) {
		tape.replace(index, " ");
		return true;
	}
	else {
		return false;
	}
}

//writes a symbol(string) given by s to the current cell denoted by the index
//uses the dlinkedlist method replace to place an entry at the given index
//if empty returns false
bool Tape::writeSymbol(std::string s) {
	if (index != -1) {
		tape.replace(index, s);
		return true;
	}
}

//reads the current cell off the tape
//does so by using the dlinkedlists method getItem, which takes an item given by an index
//if empty returns an empty string, if not returns the string in the current cell
std::string Tape::readSymbol() const {
	if (index != -1) {
		return tape.getItem(index);
	}
	else {
		std::string m = {};
		return m;
	}
}

//clears a tape and sets it so its empty
//uses the dlinkedlists method clear to clear the list that represents the tape
void Tape::clear() {
	tape.clear();
	size = 0;
	index = -1;
}

//prints the contents of the tape by printing the list that represents the tape
void Tape::printTape() const {
	tape.printList();
}

//brings the head to the first cell also denoted by the index 0
void Tape::rewind() {
	if (index != -1) {
		index = 0;
	}
}