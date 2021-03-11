#include "lodepng.h"
#include "Maze.hpp"
#include "Stack.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <random>

//method that is able to read in a file containing a unsolved or solved maze and convert it into ascii representation
bool Maze::read(std::string filename)
{
  bool flag = false;
  std::vector<std::uint8_t> pixels = std::vector<std::uint8_t>(4*cols*rows);
  unsigned int w, h;
  
  //read png
  if(filename.empty())
    flag = lodepng::decode(pixels, w, h, "maze.png");
  else
    flag = lodepng::decode(pixels, w, h, filename);

  return false;
}

//takes ascii represented mazes produced and converts into a visual png for non-coders to understand
bool Maze::write(std::string filename) const
{
  bool flag = false;

  std::vector<std::uint8_t> pixels = std::vector<std::uint8_t>(4*cols*rows,255); //RGBA values for each pixel in image

  for (int i = 0; i < rows*cols; i++) {
	  if (maze[i] == ' ') {
		  pixels[(i * 4)] = 255;
		  pixels[(i * 4) + 1] = 255;
		  pixels[(i * 4) + 2] = 255;
		  pixels[(i * 4) + 3] = 255;
	  }
	  else if (maze[i] == '#') {
		  pixels[(i * 4)] = 0;
		  pixels[(i * 4) + 1] = 0;
		  pixels[(i * 4) + 2] = 0;
		  pixels[(i * 4) + 3] = 255;
	  }
	  else if (maze[i] == 'B') {
		  pixels[(i * 4)] = 0;
		  pixels[(i * 4) + 1] = 128;
		  pixels[(i * 4) + 2] = 0;
		  pixels[(i * 4) + 3] = 255;
	  }
	  else if (maze[i] == 'E') {
		  pixels[(i * 4)] = 255;
		  pixels[(i * 4) + 1] = 0;
		  pixels[(i * 4) + 2] = 0;
		  pixels[(i * 4) + 3] = 255;
	  }
	  else if (maze[i] == '*') {
		  pixels[(i * 4)] = 0;
		  pixels[(i * 4) + 1] = 0;
		  pixels[(i * 4) + 2] = 255;
		  pixels[(i * 4) + 3] = 255;
	  }
  }


  //write png
  if(filename.empty())
    flag = lodepng::encode("maze.png", pixels, cols, rows);
  else
    flag = lodepng::encode(filename, pixels, cols, rows);
  
  return !flag;
}

std::ostream& operator<<(std::ostream& os, const Maze& m)
{
  for(int i = 0; i < m.rows*m.cols; i++)
    {
      if(i % m.cols == 0)
	os  << std::endl;
      
      os << m.maze[i];
    }

  os  << std::endl << std::endl;
  
  return os;
}

//default constructor
//initializes an empty maze with size zero and nothing in the maze
Maze::Maze() : rows(0), cols(0), maze(rows*cols) {
	
}

//paramaterized constructor
//initializes a maze based on user input based on number of rows and columns as well as where to start and end
//starts by creating a maze full of walls denoted by '#' and continues by gathering neighbors froma seed point
//and knocking walls down in between the seed or its neighbor at random and then marks the neighbor as visited
// from there neighbors of neighbors are found at random and walls are knocked down until all the neighbors are marked as visited nd no walls
//are between them, throws and exception for when there is no valid maze and continues until one os generated
Maze::Maze(std::size_t rows, std::size_t cols, std::size_t begin, std::size_t end) throw(std::invalid_argument) {

	if ((rows >= 1 && cols >= 2) || (rows >= 2 && cols >= 1) || (begin != end)) {
		this->cols = cols;
		this->rows = rows;
		maze.reserve(rows*cols);
		Stack<unsigned char> stack;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				maze.push_back(j + (i*cols));

				if ((j + (i * cols)) == begin) {
					maze[j + (i * cols)] = 'B';
				}
				else if ((j + (i * cols)) == end) {
					maze[j + (i * cols)] = 'E';
				}
				else {
					maze[j + (i * cols)] = '#';
				}
			}
		}
		unsigned char seed = maze[0];

		if (seed == 'B') {
			maze[0] = 'B';
		}
		else if (seed == 'E') {
			maze[0] = 'E';
		}
		else {
			maze[0] = ' ';
		}
		int index;
		while (stack.isEmpty()) {
			int ind = rand() % 2;
			//std::cout << ind << std::endl;
			if (getNeighbors(0)[ind] < rows*cols) {
				int wall = getWall(0, getNeighbors(0)[ind]);
				if (maze[wall] == 'B') {
					maze[wall] = 'B';
				}
				else if (maze[wall] == 'E') {
					maze[wall] = 'E';
				}
				else {
					maze[wall] = ' ';
				}
				if (maze[getNeighbors(0)[ind]] == 'B') {
					maze[getNeighbors(0)[ind]] = 'B';
				}
				else if (maze[getNeighbors(0)[ind]] == 'E') {
					maze[getNeighbors(0)[ind]] = 'E';
				}
				else {
					maze[getNeighbors(0)[ind]] = ' ';
				}
				stack.push(seed);
				index = getNeighbors(0)[ind];
			}
		}
		unsigned char cell;
		while (!stack.isEmpty()) {
			cell = stack.pop();
			//int ind = rand() % 4;
			std::vector<std::size_t> unv;
			for (int ind = 0; ind < 4; ind++) {
				if (getNeighbors(index)[ind] < rows*cols) {
					unv.push_back(getNeighbors(index)[ind]);
					//std::cout << getNeighbors(index)[ind] << std::endl;
				}
			}

			if (unv.size() != 0) {
			}


			std::random_device rd;
			std::mt19937 g(rd());
			std::shuffle(unv.begin(), unv.end(), g);
			int wall;
			wall = getWall(index, unv[0]);
			std::cout << "wall: " << getWall(index, unv[0]) << std::endl;
			if (maze[unv[0]] != ' ') {
				stack.push(cell);
				if (maze[unv[0]] == 'B') {
					maze[unv[0]] = 'B';
					stack.push(maze[unv[0]]);
				}
				else if (maze[unv[0]] == 'E') {
					maze[unv[0]] = 'E';
					stack.push(maze[unv[0]]);
				}
				else {
					maze[unv[0]] = ' ';
					stack.push(maze[unv[0]]);
				}
				if (maze[wall] == 'B') {
					maze[wall] = 'B';
				}
				else if (maze[wall] == 'E') {
					maze[wall] = 'E';
				}
				else {
					maze[wall] = ' ';
				}
			}
			std::cout << unv[0] << std::endl;
			index = unv[0];
		}
	}

	else {
	try{
		
		if ((rows < 1 && cols < 2) || (rows < 2 && cols < 1)) {
			throw std::invalid_argument("Invalid Maze");
		}
	}
		catch (const std::invalid_argument& ia) {
		std::cout << "Invalid Argument: " << ia.what() << '\n';
		//abort();
	}
}
}


//sets the private data members rows and maze so that a maze can be set 
//validates that the maze to be set is valid and sets the data member rows
//not fully completed(does set variables but does not check for validity)
bool Maze::set(const std::vector<unsigned char>& maze, std::size_t rows) {
	this->rows = rows;
	this->maze = maze;

	int start, end;
	for (int i = 0; i < rows*cols; i++) {
		if (maze[i] == 'B') {
			start = i;
		}
		if (maze[i] == 'E') {
			end = i;
		}
	}
	return true;
}

//returns the private data member maze and allows access to it 
//returns a valid maze if possible 
const std::vector<unsigned char>& Maze::get() const {
	//const std::vector<unsigned char> m;
	return maze;
}


//similar to parameterized constructor, but does not handle excpetions
//returns false for invalid parameters
//same algorithmic process as constrcutor
//takes the dimensions of rows by columns and places a maze full of walls denoted by '#'
//starting with the seed cell walls are knocked down inbetween random neighbors until all the walls are knocked down and all neighbors are visited
//returns false for invalid mazes consisting of size too small to conatin start and end or if the start and end points are the same
bool Maze::create(std::size_t rows, std::size_t cols, std::size_t begin, std::size_t end) {
	if (begin == end) {
		return false;
	}
	if ((rows < 1 && cols < 2) || (rows < 2 && cols < 1)) {
		return false;
	}


	this->cols = cols;
	this->rows = rows;
	maze.reserve(rows*cols);
	Stack<unsigned char> stack;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			maze.push_back(j + (i*cols));

			if ((j + (i * cols)) == begin) {
				maze[j + (i * cols)] = 'B';
			}
			else if ((j + (i * cols)) == end) {
				maze[j + (i * cols)] = 'E';
			}
			else {
				maze[j + (i * cols)] = '#';
			}
		}
	}
	unsigned char seed = maze[0];

	if (seed == 'B') {
		maze[0] = 'B';
	}
	else if (seed == 'E') {
		maze[0] = 'E';
	}
	else {
		maze[0] = ' ';
	}
	int index;
	//finds the beginning and end point and marks the seed cell
	//starts removing a wall and marking a neighbor for seed cell
	while (stack.isEmpty()) {
		int ind = rand() % 2;
		//std::cout << ind << std::endl;
		if (getNeighbors(0)[ind] < rows*cols) {
			int wall = getWall(0, getNeighbors(0)[ind]);
			if (maze[wall] == 'B') {
				maze[wall] = 'B';
			}
			else if (maze[wall] == 'E') {
				maze[wall] = 'E';
			}
			else {
				maze[wall] = ' ';
			}
			if (maze[getNeighbors(0)[ind]] == 'B') {
				maze[getNeighbors(0)[ind]] = 'B';
			}
			else if (maze[getNeighbors(0)[ind]] == 'E') {
				maze[getNeighbors(0)[ind]] = 'E';
			}
			else {
				maze[getNeighbors(0)[ind]] = ' ';
			}
			stack.push(seed);
			index = getNeighbors(0)[ind];
		}
	}
	unsigned char cell;
	while (!stack.isEmpty()) {
		cell = stack.pop();
		//int ind = rand() % 4;
		std::vector<std::size_t> unv;
		//gets valid neighbors and stores it into unv
		for (int ind = 0; ind < 4; ind++) {
			if (getNeighbors(index)[ind] < rows*cols) {
				unv.push_back(getNeighbors(index)[ind]);
				//std::cout << getNeighbors(index)[ind] << std::endl;
			}
		}

		if (unv.size() != 0) {
		}

		//randonmly permutes the vector containing valid neighbors

		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(unv.begin(), unv.end(), g);
		int wall;
		wall = getWall(index, unv[0]);
		std::cout << "wall: " << getWall(index, unv[0]) << std::endl;
		//if the neighbor is marked as unvisited then visit the neighbor and knock the wall down
		//then mark the neighbor as the current cell
		if (maze[unv[0]] != ' ') {
			stack.push(cell);
			if (maze[unv[0]] == 'B') {
				maze[unv[0]] = 'B';
				stack.push(maze[unv[0]]);
			}
			else if (maze[unv[0]] == 'E') {
				maze[unv[0]] = 'E';
				stack.push(maze[unv[0]]);
			}
			else {
				maze[unv[0]] = ' ';
				stack.push(maze[unv[0]]);
			}
			if (maze[wall] == 'B') {
				maze[wall] = 'B';
			}
			else if (maze[wall] == 'E') {
				maze[wall] = 'E';
			}
			else {
				maze[wall] = ' ';
			}
		}
		std::cout << unv[0] << std::endl;
		index = unv[0];



		return true;
	}
	

	

}


//solves a valid maze using recursive backtarcking
//finds the start and end points to find the shortest path in between them
bool Maze::solve() {
	int start, end;
	for (int i = 0; i < rows*cols; i++) {
		if (maze[i] == 'B') {
			start = i;
		}
		if (maze[i] == 'E') {
			end = i;
		}
	}


	if (backtrack(start)) {
		return true;
	}
	else {
		return false;
	}
}

//gets the neighbors of the current cell denotedby its index
//creates a vector full of the neighbors and has placeholders to keep the size consistent
//returns a vector full of the current cells neighbors
std::vector<std::size_t> Maze::getNeighbors(std::size_t ind) const {
	std::vector<std::size_t> m;
	
	if (ind / cols < 2 && ind % cols < 2) {
		m = { ind + (2 * cols), ind + 2, rows*cols, rows*cols };
	}
	else if (ind / cols < 2 && ind % cols > cols - 3) {
		m = { ind + (2 * cols), ind - 2, rows*cols, rows*cols };
	}
	else if ((ind / cols > rows - 3) && ind % cols < 2) {
		m = { ind - (2 * cols), ind + 2, rows*cols, rows*cols };
	}
	else if ((ind / cols > rows - 3) && ind % cols > cols - 3) {
		m = { ind - (2 * cols), ind - 2, rows*cols, rows*cols };
	}
	else if (ind % cols < 2) {
		m = { ind - (2 * cols), ind + (2 * cols), ind + 2, rows*cols };
	}
	else if (ind % cols > cols - 3) {
		m = { ind - (2 * cols), ind + (2 * cols), ind - 2, rows*cols };
	}
	else if (ind / cols < 2) {
		m = { ind + (2 * cols), ind + 2, ind - 2, rows*cols };
	}
	else if (ind / cols > rows - 3) {
		m = { ind - (2 * cols), ind + 2, ind - 2, rows*cols };
	}
	else {
		m = { ind - (2 * cols), ind + (2 * cols), ind - 2, ind + 2 };
	}
	return m;
}


//returns the wall in between the current cell and its neighbor
//uses the indices of the current cell and its neighbor to find whaere to knock a wall down
int Maze::getWall(std::size_t ind1, std::size_t ind2) const {
	int w;

	if (ind2 == ind1 + 2) {
		w = ind1 + 1;
	}
	else if (ind2 == ind1 - (2 * cols)) {
		w = ind1 - cols;
	}
	else if (ind2 == ind1 + (2 * cols)) {
		w = ind1 + cols;
	}
	else if (ind2 == ind1 - 2) {
		w = ind1 - 1;
	}

	return w;
}

//returns the successors of a curent cell denoted by its index
//successors are cells directly above, below, left of, or right of the current cell
std::vector<std::size_t> Maze::getSuccessors(std::size_t ind) const {
	std::vector<std::size_t> m;
		m = { ind - cols, ind + cols, ind - 1, ind + 1 };
	
	return m;
}

//recursice method to go through the maze and solve the path from the beginning to the end
//incomplete because of repeated stack overflows from any way I tried 
//done by finding the end in the maze if the current cell isn't the end it will keep backtracking through
//the maze leaving a trail from the beginning eventually to the end
//returns true if found the end or false if at a wall
bool Maze::backtrack(std::size_t ind) {
	if (maze[ind] == 'E') {
		return true;
	}
	else if (maze[ind] == '#') {
		return false;
	}
	else {
		if (maze[ind] == 'B') {
			maze[ind] = 'B';
		}
		else {
			maze[ind] = '*';
		}
		backtrack(ind + 1);
	}
}