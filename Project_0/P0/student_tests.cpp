#define _USE_MATH_DEFINES
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include <cmath>
#include <complex>
#include <iostream>

#include "catch.hpp"
#include "Vector.hpp"

// This is just a simple example for demonstration
// we will see how to do proper testing in meeting 3
TEST_CASE( "Test default constructor", "[Vector]" )
{
  Vector v;
  REQUIRE(v.getI() == 0);
  REQUIRE(v.getJ() == 0);
  REQUIRE(v.getK() == 0);
}

TEST_CASE("Test paramerterized constructor", "[Vector]") {

	srand(time(NULL));
	double x = rand() % 100 / 10.0;
	double y = rand() % 100 / 10.0;
	double z = rand() % 100 / 10.0;
	Vector v(x, y, z);
	REQUIRE(v.getI() == x);
	REQUIRE(v.getJ() == y);
	REQUIRE(v.getK() == z);
}

//tests both default and paramterized constructors for set method
TEST_CASE("Test setters", "[Vector]") {
	Vector v;

	REQUIRE(v.getI() == 0);
	REQUIRE(v.getJ() == 0);
	REQUIRE(v.getK() == 0);

	double x = rand() % 100 / 10.0;
	double y = rand() % 100 / 10.0;
	double z = rand() % 100 / 10.0;
	v.setI(x);
	v.setJ(y);
	v.setK(z);

	REQUIRE(v.getI() == x);
	REQUIRE(v.getJ() == y);
	REQUIRE(v.getK() == z);
}

//tests both default and paramterized constructors for equal method
TEST_CASE("Test equal", "[Vector]") {
	Vector v1;
	Vector v2;

	REQUIRE(v1.equal(v2));
	REQUIRE(v2.equal(v1));

	double x = rand() % 100 / 10.0;
	double y = rand() % 100 / 10.0;
	double z = rand() % 100 / 10.0;
	
	v1.setI(x);
	v1.setJ(y);
	v1.setK(z);
	v2.setI(x);
	v2.setJ(y);
	v2.setK(z);

	REQUIRE(v1.equal(v2));
	REQUIRE(v2.equal(v1));
}

//tests both default and paramterized constructors for addition method
TEST_CASE("Testing add", "[Vector]") {
	Vector v1;
	Vector v2;
	Vector v3;

	v3 = v1.add(v2);
	REQUIRE(v3.getI() == 0);
	REQUIRE(v3.getJ() == 0);
	REQUIRE(v3.getK() == 0);

	double x1 = rand() % 100 / 10.0;
	double y1 = rand() % 100 / 10.0;
	double z1 = rand() % 100 / 10.0;
	double x2 = rand() % 100 / 10.0;
	double y2 = rand() % 100 / 10.0;
	double z2 = rand() % 100 / 10.0;

	v1.setI(x1);
	v1.setJ(y1);
	v1.setK(z1);
	v2.setI(x2);
	v2.setJ(y2);
	v2.setK(z2);

	v3 = v1.add(v2);
	REQUIRE(x1 + x2 == v3.getI());
	REQUIRE(y1 + y2 == v3.getJ());
	REQUIRE(z1 + z2 == v3.getK());
}

//tests both default and paramterized constructors for subtraction method
TEST_CASE("Testing sub", "[Vector]") {
	Vector v1;
	Vector v2;
	Vector v3;

	v3 = v1.sub(v2);
	REQUIRE(v3.getI() == 0);
	REQUIRE(v3.getJ() == 0);
	REQUIRE(v3.getK() == 0);

	double x1 = rand() % 100 / 10.0;
	double y1 = rand() % 100 / 10.0;
	double z1 = rand() % 100 / 10.0;
	double x2 = rand() % 100 / 10.0;
	double y2 = rand() % 100 / 10.0;
	double z2 = rand() % 100 / 10.0;

	v1.setI(x1);
	v1.setJ(y1);
	v1.setK(z1);
	v2.setI(x2);
	v2.setJ(y2);
	v2.setK(z2);

	v3 = v1.sub(v2);
	REQUIRE(x1 - x2 == v3.getI());
	REQUIRE(y1 - y2 == v3.getJ());
	REQUIRE(z1 - z2 == v3.getK());
}

//tests both default and paramterized constructors for cross product method
TEST_CASE("Testing cross", "[Vector]") {
	Vector v1;
	Vector v2;
	Vector v3;

	v3 = v1.cross(v2);
	REQUIRE(v3.getI() == 0);
	REQUIRE(v3.getJ() == 0);
	REQUIRE(v3.getK() == 0);

	double x1 = rand() % 100 / 10.0;
	double y1 = rand() % 100 / 10.0;
	double z1 = rand() % 100 / 10.0;
	double x2 = rand() % 100 / 10.0;
	double y2 = rand() % 100 / 10.0;
	double z2 = rand() % 100 / 10.0;

	v1.setI(x1);
	v1.setJ(y1);
	v1.setK(z1);
	v2.setI(x2);
	v2.setJ(y2);
	v2.setK(z2);

	v3 = v1.cross(v2);
	REQUIRE(y1*z2 - z1*y2 == v3.getI());
	REQUIRE(z1*x2 - x1*z2 == v3.getJ());
	REQUIRE(x1*y2 - y1*x2 == v3.getK());
}

//tests both default and paramterized constructors for dot product method
TEST_CASE("Testing dot", "[Vector]") {
	Vector v1;
	Vector v2;
	double v3;

	v3 = v1.dot(v2);
	REQUIRE(v3 == 0);

	double x1 = rand() % 100 / 10.0;
	double y1 = rand() % 100 / 10.0;
	double z1 = rand() % 100 / 10.0;
	double x2 = rand() % 100 / 10.0;
	double y2 = rand() % 100 / 10.0;
	double z2 = rand() % 100 / 10.0;

	v1.setI(x1);
	v1.setJ(y1);
	v1.setK(z1);
	v2.setI(x2);
	v2.setJ(y2);
	v2.setK(z2);

	v3 = v1.dot(v2);
	REQUIRE(v3 == (x1*x2) + (y1*y2) + (z1*z2));
}

//tests both default and paramterized constructors for two norm method
TEST_CASE("Testing norm", "[Vector]") {
	Vector v;
	REQUIRE(v.norm() == 0);

	v.setI(1);
	REQUIRE(v.norm() == 1);

	v.setI(0);
	v.setJ(1);
	REQUIRE(v.norm() == 1);

	v.setI(0);
	v.setJ(0);
	v.setK(1);
	REQUIRE(v.norm() == 1);

	v.setI(14);
	v.setJ(5);
	v.setK(2);
	REQUIRE(v.norm() == 15);
}

TEST_CASE("Testing angle", "[Vector]") {
	Vector v1, v2, v3, v4;
	//undefined
	REQUIRE(v1.angle(v2) == -1);
	//defined no interval correction
	double x1 = 1;
	double y1 = 2;
	double z1 = 3;
	double x2 = 4;
	double y2 = 5;
	double z2 = 6;
	v1.setI(x1);
	v1.setJ(y1);
	v1.setK(z1);
	v2.setI(x2);
	v2.setJ(y2);
	v2.setK(z2);
	std::ostringstream p1, p2;
	p1 << std::setprecision(4) << v2.angle(v1);
	p2 << std::setprecision(4) << acos((x1 * x2 + y1 * y2 + z1 * z2) / ((sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2))) * (sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2)))));
	REQUIRE(p1.str() == p2.str());
	//defined with interval correction
	double x3 = -5;
	double y3 = -5;
	double z3 = -5;
	double x4 = 3;
	double y4 = 3;
	double z4 = 3;
	v3.setI(x3);
	v3.setJ(y3);
	v3.setK(z3);
	v4.setI(x4);
	v4.setJ(y4);
	v4.setK(z4);
	std::ostringstream p3, p4;
	p3 << std::setprecision(4) << v3.angle(v4);
	p4 << std::setprecision(4) << (acos((x3 * x4 + y3 * y4 + z3 * z4) / ((sqrt(pow(x3, 2) + pow(y3, 2) + pow(z3, 2))) * (sqrt(pow(x4, 2) + pow(y4, 2) + pow(z4, 2))))));
	REQUIRE(p3.str() == p4.str());


}