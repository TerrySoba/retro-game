#include "catch/catch.hpp"

#include "paint_surface.h"
#include "png_image.h"
#include "compare_image.h"
#include "main.h"

TEST_CASE("Paint Surface DrawImage1")
{
    {
        PngImage image1(TestParams::testDataDir + "rgb_testimage_2x2.png");
        PngImage image2(TestParams::testDataDir + "testimage_3x7.png");
        PngImage image3(TestParams::testDataDir + "draw_result1.png");

        PaintSurface surf(image2);
        surf.drawImage(image1, 1, 2);

        REQUIRE(compareImage(image2, image3) == true);
    }

    {
        PngImage image1(TestParams::testDataDir + "rgb_testimage_2x2.png");
        PngImage image2(TestParams::testDataDir + "testimage_3x7.png");
        PngImage image3(TestParams::testDataDir + "draw_result1.png");

        PaintSurface surf(image2);
        // surf.drawImage(image1, 1, 2);
        surf.drawImage(image1, 0, 0, image1.getWidth(), image1.getHeight(), 1, 2);

        REQUIRE(compareImage(image2, image3) == true);
    }
}

TEST_CASE("Paint Surface DrawImage2")
{
    PngImage image1(TestParams::testDataDir + "rgb_testimage_2x2.png");
    PngImage image2(TestParams::testDataDir + "testimage_3x7.png");
    PngImage image3(TestParams::testDataDir + "draw_result2.png");

    PaintSurface surf(image2);
    surf.drawImage(image1,
                   1, 0, // source pos
                   1, 2, // source size
                   1, 5); // target pos

    REQUIRE(compareImage(image2, image3) == true);
}



