#include "catch/catch.hpp"

#include "compare_image.h"
#include "memory_image.h"

void fillImage(Image& img, uint32_t color)
{
    auto data = img.getData();
    for (size_t i = 0; i < img.getHeight() * img.getWidth(); ++i)
    {
        data[i] = color;
    }
}

TEST_CASE("CompareImageTestContent")
{
    MemoryImage imageA(2,2);
    fillImage(imageA, 0);

    MemoryImage imageB(2,2);
    fillImage(imageB, 0);

    REQUIRE(compareImage(imageA, imageB) == true);
    REQUIRE(compareImage(imageB, imageA) == true);

    imageB.getData()[1] = 1;

    REQUIRE(compareImage(imageA, imageB) == false);
    REQUIRE(compareImage(imageB, imageA) == false);
}

TEST_CASE("CompareImageTestSizeX")
{
    MemoryImage imageA(3,2);
    fillImage(imageA, 0);

    MemoryImage imageB(2,2);
    fillImage(imageB, 0);

    REQUIRE(compareImage(imageA, imageB) == false);
    REQUIRE(compareImage(imageB, imageA) == false);
}

TEST_CASE("CompareImageTestSizeY")
{
    MemoryImage imageA(2,2);
    fillImage(imageA, 0);

    MemoryImage imageB(2,3);
    fillImage(imageB, 0);

    REQUIRE(compareImage(imageA, imageB) == false);
    REQUIRE(compareImage(imageB, imageA) == false);
}

