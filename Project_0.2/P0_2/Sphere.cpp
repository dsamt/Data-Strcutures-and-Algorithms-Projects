#include "Sphere.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

//default constrcutor that sets the default settings of the shape that will be created
Sphere::Sphere() : rad(1), pos(0, 0, 0), col{ 255, 0, 0, 255 }, amb(0.2) {

}
//paramerterized constructor that allows for the use of the variables in question
Sphere::Sphere(double rad, Vector pos, std::vector<unsigned char> col, double amb) {
	this->rad = rad;
	this->pos = pos;
	this->col = col;
	this->amb = amb;
}
//returns the color of the shape and allows access to it
std::vector<unsigned char> Sphere::color() const {
	return col;
}
//returns the position of the center of the shape
Vector Sphere::position() const {
	return pos;
}
//allows acces to the ambience of the shape that is being colored
double Sphere::ambient() const {
	return amb;
}

//allows the user to get the point of intersection for a shape and the rays that will be traced if need be
//if no intersection returns infinity
//if intersection returns the vector at the point of intersection
Vector Sphere::intersect(const Vector& s, const Vector& d) const {
	Vector v(s.sub(position()));
	double first_term = v.dot(d);
	double first_term_sq = pow(first_term, 2);
	double s_mag = v.norm();
	double s_mag_sq = pow(s_mag, 2);
	double rad_sq = pow(rad, 2);
	double second_term = s_mag_sq - rad_sq;
	double first_eq = first_term_sq - second_term;
	//if the first equation in 2.2 is not satisified, no intersection, set to inifinity
	if (first_eq <= 0) {
		Vector v(INFINITY, INFINITY, INFINITY);
		return v;
	}
	else {
		//quadratic equation to solve first equation and find points of intersection
		double t_plus = -1 * (first_term)+sqrt(first_term_sq - second_term);
		double t_minus = -1 * (first_term)-sqrt(first_term_sq - second_term);

		Vector t_d_plus(d.getI()*t_plus, d.getJ()*t_plus, d.getK()*t_plus);
		Vector t_d_minus(d.getI()*t_minus, d.getJ()*t_minus, d.getK()*t_minus);
		double t_plus_mag = t_d_plus.norm();
		double t_minus_mag = t_d_minus.norm();
		//find which  vector is shorter to see which is closer to camera
		if (t_plus_mag <= t_minus_mag) {
			Vector y(s.add(t_d_plus));
			return y;
		}
		else if (t_minus_mag < t_plus_mag) {
			Vector y(s.add(t_d_minus));
			return y;
		}
	}
}
//allows the radius of the shape to be accessed
double Sphere::radius() const {
	return rad;
}
//calculates the unit vector normal to the surface at point of intersection
Vector Sphere::normal(const Vector& pos) const {
	Vector num(pos.sub(position()));
	double den;
	den = num.norm();

	Vector normal((num.getI() / den), (num.getJ() / den), (num.getK() / den));

	return normal;
}