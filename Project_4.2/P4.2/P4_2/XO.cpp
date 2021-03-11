#include "XO.hpp"

//default constructor
//creates a blank game so that moves can be made on the board
//this means that no positions are occupied and no moves have been made yet
//sets the appropiate fields, state and numMoves to all zeroes
XO::XO() {
	for (int i = 0; i < 9; i++)
		b.state[i] = 0;
	b.numMoves = 0;
}

//parameterized constructor
//sets up a game based on user inputted moves
//makes moves on a board based on the user inputted parameters play, pos, and n
//sets the board's variables to represent a given game by setting the variables states, moves, turns, and numMoves
//throws a logic error for any invalid moves
XO::XO(const int8_t* play, const uint8_t* pos, const uint8_t& n) {
	
	if (n <= 9 ) {
		b.numMoves = n;
		for (int i = 0; i < b.numMoves; i++) {
			if (b.state[pos[i]] == 0 && pos[i] < 9) {
				b.turn[i] = play[i];
				b.moves[i] = pos[i];
				b.state[b.moves[i]] = b.turn[i];
			}
			else {
				throw std::logic_error("invalid move");
			}
		}
	}
	else {
		throw std::logic_error("invalid move");
	}

	
}

//prints the board's contents to the console using the standard library out function 
//utilizes the overloaded operator<<
void XO::show() {
	std::cout << b;
}

//method to make a move that the user desires to make
//makes a move based on the parameters play and pos that are passed by the user
//updates the proper variables based on the state of the users move: state, moves, turn, and numMoves
//returns true for valid moves and false for invalid moves
bool XO::makeMove(const int8_t& play, const uint8_t& pos) {
	
	if (b.numMoves <= 9 && b.state[pos] == 0 && pos < 9) {
		b.moves[b.numMoves] = pos;
		b.turn[b.numMoves] = play;
		b.state[pos] = play;
		b.numMoves += 1;
		
		return true;
	}
	else {
		return false;
	}
}


//makes a set of moves similar to the parameterized based on the users input to the function call
//based on the user inputs for play, pos, and n it updates the proper variables that represent the game
//updates the variables moves, turns, state, and numMoves
//returns true for valid moves and false for invalid moves
bool XO::makeMoves(const int8_t* play, const uint8_t* pos, const uint8_t& n) {
	bool flag;
	if (n <= 9) {
		b.numMoves = n;
		for (int i = 0; i < b.numMoves; i++) {
			
			if (b.state[pos[i]] == 0 && pos[i] < 9) {
				b.turn[i] = play[i];
				b.moves[i] = pos[i];
				b.state[b.moves[i]] = b.turn[i];
				flag = true;
			}
			else {
				flag = false;
			}
		}
	}
	else {
		flag = false;
	}

	/*
	for (int i = 0; i < 9; i++) {
		int y = (int)b.state[i];
		std::cout << y << std::endl;
	}
	*/
	return flag;
}

//method that determines and make the most optimal move according to the algorirthm and the given board's state
//uses a breadth first search technique to gather a game tree that represents all the possible moves for a given state of the game
//based on the game tree uses a minimax strategy to minimize opponent's score and maximize user's score
//the game's states are updated to represent the moves and the state of the game for the variables moves, turn, state, and numMoves
bool XO::makeOptimalMove() {
	
	Deque<BoardXO> q;

	q.pushBack(b);
	visited.push_back(b);
	b.id = 0;
	used[b.id] = 0;

	while (!q.isEmpty()) {
		BoardXO node = q.front();
		q.popFront();

		if (gameOver(node)) {
		//	b = node;
			if (winner(node) == -1) {
				score = 10 - node.numMoves;
			}
			else if (winner(node) == 1) {
				score = node.numMoves - 10;
			}
			return true;
		}
		else {
			for (int i = 0; i < 9; i++) {
				//if(node is not visited)
				if (node.state[i] == 0) {
					std::cout << i << std::endl;
					makeMove(-node.turn[node.numMoves], i, node);
					q.pushBack(node);
					visited.push_back(node);
					undoMove(node.turn[node.numMoves], i, node);
				}

			}
		}
	}


	
	
	if (b.numMoves <= 9) {
	b.numMoves++;
}
	return true;

}

//returns the private variable b, that represents theb board that is being played
//good for debugging and access to the private variab;e b
BoardXO XO::getBoard() {
	return b;
}

//method that returns whether the game is in a state of draw or win/loss
//if the max number of moves is made and there is no winner the game is a draw and returns true
//if someone has won the T3 game returns true for the winner either -1 or 1 for three in a row on the board
bool XO::gameOver() {
	bool gameState;

	if (winner() == -1 || winner() == 1) {
		gameState = true;
	}
	else if (b.numMoves == 9) {
		gameState = true;
	}
	else {
		gameState = false;
	}
	return gameState;
}

//returns who won the game or if it ended in a draw
//for T3 if a player has three ina row at any point there is a winner and that winner is returned either 1 or -1
//if there is no winner and the max number of moves has been made the game ends ina draw and returns 0
int8_t XO::winner() {
	if (b.state[0] == -1 && b.state[1] == -1 && b.state[2] == -1) {
		return -1;
	}
	else if (b.state[3] == -1 && b.state[4] == -1 && b.state[5] == -1) {
		return -1;
	}
	else if (b.state[6] == -1 && b.state[7] == -1 && b.state[8] == -1) {
		return -1;
	}
	else if (b.state[0] == -1 && b.state[3] == -1 && b.state[6] == -1) {
		return -1;
	}
	else if (b.state[1] == -1 && b.state[4] == -1 && b.state[7] == -1) {
		return -1;
	}
	else if (b.state[2] == -1 && b.state[5] == -1 && b.state[8] == -1) {
		return -1;
	}
	else if (b.state[0] == -1 && b.state[4] == -1 && b.state[8] == -1) {
		return -1;
	}
	else if (b.state[2] == -1 && b.state[4] == -1 && b.state[6] == -1) {
		return -1;
	}
	else if (b.state[0] == 1 && b.state[1] == 1 && b.state[2] == 1) {
		return 1;
	}
	else if (b.state[3] == 1 && b.state[4] == 1 && b.state[5] == 1) {
		return 1;
	}
	else if (b.state[6] == 1 && b.state[7] == 1 && b.state[8] == 1) {
		return 1;
	}
	else if (b.state[0] == 1 && b.state[3] == 1 && b.state[6] == 1) {
		return 1;
	}
	else if (b.state[1] == 1 && b.state[4] == 1 && b.state[7] == 1) {
		return 1;
	}
	else if (b.state[2] == 1 && b.state[5] == 1 && b.state[8] == 1) {
		return 1;
	}
	else if (b.state[0] == 1 && b.state[4] == 1 && b.state[8] == 1) {
		return 1;
	}
	else if (b.state[2] == 1 && b.state[4] == 1 && b.state[6] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

//helper method for the makeOPtimalMoves method that allows a board to be passed through and retruns if the state of the game is over
bool XO::gameOver(const BoardXO& brd) {
	bool gameState;

	if (winner(brd) == -1 || winner(brd) == 1) {
		gameState = true;
	}
	else if (brd.numMoves == 9) {
		gameState = true;
	}
	else {
		gameState = false;
	}
	return gameState;
}

//helper method for makeOptimalMoves and allows a board object to be passed and returns whether someone on the baord has won or not
int8_t XO::winner(const BoardXO& brd) {
	if (brd.state[0] == -1 && brd.state[1] == -1 && brd.state[2] == -1) {
		return -1;
	}
	else if (brd.state[3] == -1 && brd.state[4] == -1 && brd.state[5] == -1) {
		return -1;
	}
	else if (brd.state[6] == -1 && brd.state[7] == -1 && brd.state[8] == -1) {
		return -1;
	}
	else if (brd.state[0] == -1 && brd.state[3] == -1 && brd.state[6] == -1) {
		return -1;
	}
	else if (brd.state[1] == -1 && brd.state[4] == -1 && brd.state[7] == -1) {
		return -1;
	}
	else if (brd.state[2] == -1 && brd.state[5] == -1 && brd.state[8] == -1) {
		return -1;
	}
	else if (brd.state[0] == -1 && brd.state[4] == -1 && brd.state[8] == -1) {
		return -1;
	}
	else if (brd.state[2] == -1 && brd.state[4] == -1 && brd.state[6] == -1) {
		return -1;
	}
	else if (brd.state[0] == 1 && brd.state[1] == 1 && brd.state[2] == 1) {
		return 1;
	}
	else if (brd.state[3] == 1 && brd.state[4] == 1 && brd.state[5] == 1) {
		return 1;
	}
	else if (brd.state[6] == 1 && brd.state[7] == 1 && brd.state[8] == 1) {
		return 1;
	}
	else if (brd.state[0] == 1 && brd.state[3] == 1 && brd.state[6] == 1) {
		return 1;
	}
	else if (brd.state[1] == 1 && brd.state[4] == 1 && brd.state[7] == 1) {
		return 1;
	}
	else if (brd.state[2] == 1 && brd.state[5] == 1 && brd.state[8] == 1) {
		return 1;
	}
	else if (brd.state[0] == 1 && brd.state[4] == 1 && brd.state[8] == 1) {
		return 1;
	}
	else if (brd.state[2] == 1 && brd.state[4] == 1 && brd.state[6] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

//helper method for optimal moves that allows a board to be passed through as a paramter and a move is made just for that specific baord
//works the same as the the other makeMove method just this is for a specific board that is passed through
void XO::makeMove(const int8_t& play, const uint8_t& pos, BoardXO& brd) {
	if (brd.numMoves <= 9 && brd.state[pos] == 0 && pos < 9) {
		brd.moves[brd.numMoves] = pos;
		brd.turn[brd.numMoves] = play;
		brd.state[pos] = play;
		brd.numMoves += 1;
	}
	
}

//helper method for optimal move and works as a way to reset the move that was just made in order to get all possible moves for a current state
void XO::undoMove(const int8_t& play, const uint8_t& pos, BoardXO& brd) {
	brd.numMoves -= 1;
	brd.moves[brd.numMoves] = 0;
	brd.turn[brd.numMoves] = 10;
	brd.state[pos] = 0;
}