#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "Vector.hpp"
#include "Sphere.hpp"

//This method uses the C++ output function to display the vector that has been created by the user
void Vector::output(std::ostream &out) const
{
	out << vx << "i + " << vy << "j + " << vz << "k";
}

//Default constructor method that sets and creates an initial vector to the zero vector
Vector::Vector() : vx(0), vy(0), vz(0)
{
}

//paramterized constrcutor method that accesses and creates the indivdual components of a defined Vector
Vector::Vector(double vx, double vy, double vz) {
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
}

//method that gets the x component of the defined vector and is used to return was that value is
double Vector::getI() const {
	return vx;
}

//method that gets the y component of the defined vector and is used to return was that value is
double Vector::getJ() const {
	return vy;
}

////method that gets the z component of the defined vector and is used to return was that value is
double Vector::getK() const {
	return vz;
}

//method that allows the user to set the x component of the vector
void Vector::setI(double newVx) {
	vx = newVx;
}

//method that allows the user to set the y component of the vector
void Vector::setJ(double newVy) {
	vy = newVy;
}

//method that allows the user to set the z component of the vector
void Vector::setK(double newVz) {
	vz = newVz;
}

//method that checks if two vector's components are equal by comparing the lhs(one vector) 
//and rhs(another vector) and returns true if they are equal and false otherwise
bool Vector::equal(const Vector& rhs) const {
	return ((vx == rhs.vx) && (vy == rhs.vy) && (vz == rhs.vz));
}

//method that takes two vectors and adds their individual componets to create a resultant vector and returns that vector
Vector Vector::add(const Vector &rhs) const {
	return Vector(vx + rhs.vx, vy + rhs.vy, vz + rhs.vz);
}

//method that takes two vectors and subtracts their individual componets to create a resultant vector and returns that vector
Vector Vector::sub(const Vector &rhs) const {
	return Vector(vx - rhs.vx, vy - rhs.vy, vz - rhs.vz);
}

//Method that takes two vectors and finds the cross product of them and creates a resultant vector, which is returned by the method
Vector Vector::cross(const Vector &rhs) const {
	return Vector(((vy*rhs.vz) - (vz*rhs.vy)), ((vz*rhs.vx) - (vx*rhs.vz)), ((vx*rhs.vy) - (vy*rhs.vx)));
}

//Method that returns a double, which represents the dot product of two given vetcors
double Vector::dot(const Vector &rhs) const {
	return (vx*rhs.vx) + (vy*rhs.vy) + (vz*rhs.vz);
}

//Methid that takes two vetcors and finds the two norm(magnitude) of the vectros and returns a double
double Vector::norm() const {
	double vx_squared = std::pow(vx, 2);
	double vy_squared = std::pow(vy, 2);
	double vz_squared = std::pow(vz, 2);

	return sqrt(vx_squared + vy_squared + vz_squared);
}

//Method used to find the angle between two given vetcors and returns a double(with special parameters)
double Vector::angle(const Vector &rhs) const {
	double angle;

	//finds the angle if neither of the vectors is the zero vector
	if ((vx != 0 || vy != 0 || vz != 0) && (rhs.vx != 0 || rhs.vy != 0 || rhs.vz != 0)) {
		angle = acos(dot(rhs) / ((sqrt(pow(vx, 2) + pow(vy, 2) + pow(vz, 2))) * (sqrt(pow(rhs.vx, 2) + pow(rhs.vy, 2) + pow(rhs.vz, 2)))));

		//gives the angle if the angle found is outside the interval [0, 2pi)
		if (angle < 0)
			angle = angle + 2 * M_PI;
	}
	//method returns -1 if the denominator of the angle formula is zero
	else if ((vx == 0 && vy == 0 && vz == 0) || (rhs.vx == 0 && rhs.vy == 0 && rhs.vz == 0))
		angle = -1;
	return angle;
}
