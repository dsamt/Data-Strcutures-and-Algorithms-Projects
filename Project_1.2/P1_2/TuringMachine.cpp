#include "TuringMachine.hpp"

//Code away

//default constructor
//sets the parameters for an empty turing machine meaning an empty tape and no symbols
TuringMachine::TuringMachine() : t(), symbols(0) {

}

//paramerterized constructor
//sets the paramters for the turing machine including a tape and symbols that will be included on the tape
//allows user to define a turing machine tat is not default and has contents
TuringMachine::TuringMachine(Tape toCopy, const std::vector<std::string>& p) : t(toCopy), symbols(p) {

}

//destructor that destroys any memory that was allocated
TuringMachine::~TuringMachine() {
	t.clear();
}

//allows access to the pruvate data member symbols that represents the strings taht are included on the tape
std::vector<std::string> TuringMachine::getSymbols() const {
	return symbols;
}

//returns the tape that has been defined as a private data member
//allows access to this data and allows to see the tape that is defined
Tape TuringMachine::getTape() {
	return t;
}

//sets the symbols to be put into the tape
//uses the paramertized constructor to create a tape based on the given symbols p
//returnns true if the tape can be creates and false otherwise
bool TuringMachine::setSymbols(std::vector<std::string> p) {
	if (t.isEmpty()) {
		return false;
	}
	else {
		Tape(p);
		return true;
	}
}

//uses the tape's method to set the contenst of a tape to be used by the turing machine
//based on the given tape toCopy sets the tape by copying its content into a new tape
bool TuringMachine::setTape(Tape& toCopy) {
	if (t.isEmpty()) {
		return false;
	}
	else {
		t.setTape(toCopy);
		return true;
	}

}

//checks if the setup for pattern mathcing matches the basic legal symbols
//must be three legal symbols and must match the rules
//returns true if the setup is right and false otherwise
bool TuringMachine::setupCheck() {
	bool flag = false;
	//checks the size to make sure there are only three legal symbols
	if (t.getSize() == 3) {
		flag = true;
	}
	else {
		flag = false;
	}
	//gives the legal symbols to check against
	std::vector<std::string> sym = { "a", "b", "c" };
	if (symbols == sym) {
		flag = true;
	}
	else {
		flag = false;
	}

	return flag;
}

//resets the machine to an empty machine with empty tape and no symbols
void TuringMachine::reset() {
	TuringMachine();
}

//returns whether a group of symbols matches the legal patterns given
//uses an FSM to denote which state the machine is in(where and what the head is reading)
//if the pattern matches return true if not return false
//states are based on legal symbols and patterns and moves through the state machine accordingly
//does not take into account all of the legal paterns and rules(ran out of time)
bool TuringMachine::patternMatch() {
	t.rewind();
	
		typedef enum {
			a_state, b_state, c_state, blank_state,
		} state;

		state NextState;
		if (t.readSymbol() == "a") {
			NextState = a_state;
		}
		else {
			return false;
		}
		switch (NextState) {
			//case for the tape starting with an a and moves to other states according to legal patterns
		case a_state: {
			t.moveRight();
			if (t.readSymbol() == "a") {
				NextState = a_state;
			}
			else if (t.readSymbol() == "b") {
				NextState = b_state;
			}
			else {
				return false;
			}
		}
		break;
		//case for when there is a b aftern an a
		case b_state: {
			t.moveRight();
			if (t.readSymbol() == "b"){
				NextState = b_state;
			}
			else if (t.readSymbol() == "c") {
				NextState = c_state;
			}
			else {
				return false;
			}
		}
		break;
		//case for a c when after a b
		case c_state: {
			t.moveRight();
			if (t.readSymbol() == "c"){
				NextState = c_state;
			}
			else {
				return false;
			}
		}
		break;
	deault:
		break;
		}


	return true;
}