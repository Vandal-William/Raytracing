#include <catch2/catch_test_macros.hpp>

#include "colour/colour.h"

TEST_CASE("Colour gives back r, g and b", "[colour]") {
    Colour colour(1, 0.5, 0);

    REQUIRE(colour.r() == 1);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0);
}
