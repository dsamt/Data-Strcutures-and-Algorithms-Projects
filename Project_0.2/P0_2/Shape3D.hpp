#ifndef _SHAPE3D_HPP_
#define _SHAPE3D_HPP_

#include <iostream>

#include "Vector.hpp"

class Shape3D
{
public:
  /** 
   * The color of the shape
   * @return color shape: order is rgba with rgb in the interval [0,255] and a = 255;
   */
  virtual std::vector<unsigned char> color() const = 0;

  /** 
   * The position of the shape
   * @return position of shape (center) w/r/t Vector(0,0,0)
   */
  virtual Vector position() const = 0;

  /** 
   * The ambient of the shape
   * @return ambience of shape on the interval [0,1]
   */
  virtual double ambient() const = 0;

  /** 
   * The position (as a Vector w/r/t Vector(0,0,0)) at which the unit vector d, originating from s, would or would not intersect with the shape
   * @return position at which user-supplied vector intersects with the shape (Vector(INFINITY, INFINITY, INFINITY) if no intersection)
   */
  virtual Vector intersect(const Vector& s, const Vector& d) const = 0;

  /** 
   * The (unit) normal vector of the shape at the user supplied position on the surface of the shape (as a Vector w/r/t Vector(0,0,0))
   * @return vector normal to the shape's surface at user-supplied position (Vector(INFINITY, INFINITY, INFINITY) if no normal available)
   */
  virtual Vector normal(const Vector& pos) const = 0;
};

#endif
