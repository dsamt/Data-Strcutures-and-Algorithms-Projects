#ifndef _RAYTRACER_HPP_
#define _RAYTRACER_HPP_

#include <iostream>
#include <vector>

#include "Shape3D.hpp"
#include "Vector.hpp"

//width and height (in pixels) of our image (NOTE: these may change!)
// width := k and height := m
#define WIDTH  1024
#define HEIGHT 1024
//width and height (in coordinate system) of our veiwport (NOTE: these may change!)
// WARNING: HX/Y ratio should match the WIDTH/HEIGHT ratio
#define HX 5
#define HY 5

#define DEBUG false
#define DEBUG_VIEW false

/**
 * A simple ray tracer in C++: currently only supports one object in scene 
 */ 
class RayTracer
{
public:
  /**
   * Default constructor. should render a scene with default sphere, light source at (0,10,0), and camera at (5,0,0) with 
   * target at (0,0,0), and white background
   */ 
  RayTracer();
  
  /**
   * Use the parameters to set the scene components and render scene; use white background.
   * @param light - position (Vector w/r/t (0,0,0)) of light source
   * @param camera - position (Vector w/r/t (0,0,0)) of camera source
   * @param target - position (Vector w/r/t (0,0,0)) of target (where camera is looking)
   * @param shape - the shape we wish to render in the scene
   */
  RayTracer(Vector light, Vector camera, Vector target, const Shape3D& shape);
  
  /**
   * Create png of rendered scene with name of the file given by filename (use scene.png if filename is empty)
   * Required function: don't delete this (I wrote it for you); may need to modify it
   * @return whether was scene was successfully written to disk as .png
   */
  bool getScene(std::string filename); //write image of scene as <filename>.png

  /**
   * Create png of rendered scene with name of file `scene.png'
   * Required function: don't delete this (I wrote it for you); may need to modify it
   * @return whether was scene was successfully written to disk as .png
   */
  bool getScene(); //write image of scene as `scene.png'

  /**
   * Grading function: allow access to private data to compare view rays with reference
   * @return address of the vector holding the view rays
   */
  std::vector<Vector>& getView();

  /**
   * Grading function: allow access to private data to compare pixel values with reference
   * @return a pointer to the vector holding the pixels
   */
  std::vector<unsigned char>& getPixels();
  

private:
  std::vector<Vector> view = std::vector<Vector>(WIDTH*HEIGHT); //normalized vectors leaving our camera
  std::vector<unsigned char> pixels = std::vector<unsigned char>(4*WIDTH*HEIGHT); //RGBA values for each pixel in image
  bool FIN; //set to true if scene has been rendered
  
  /**
   * Establish normalized vector from camera/eye to image plane (we will use these vectors to determine intersection with the shape)
   */
  void genView(const Vector& camera, const Vector& target);
};
#endif
