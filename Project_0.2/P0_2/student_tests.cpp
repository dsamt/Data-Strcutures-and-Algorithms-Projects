
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include <cmath>
#include <iostream>

#include "catch.hpp"
#include "RayTracer.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

// This is just a simple example for demonstration
TEST_CASE( "Test default constructor", "[RayTracer]" ) {
  RayTracer r;
  r.getScene("scene_default.png");
}

TEST_CASE( "Test parameterized constructor", "[RayTracer]" ) {
  Vector light(0,10,0), camera(5,0,0), target(0,0,0);

  //a large magenta sphere with lots of internal light
  std::vector<unsigned char> col = {255,0,255,255};
  Sphere sph(2, Vector(0,0,0), col, 0.5);
  
  RayTracer r(light, camera, target, sph);
  r.getScene("scene_parameterized.png");
}

TEST_CASE("Test normal", "[Sphere]") {
	Vector C(0, 0, 0);
	Vector y(1, 1, 1);

	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(2, C, col, 0.5);
	Vector num(y.sub(C));
	Vector norm(num.getI() / num.norm(), num.getJ() / num.norm(), num.getK() / num.norm());

	Vector normal(sph.normal(y));

	REQUIRE(normal.getI() == norm.getI());
	REQUIRE(normal.getJ() == norm.getJ());
	REQUIRE(normal.getK() == norm.getK());

}

TEST_CASE("Test intersection", "[Sphere]") {
	Vector C(0, 0, 0);
	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(1, C, col, 0.5);
	Vector s(5,0,0);
	Vector d(s.getI() / s.norm(), s.getJ() / s.norm(), s.getK() / s.norm());
	Vector intersect(sph.intersect(s, d));
	//intersection point calculated by hand
	REQUIRE(intersect.getI() == 1);
	REQUIRE(intersect.getJ() == 0);
	REQUIRE(intersect.getK() == 0);



}

TEST_CASE("Test color", "[Sphere]") {
	Vector C(0, 0, 0);
	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(1, C, col, 0.5);

	REQUIRE(sph.color()[0] == 255);
	REQUIRE(sph.color()[1] == 0);
	REQUIRE(sph.color()[2] == 255);
	REQUIRE(sph.color()[3] == 255);

}

TEST_CASE("Test Radius", "[Sphere]") {
	Vector C(0, 0, 0);
	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(1, C, col, 0.5);

	REQUIRE(sph.radius() == 1);


}

TEST_CASE("Test Position", "[Sphere]") {
	Vector C(0, 0, 0);
	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(1, C, col, 0.5);

	REQUIRE(sph.position().getI() == C.getI());
	REQUIRE(sph.position().getJ() == C.getJ());
	REQUIRE(sph.position().getK() == C.getK());

}
