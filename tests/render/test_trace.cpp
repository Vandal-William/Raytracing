#include <catch2/catch_test_macros.hpp>

#include "render/trace.h"
#include "test_helpers.h"

TEST_CASE("trace gives the sphere's colour when the ray hits it", "[trace]") {
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    requireColoursEqual(trace(testCameraRay(), sphere), Colour(1, 0, 0));
}

TEST_CASE("trace gives black when the ray misses", "[trace]") {
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));
    requireColoursEqual(trace(testCameraRay(), sphere), Colour(0, 0, 0));
}
