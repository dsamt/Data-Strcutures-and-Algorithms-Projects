//
//  RouteFinder.cpp
//  
//

#include "RouteFinder.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


//default constructor
//creates an empty problem set where there are no routes to be found because there are no boxes
//to be delivered and there is no distance to be traveled
RouteFinder::RouteFinder()  {
	num = 0;
	totalDist = 0;
	maxBoxes = 0;
	maxDist = 0;
}

//copy constructor
//this is another constructir that creates a deep copy of the paramter x which is a route finder object
//this copies the current contents from the route finder object created from the paramterized constructor into the new 
//object, sets the appropriate data fields in order to create a new class object to solve the problem
RouteFinder::RouteFinder(const RouteFinder& r) {

	dist = r.dist;
	boxes = r.boxes;
	num = r.num;
	maxBoxes = r.maxBoxes;
	maxDist = r.maxDist;
}

// Parameterized constructor
//this constructor actually sets up the problem to be solved by reading froma  file that is passed through as a parameter
//it creates the class object by setting the proper data fields that are explicity given in the file to be read
//the data fields are labeled in the file and can be accessed and addressed by these labels
//each data field is set through the private data members from the class
//if the file that is read cannot be opened for whatever reason the constructor throws an exception
//and ghandles it by callinga default file that we know exists and can be opened called "sample.txt"
//if the file is in the incorrect format so that the proper fields cannot be read then an exception is thrown and the default file is again read from
RouteFinder::RouteFinder(const std::string& f) {
	std::ifstream infile(f);
	std::vector<std::string> word;
	//throw an exception if file cannot be accessed
	if (!infile.is_open()) {
		try {
			infile.open("sample.txt");
		}
		catch (const std::exception& e) {
			std::ostringstream msg;
			msg << "Opening file '" << f << "' failed" << std::endl;
			throw std::runtime_error(msg.str());
		}
	}
	//read the file in word by word if the file can be opened
	if (infile.is_open()) {
		std::string line;
		while (infile >> line) {
			std::istringstream iss(line);
			

			word.push_back(line);
		}
	}
	
	//sets the private data fields accordingly based on what is read from the file
	if (word[0] == "num") {
		setHouseNum(std::stoi(word[1]));
	}
	if (word[num + 5] == "mdist") {
		setMaxDist(std::stod(word[num + 6]));
	}
	if (word[num + 3] == "mboxes") {
		setMaxBoxes(std::stoi(word[num + 4]));
	}
	if (word[2] == "boxes") {
		for (int i = 0; i < num; i++) {
			boxes.push_back(std::stoi(word[i + 3]));
		}
	}
	int k = 0;
	if (word[num + 7] == "dist") {
		for (int j = 1; j <= num; j++){
			for (int i = 0; i < j; i++) {
				Dist.addBack(std::stod(word[num + 8 + k]));
				k++;
			}
			dist.push_back(Dist);
			Dist.clear();
		}
	}
	//throw an exception if format is wrong
	if (infile.is_open() && (word[0] != "num" || word[num + 5] != "mdist" || word[num + 3] != "mboxes" || word[2] != "boxes" || word[num + 7] != "dist")) {
		try {
			infile.open("sample.txt");
		}
		catch (const std::exception& e) {
			std::ostringstream msg;
			msg << "File '" << f << "' has incorrect format" << std::endl;
			throw std::runtime_error(msg.str());
		}
		std::string line;
		while (infile >> line) {
			std::istringstream iss(line);


			word.push_back(line);
		}
	}

}



//Assignment operator overloading: performs a deep copy of x
//this is a copy assignment operator and does a similar job as the copy constructor
//creates a deep copy of the existing class object and copies the data fields into the new object
//that is given by the paramter passed in the method, uses a helper function to swap the data fields that are needed
//returns a class object that has the attributes from the existing object 
RouteFinder& RouteFinder::operator=(RouteFinder x) {
	swap(*this, x);

	return *this;
}

//helper method for the assignment operator
//swaps all the data fields from the existing route finder object into the new one that is used by the assignemnt operator
//allows for a deep copy to be made when it is used in the assignment operator
void RouteFinder::swap(RouteFinder& x, RouteFinder& y) {
	std::swap(x.dist, y.dist);
	std::swap(x.boxes, y.boxes);
	std::swap(x.num, y.num);
	std::swap(x.maxBoxes, y.maxBoxes);
	std::swap(x.maxDist, y.maxDist);
}

//returns the value of the private data member HouseNum, which is of type int
//allows access to the private data member HouseNum
int RouteFinder::getHouseNum() const {
	return num;
}

//returns the value of the private data member Dist, which is of type vector of linked lists
//allows access to the private data member Dist
std::vector< dLinkedList<double> > RouteFinder::getDist() const {
	return dist;
}

//returns the value of the private data member Boxes, which is of type vector of integers
//allows access to the private data member Boxes
std::vector<int> RouteFinder::getBoxes() const {
	return boxes;
}

//returns the value of the private data member maxBoxes, which is of type int
//allows access to the private data member maxBoxes
int RouteFinder::getMaxBoxes() const {
	return maxBoxes;
}

//returns the value of the private data member MaxDist, which is of type double
//allows access to the private data member MaxDist
double RouteFinder::getMaxDist() const {
	return maxDist;
}

//sets the private data member HouseNum by passing the appropriate type through the method
//which is of type int and sets the private data member accordingly
void RouteFinder::setHouseNum(int n) {
	this->num = n;
}

//sets the private data member Dist by passing the appropriate type through the method
//which is of type vector of linked lists and sets the private data member accordingly
void RouteFinder::setDist(std::vector< dLinkedList<double> > d) {
	this->dist = d;
}

//sets the private data member Boxes by passing the appropriate type through the method
//which is of type vector of int and sets the private data member accordingly
void RouteFinder::setBoxes(std::vector<int> b) {
	this->boxes = b;
}

//sets the private data member MaxBoxes by passing the appropriate type through the method
//which is of type int and sets the private data member accordingly
void RouteFinder::setMaxBoxes(int m) {
	this->maxBoxes = m;
}

//sets the private data member MaxDist by passing the appropriate type through the method
//which is of type double and sets the private data member accordingly
void RouteFinder::setMaxDist(double d) {
	this->maxDist = d;
}

//solves the problem at stake, which is finding the shortest distance for n number of delivery drivers
//by taking in the distances from each house repectively and based on parameters set by the constructor
//this algorithm finds the feasible routes to deliver a certain amount of boxes to a certain amount of houses
void RouteFinder::solve() {
	
	std::vector<std::vector<double>> d = getVector(dist);//sets a vector that represents the dist vector full of linked lists in the form of a vector full of doubles to make it easier to read from, done so througha helper method
	//sets placeholder variables to read into vectors later
	double totalBoxes = 0;
	double routeCosts = 0;
	int box = 0;
	totalDist = 0;
	//main part of the algorithm that goes through each of the houses distances, reads the vector backwards starting from the last house
	for (int j = num - 1; j >= 0; j--) {
		for (int i = 0; i <= j; i++) {
			//each if statement sets the variables to be used as constraints later and is based on if the distances to the right of the intial value of each row in eahc vector is less than how far the distance from that house is from the depot
			if (d[j][i] <= d[j][0] && i != 0 && !Dist.contains(j + 1) && !Dist.contains(i) && box < maxBoxes && (box + boxes[i-1]) < maxBoxes) {
				box += boxes[i - 1];
				routeCosts += d[i - 1][0];
				if (!Dist.contains(j + 1)) {
					box += boxes[j];
					routeCosts += d[j][i] + d[j][0];
				}
			}
			else if (d[j][i] <= d[j][0] && i != 0 && Routes.contains(j + 1) && box < maxBoxes && (box + boxes[i - 1]) <= maxBoxes) {
				box += boxes[i - 1];
				routeCosts += d[j][i] + d[i - 1][0];
				routeCosts -= d[j][0];
			}
			else if (d[j][i] <= d[j][0] && i == j && !Dist.contains(j + 1) && box < maxBoxes) {
				box += boxes[j];
				routeCosts += 2 * d[j][0];
			}
			else if (Dist.getCurrentSize() == num - 1 && i == 0 && Routes.isEmpty() && !Dist.contains(j + 1) && box < maxBoxes) {
				box += boxes[j];
				routeCosts += 2 * d[j][0];
			}
			
			
			if (d[j][i] <= d[j][0] && box > maxBoxes && routeCosts < maxDist && !Dist.contains(j + 1) && !Dist.contains(i)) {
				routeCosts = 0;
				routeCosts += 2 * d[j][0];
			}
			

			//for each if statement based on if the number of boxes set eariler and distance set eariler is less than the constraints and if the distances right of the intial value of the vector in each row are less than add the values of the house to the linked list to be added to the routes vector later
			if (d[j][i] <= d[j][0] && i != 0 && !Dist.contains(j + 1) && !Dist.contains(i) && box <= maxBoxes && routeCosts < maxDist && Routes.getCurrentSize() < 3) {
				Routes.addBack(i);
				Dist.addBack(i);
				if (!Dist.contains(j + 1)) {
					Routes.addBack(j + 1);
					Dist.addBack(j + 1);
				}
			}
			else if (d[j][i] <= d[j][0] && i != 0 && Routes.contains(j + 1) && !Dist.contains(i) && box <= maxBoxes && routeCosts < maxDist && Routes.getCurrentSize() < 3) {
				Routes.addBack(i);
				Dist.addBack(i);
			}
			/*
			else if (d[j][i] <= d[j][0] && i == j && !Dist.contains(j + 1) && box <= maxBoxes){
				Routes.addBack(j + 1);
				Dist.addBack(j + 1);
			}
			*/
			else if (d[j][i] <= d[j][0] && box > maxBoxes && routeCosts < maxDist && !Dist.contains(j + 1) && !Dist.contains(i) && Routes.getCurrentSize() < 3) {
				Routes.addBack(j + 1);
				Dist.addBack(j + 1);
				box -= boxes[i - 1];
				routeCosts -= 0;
			}
			else if (Dist.getCurrentSize() == num - 1 && i == 0 && Routes.isEmpty() && !Dist.contains(j + 1) && routeCosts < maxDist && Routes.getCurrentSize() < 3) {
				Routes.addBack(j + 1);
				Dist.addBack(j + 1);
			}
			else if (d[j][i] <= d[j][0] && routeCosts >= maxDist && box <= maxBoxes && !Dist.contains(j + 1) && !Dist.contains(i) && Routes.getCurrentSize() < 3) {
				Routes.addBack(j + 1);
				Dist.addBack(j + 1);
			}
			
		}
		if (!Dist.contains(j + 1))
		{
			Routes.addBack(j + 1);
			box = boxes[j];
			routeCosts = 2 * d[j][0];
		}
		//adds each value that was set eariler to their corresponding private data member and restes certain values
			if (!Routes.isEmpty()) {
			boxNum.push_back(box);
			routeCost.push_back(routeCosts);
			box = 0;
			routeCosts = 0;
			Routes.add(0);
			Routes.addBack(0);
			//Routes.printList();
			routes.push_back(Routes);
			Routes.clear();
		}
	}
	//sets the total distance from the vector routeCost that cintains the distance for each house in the route
	for (int i = 0; i < routeCost.size(); i++) {
		//std::cout << routeCost[i] << std::endl;
		totalDist += routeCost[i];
	}
	
	//std::cout << totalDist << std::endl;
}

//helper method to set the distances that were read into linked lists into a vector instead in order to make it easier to read from
//returns a two dimensional vector that is in the same pyramid form as in the description
std::vector<std::vector<double>> RouteFinder::getVector(std::vector< dLinkedList<double> > d) {
	std::vector<std::vector<double>> vect(num, std::vector<double>(num + 1));
	for (int j = 0; j < num; j++) {
		for (int i = 0; i <= j; i++) {
			if (d[j].getItem(i) == -1) {
				vect[j][i] = INFINITY;
			}
			else {
				vect[j][i] = d[j].getItem(i);
			}
			
			//std::cout << vect[j][i] << " ";
			
		} 
		//std::cout << std::endl;
	}

	return vect;
}

//returns the private data member from the soultion, which is vector full of linked lists that contains the routes for the solution
//allows access to the private data member routes, which is part of the solution
std::vector< dLinkedList<int> > RouteFinder::getRoutes() const {
	return routes;
}

//returns the private data member from the soultion, which is vector full of doubles that contains the routes distances for the solution
//allows access to the private data member routeCost, which is part of the solution
std::vector<double> RouteFinder::getRouteDist() const {
	return routeCost;
}

//returns the private data member from the soultion, which is vector full of ints that contains the box numbers for the solution
//allows access to the private data member BoxNum, which is part of the solution
std::vector<int> RouteFinder::getBoxNum() const {
	return boxNum;
}

//returns the private data member from the soultion, which is a double that contains the total distance traveled for the solution
//allows access to the private data member totalDist, which is part of the solution
double RouteFinder::getFinalDist() const {
	return totalDist;
}