#include "catch/catch.hpp"

#include "rectangle.h"

TEST_CASE("Rectangle constructor")
{
    Rectangle r(1, 2, 3, 4);

    REQUIRE(r.getWidth() == 3);
    REQUIRE(r.getHeight() == 4);
    REQUIRE(r.getTopLeft().x == 1);
    REQUIRE(r.getTopLeft().y == 2);
    REQUIRE(r.getBottomRight().x == 4);
    REQUIRE(r.getBottomRight().y == 6);
}

