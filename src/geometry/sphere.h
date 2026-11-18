#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "math/vector.h"

class Sphere {
  public:
    Sphere(const Vector& centre, double radius, const Colour& colour);

    bool isHitBy(const Ray& ray) const;
    Colour colour() const;

  private:
    Vector _centre;
    double _radius;
    Colour _colour;
};
