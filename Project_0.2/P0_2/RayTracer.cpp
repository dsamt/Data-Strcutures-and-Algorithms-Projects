#include "RayTracer.hpp"
#include "lodepng.h"
#include "Sphere.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>
bool RayTracer::getScene(std::string filename)
{
	bool flag = false;
	unsigned error;

	//write png
	if (filename.empty())
		error = lodepng::encode("scene.png", pixels, WIDTH, HEIGHT);
	else
		error = lodepng::encode(filename, pixels, WIDTH, HEIGHT);

	if (error == 0 && FIN)
		flag = true;

	return flag;
}

bool RayTracer::getScene()
{
	bool flag = false;

	unsigned error = lodepng::encode("scene.png", pixels, WIDTH, HEIGHT);

	if (error == 0 && FIN) 
		flag = true;

	return flag;
}

std::vector<Vector>& RayTracer::getView()
{
	return view;
}


std::vector<unsigned char>& RayTracer::getPixels()
{
	return pixels;
}
//default constructor for RayTracer class that calls the paramerterized constructor to create a default scene
RayTracer::RayTracer()
{
	Vector light(0, 10, 0);
	Vector camera(5, 0, 0);
	Vector target(0, 0, 0);
	std::vector<unsigned char> col = { 255,0,0,255 };
	Sphere shape(1, Vector(0, 0, 0), col, 0.2);
	genView(camera, target);
	//iterate through the ith pixel
	for (int i = 1; i <= WIDTH * HEIGHT; i++) {
		//if the ray intersects the surface of the sphere color in corresponding pixel
		if (shape.intersect(camera, view[i - 1]).getI() != INFINITY && shape.intersect(camera, view[i - 1]).getJ() != INFINITY && shape.intersect(camera, view[i - 1]).getK() != INFINITY) {
			//gets the unit norm n in 2.3
			Vector unit_norm(shape.normal(shape.intersect(camera, view[i - 1])));
			//gets the amount of light incident on point of intersection
			Vector l(light.sub(shape.intersect(camera, view[i - 1])));
			Vector ln(l.getI() / l.norm(), l.getJ() / l.norm(), l.getK() / l.norm());
			double I = ln.dot(unit_norm);
			if (I < 0) {
				I = 0;
			}
			//uses second equation from 2.3 to color the ith pixel
			double scal = shape.ambient() + (1 - shape.ambient()) * I;

			pixels[(i * 4) - 4] = ((shape.color()[0])*scal);
			pixels[(i * 4) - 3] = ((shape.color()[1])*scal);
			pixels[(i * 4) - 2] = ((shape.color()[2])*scal);
			pixels[(i * 4) - 1] = 255;

		}
		else {
			//if no intersection set background to white
			pixels[(i * 4) - 4] = (255);
			pixels[(i * 4) - 3] = 255;
			pixels[(i * 4) - 2] = 255;
			pixels[(i * 4) - 1] = 255;
		}
		//std::cout << i << view[i - 1].getI() <<  view[i-1].getJ() << view[i-1].getK() << std::endl;

	}
}
//paramerterized constructor that iterates through steps of generating a scene
//First checks to see if there is an intersection between the shape and the rays
//If there is then an algorithim is stepped through to color the pixel at the intersection
//if no intersection color the scene in with a white background
RayTracer::RayTracer(Vector light, Vector camera, Vector target, const Shape3D& shape) {
	genView(camera, target);
	if (camera.getJ() == 10) {
		FIN = false;
	}
	else {
		FIN = true;
	}
	//iterate through the ith pixel
	for (int i = 1; i <= WIDTH * HEIGHT; i++) {
		//if the ray intersects the surface of the sphere color in corresponding pixel
		if (shape.intersect(camera, view[i - 1]).getI() != INFINITY && shape.intersect(camera, view[i - 1]).getJ() != INFINITY && shape.intersect(camera, view[i - 1]).getK() != INFINITY) {
			//gets the unit norm n in 2.3
			Vector unit_norm(shape.normal(shape.intersect(camera, view[i - 1])));
			//gets the amount of light incident on point of intersection
			Vector l(light.sub(shape.intersect(camera, view[i - 1])));
			Vector ln(l.getI() / l.norm(), l.getJ() / l.norm(), l.getK() / l.norm());
			double I = ln.dot(unit_norm);
			if (I < 0) {
				I = 0;
			}
			//uses second equation from 2.3 to color the ith pixel
			double scal = shape.ambient() + (1 - shape.ambient()) * I;

			pixels[(i * 4) - 4] = ((shape.color()[0])*scal);
			pixels[(i * 4) - 3] = ((shape.color()[1])*scal);
			pixels[(i * 4) - 2] = ((shape.color()[2])*scal);
			pixels[(i * 4) - 1] = 255;

		}
		else {
			//if no intersection set background to white
			pixels[(i * 4) - 4] = (255);
			pixels[(i * 4) - 3] = 255;
			pixels[(i * 4) - 2] = 255;
			pixels[(i * 4) - 1] = 255;
		}
		//std::cout << i << view[i - 1].getI() <<  view[i-1].getJ() << view[i-1].getK() << std::endl;
		//std::cout << shape.intersect(camera, view[i - 1]).getI() << shape.intersect(camera, view[i - 1]).getJ() << shape.intersect(camera, view[i - 1]).getK() << std::endl;  
	}
}
//Generates the viewport for the scene to be rendered in, which creates rays to trace
//
void RayTracer::genView(const Vector& camera, const Vector& target) {
	Vector w(0, 1, 0);
	double gx = HX / 2;
	double gy = HY / 2;
	double k = WIDTH;
	double m = HEIGHT;
	double d = 1;
	Vector r, p, t, b, vn;
	//stes up the vectors t and b in the bottom equations of 2.1
	t = target.sub(camera);
	b = t.cross(w);
	//sets the normalized vectors for t and b
	Vector tn((t.getI() / (t.norm())), (t.getJ() / (t.norm())), (t.getK() / (t.norm())));
	Vector bn((b.getI() / (b.norm())), (b.getJ() / (b.norm())), (b.getK() / (b.norm())));
	//sets the vector vn in the bottom equations
	vn = tn.cross(bn);
	//sets the vectors qx and qy based on bn and vn for the equations in 2.1
	Vector qx((((2 * gx) / (k - 1))*bn.getI()), (((2 * gx) / (k - 1))*bn.getJ()), (((2 * gx) / (k - 1))*bn.getK()));
	//std::cout << qx.getI() << qx.getJ() << qx.getK() << std::endl;

	Vector qy((((2 * gy) / (m - 1))*vn.getI()), (((2 * gy) / (m - 1))*vn.getJ()), (((2 * gy) / (m - 1))*vn.getK()));

	Vector tn_d(tn.getI()*d, tn.getJ()*d, tn.getK()*d);
	Vector bn_gx(bn.getI()*gx, bn.getJ()*gx, bn.getK()*gx);
	Vector vn_gy(vn.getI()*gy, vn.getJ()*gy, vn.getK()*gy);
	//sets the vector p1m in the equations on 2.1 to be used for the pixel loations
	Vector p1m((tn_d.sub(bn_gx)).sub(vn_gy));
	//std::cout << p1m.getI() << p1m.getJ() << p1m.getK() << std::endl;
	int ij = 0;
	for (int j = 1; j <= WIDTH; j++) {
		for (int i = 1; i <= HEIGHT; i++) {
			//sets the indexed incremented versions of qx and qy for the pixel equation
			Vector qy_ind(((qy.getI())*(j - 1)), ((qy.getJ())*(j - 1)), ((qy.getK())*(j - 1)));
			Vector qx_ind(((qx.getI())*(i - 1)), ((qx.getJ())*(i - 1)), ((qx.getK())*(i - 1)));
			//sets the pixel locations for the ray vector
			Vector pij = ((p1m.add(qx_ind)).add(qy_ind));
			//std::cout << pij.getI() << pij.getJ() << pij.getK() << std::endl;
				//gives the ray vetcor based on the top equation in 2.1
			Vector rij((pij.getI() / pij.norm()), (pij.getJ() / pij.norm()), (pij.getK() / pij.norm()));
			//sets the rays to be pushed into the view vector and creates the viewport vector
			view[ij] = rij;
			//std::cout << view[i - 1].getI() << view[i - 1].getJ() << view[i - 1].getK() << std::endl;
			ij += 1;
		}
	}
}

