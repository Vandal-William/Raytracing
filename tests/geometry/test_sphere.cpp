#include <catch2/catch_test_macros.hpp>

#include "geometry/sphere.h"
#include "test_helpers.h"

TEST_CASE("a ray hits a sphere centred on its axis", "[sphere]") {
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    REQUIRE(sphere.isHitBy(testCameraRay()));
}

TEST_CASE("a ray hits a sphere off its axis", "[sphere]") {
    Sphere sphere(Vector(3, 0, 9), 5, Colour(1, 0, 0));
    REQUIRE(sphere.isHitBy(testCameraRay()));
}

TEST_CASE("a ray misses a sphere too far off axis", "[sphere]") {
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));
    REQUIRE_FALSE(sphere.isHitBy(testCameraRay()));
}

TEST_CASE("a sphere behind the eye is not hit", "[sphere]") {
    Sphere sphere(Vector(0, 0, -11), 5, Colour(1, 0, 0));
    REQUIRE_FALSE(sphere.isHitBy(testCameraRay()));
}

TEST_CASE("a sphere gives back its colour", "[sphere]") {
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    requireColoursEqual(sphere.colour(), Colour(1, 0, 0));
}
