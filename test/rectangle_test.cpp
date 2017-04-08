#include "catch/catch.hpp"

#include "rectangle.h"

TEST_CASE("Rectangle constructor")
{
    MyRectangle r(1, 2, 3, 4);

    REQUIRE(r.getWidth() == 3);
    REQUIRE(r.getHeight() == 4);
    REQUIRE(r.getTopLeft()[0] == 1);
    REQUIRE(r.getTopLeft()[1] == 2);
    REQUIRE(r.getBottomRight()[0] == 4);
    REQUIRE(r.getBottomRight()[1] == 6);
}

TEST_CASE("Intersection is Commutative")
{
    MyRectangle r1(0, 0, 100, 100);
    MyRectangle r2(-10, -20, 40, 40);

    auto inter1 = r1.intersection(r2);
    auto inter2 = r2.intersection(r1);

    REQUIRE(inter1.getWidth() == inter2.getWidth());
    REQUIRE(inter1.getHeight() == inter2.getHeight());
    REQUIRE(inter1.getTopLeft() == inter2.getTopLeft());
}

TEST_CASE("Intersection tests")
{
    MyRectangle r1(0, 0, 100, 100);


    SECTION("r2 is top left of r1")
    {
        MyRectangle r2(-10, -20, 40, 40);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 30);
        REQUIRE(inter.getHeight() == 20);
        REQUIRE(inter.getTopLeft()[0] == 0);
        REQUIRE(inter.getTopLeft()[1] == 0);
    }

    SECTION("r2 is bottom left of r1, no intersection")
    {
        MyRectangle r2(-20, 110, 40, 40);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 0);
        REQUIRE(inter.getHeight() == 0);
        REQUIRE(inter.getTopLeft()[0] == 0);
        REQUIRE(inter.getTopLeft()[1] == 0);
    }

    SECTION("r2 is inside of r1")
    {
        MyRectangle r2(20, 30, 10, 20);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 10);
        REQUIRE(inter.getHeight() == 20);
        REQUIRE(inter.getTopLeft()[0] == 20);
        REQUIRE(inter.getTopLeft()[1] == 30);
    }

    SECTION("r2 overlaps with bottom of r1")
    {
        MyRectangle r2(20, 30, 10, 200);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 10);
        REQUIRE(inter.getHeight() == 70);
        REQUIRE(inter.getTopLeft()[0] == 20);
        REQUIRE(inter.getTopLeft()[1] == 30);
    }

    SECTION("r2 forms a cross with r1")
    {
        MyRectangle r2(-10, 10, 200, 10);
        auto inter = r1.intersection(r2);
        REQUIRE(inter.getWidth() == 100);
        REQUIRE(inter.getHeight() == 10);
        REQUIRE(inter.getTopLeft()[0] == 0);
        REQUIRE(inter.getTopLeft()[1] == 10);
    }
}


TEST_CASE("Check rectangle normalization")
{
    MyRectangle r1(0, 0, -13, -17);
    REQUIRE(r1.getWidth() == 13);
    REQUIRE(r1.getHeight() == 17);
    REQUIRE(r1.getTopLeft()[0] == -13);
    REQUIRE(r1.getTopLeft()[1] == -17);
}

TEST_CASE("equal rectangles")
{
    MyRectangle r1(0, 0, 100, 100);
    MyRectangle r2(0, 0, 100, 100);

    auto inter = r1.intersection(r2);

    REQUIRE(inter.getWidth() == r1.getWidth());
    REQUIRE(inter.getHeight() == r1.getHeight());
    REQUIRE(inter.getTopLeft() == r1.getTopLeft());
}

TEST_CASE("rectangle area")
{
    MyRectangle r1(0, 0, 100, 100);
    REQUIRE(r1.area() == 100*100);

    MyRectangle r2(0, 0, -100, 100);
    REQUIRE(r2.area() == 100*100);

    MyRectangle r3(0, 0, 100, -100);
    REQUIRE(r3.area() == 100*100);

    MyRectangle r4(0, 0, -100, -100);
    REQUIRE(r4.area() == 100*100);
}

