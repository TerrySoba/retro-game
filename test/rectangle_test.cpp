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

TEST_CASE("Intersection is Commutative")
{
    Rectangle r1(0, 0, 100, 100);
    Rectangle r2(-10, -20, 40, 40);

    auto inter1 = r1.intersection(r2);
    auto inter2 = r2.intersection(r1);

    REQUIRE(inter1.getWidth() == inter2.getWidth());
    REQUIRE(inter1.getHeight() == inter2.getHeight());
    REQUIRE(inter1.getTopLeft().x == inter2.getTopLeft().x);
    REQUIRE(inter1.getTopLeft().y == inter2.getTopLeft().y);
}



TEST_CASE("Intersection tests")
{
    Rectangle r1(0, 0, 100, 100);


    SECTION("r2 is top left of r1")
    {
        Rectangle r2(-10, -20, 40, 40);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 30);
        REQUIRE(inter.getHeight() == 20);
        REQUIRE(inter.getTopLeft().x == 0);
        REQUIRE(inter.getTopLeft().y == 0);
    }

    SECTION("r2 is bottom left of r1, no intersection")
    {
        Rectangle r2(-20, 110, 40, 40);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 0);
        REQUIRE(inter.getHeight() == 0);
        REQUIRE(inter.getTopLeft().x == 0);
        REQUIRE(inter.getTopLeft().y == 0);
    }

    SECTION("r2 is inside of r1")
    {
        Rectangle r2(20, 30, 10, 20);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 10);
        REQUIRE(inter.getHeight() == 20);
        REQUIRE(inter.getTopLeft().x == 20);
        REQUIRE(inter.getTopLeft().y == 30);
    }

    SECTION("r2 overlaps with bottom of r1")
    {
        Rectangle r2(20, 30, 10, 200);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 10);
        REQUIRE(inter.getHeight() == 70);
        REQUIRE(inter.getTopLeft().x == 20);
        REQUIRE(inter.getTopLeft().y == 30);
    }

    SECTION("r2 forms a cross with r1")
    {
        Rectangle r2(-10, 10, 200, 10);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 100);
        REQUIRE(inter.getHeight() == 10);
        REQUIRE(inter.getTopLeft().x == 0);
        REQUIRE(inter.getTopLeft().y == 10);
    }

}

