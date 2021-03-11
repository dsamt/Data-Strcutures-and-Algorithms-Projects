#ifndef BOARDXO_HPP
#define BOARDXO_HPP

#include <iostream>
#include <string>
#include "Deque.hpp"

// A board struct for the game tic-tac-toe
struct BoardXO
{
  int8_t state[9]; //where player markers are on the board (player can be -1 or 1; 0 for unoccupied)
  uint8_t moves[9];  //sequence of moves that led to current game state (i.e., which marker position players selected)
  int8_t turn[9]; //which player made the corresponding move
  uint8_t numMoves; //total number of moves that have been made in the game to this point
  uint32_t id; //a key (unique number) that one can assign to, and use to refer to, this particular board

  /* default constructor  
     @return a blank board (all positions unoccupied; i.e., 0 and numMoves = 0)*/
  BoardXO()
  {
	
	  for (int i = 0; i < 9; i++)
		  state[i] = 0;
	
	  numMoves = 0;
  }
    
  /* return marker for requested position
     @return the marker at the given position (-1, 0, 1) throw std::range_error is subscript is out of bounds*/
  const int8_t& operator[](std::uint8_t idx) const
  {
	  if (idx >= 9) {
		  throw std::range_error("Subscript is out of range");
	}
	  else {
		  return state[idx];
	  }
  }

  //prints out the board for a given game
  //uses the overloaded operator<< send the contents of the game board to the output stream
  //so that the game board can be printed to standard output console, good for debugging and visualizing a given game
  friend std::ostream& operator<<(std::ostream& os, const BoardXO& brd)
  {
	  unsigned char XO;
	  for (int i = 0; i < 7; i+=3) {
		  for (int j = 0; j < 3; j++) {
			  if (brd.state[j+i] == -1) {
				  XO = 'X';
			  }
			  else if (brd.state[j+i] == 0) {
				  XO = ' ';
			  }
			  else if (brd.state[j+i] == 1) {
				  XO = 'O';
			  }
			  os << XO;
		  }
		  os << std::endl;
	  }
	  return os;
  }
};

#endif
