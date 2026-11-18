#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "math/vector.h"

extern const double tolerance;

void requireVectorsEqual(const Vector& actual, const Vector& expected);
void requireColoursEqual(const Colour& actual, const Colour& expected);

// The ray our test camera casts through the centre of its screen:
// eye at (0, 0, -1), screen centre at (0, 0, 0).
Ray testCameraRay();
