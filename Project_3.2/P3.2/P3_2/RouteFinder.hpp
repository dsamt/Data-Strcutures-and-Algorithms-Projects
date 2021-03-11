//
//  RouteFinder.hpp
//  
//
//  Created by Tam Chantem on 10/14/20.
//

#ifndef RouteFinder_hpp
#define RouteFinder_hpp

#include "dLinkedList.hpp"


class RouteFinder
{
public:
    /** Default constructor: creates an empty RouteFinder object.
     @return Sets data fields appropriately. */
    RouteFinder();
    
    /** Copy constructor: performs a deep copy of r.
     @param r A RouteFinder object to copy.
     @return Sets data fields appropriately. */
    RouteFinder(const RouteFinder& r);
    
    /** Parameterized constructor.
     @param f A filename to load data from. See project description for the file format. If f does not exist or does not have the correct format, a RouteFinder object is created based on the input file "sample.txt", which can be assumed to always exist.
     @return Sets data fields appropriately. */
    RouteFinder(const std::string& f);
    
    /** Assignment operator overloading: performs a deep copy of x.
     @param x A RouteFinder object to copy.
     @return A RouteFinder object with identical contents as x. */
    RouteFinder& operator=(RouteFinder x);
    
    /** Gets the total number of houses.
     @return The integer number representing the total number of houses. */
    int getHouseNum() const;
   
    /** Gets the vector containing the distance between houses.
     @return The vector representing the distances. */
    std::vector< dLinkedList<double> > getDist() const;

    /** Gets the vector containing the number of boxes for the houses.
     @return The vector representing the integer number of boxes for the houses. */
    std::vector<int> getBoxes() const;
    
    /** Gets the maximum number of boxes a delivery truck can carry.
     @return An integer representing the maximum number of boxes per truck. */
    int getMaxBoxes() const;

    /** Gets the the maximum distance for each delivery truck.
     @return A number representing the maximum distance a delivery truck can travel per day. */
    double getMaxDist() const;
    
    /** Sets the total number of houses.
     @param n is the total number of houses.
     @return Set data fields appropriately. */
    void setHouseNum(int n);
    
    /** Sets the distances between houses.
     @param d is the distance matrix in the form of a vector of doubly linked list. (See project description.)
     @return Set data fields appropriately. */
    void setDist(std::vector< dLinkedList<double> > d);
    
    /** Sets the number of boxes for the houses.
     @param b is the vector containing the number of boxes to be delivered to each house.
     @return Set data fields appropriately. */
    void setBoxes(std::vector<int> b);
    
    /** Sets the maximum number of boxes a delivery truck can carry.
     @param m is the maximum number of boxes.
     @return Set data fields appropriately. */
    void setMaxBoxes(int m);
    
    /** Sets the the maximum distance for each delivery truck.
     @param d is the maximum distance a truck can travel in a day.
     @return Set data fields appropriately. */
    void setMaxDist(double d);

    /** Heuristic algorithm to solve Problem 1 (see project description).
    @return sets data fields appropriately. */
    void solve();
    
    /** Gets the final routes.
     @return A vector of doubly linked list. See project description. */
    std::vector< dLinkedList<int> > getRoutes() const;
    
    /** Gets the distance of each of the final routes.
     @return A vector of real numbers showing the cost for each route. */
    std::vector<double> getRouteDist() const;
    
    /** Gets the total number of boxes on each route.
     @return A vector of integers showing the total number of boxes on each route. */
    std::vector<int> getBoxNum() const;
    
    /** Get the total distance of the fleet.
     @return The total fleet distance per day. */
    double getFinalDist() const;
    
private:
    std::vector< dLinkedList<double> > dist; // A vector of linked lists containing the distances between houses (and distribution center). See example in the project description.
    
    std::vector<int> boxes; // The number of boxes to be delivered at each house.
    
    int num; // The total number of houses.
    
    int maxBoxes; // The total number of boxes a delivery truck can carry per day.
    
    double maxDist; // The maximum distance a delivery truck can travel per day.
    
    std::vector< dLinkedList<int> > routes; // A vector of linked lists containing the routes selected by your heuristic algorithm. See example in the project description.
    
    std::vector<double> routeCost; // A vector containing the total distance for each route in the solution.
    
    std::vector<int> boxNum; // A vector containing the total number of boxes for each route in the solution.
    
    double totalDist; //The total distance covered by the entire fleet of delivery trucks according to your algorithm.

	void swap(RouteFinder& x, RouteFinder& y); //helper method for assignment operator

	dLinkedList<double> Dist; //linked list to be used for reading in the distances for dist vector
	dLinkedList<int> Routes; //linked list used for creating routes and setting the routes solution vector

	std::vector<std::vector<double>> getVector(std::vector< dLinkedList<double> > d); //helper method to convert dist vector full of linked lists into a vector of doubles for easier reading
};

#include "RouteFinder.cpp"

#endif /* RouteFinder_hpp */
