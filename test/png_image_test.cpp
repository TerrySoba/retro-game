#include "catch/catch.hpp"

#include "png_image.h"
#include "main.h"
#include "exception.h"

TEST_CASE("Load Failure Test")
{
    REQUIRE_THROWS_AS(PngImage image("non_existing_file.png");, Exception);
}

TEST_CASE("Load Test Image")
{
    PngImage image(TestParams::testDataDir + "rgb_testimage_2x2.png");

    REQUIRE(image.getHeight() == 2);
    REQUIRE(image.getWidth() == 2);
    REQUIRE(image.getData()[0] == 0x00FF0000); // red pixel
    REQUIRE(image.getData()[1] == 0x0000FF00); // green pixel
    REQUIRE(image.getData()[2] == 0x000000FF); // blue pixel
    REQUIRE(image.getData()[3] == 0x00FFFFFF); // white pixel
}

TEST_CASE("Check Dimensions")
{
    PngImage image(TestParams::testDataDir + "testimage_3x7.png");
    REQUIRE(image.getHeight() == 7);
    REQUIRE(image.getWidth() == 3);
}
