#include "catch/catch.hpp"

#include "animation.h"
#include "main.h"

// for rgb() function
#include "paint_surface.h"

TEST_CASE("Animation File Not Found")
{
    REQUIRE_THROWS_AS(Animation a("unknown-file-name");, Exception);
}

TEST_CASE("Animation Test")
{
    for (std::string filename : {"rgb_anim_*.png", "rgb_anim_b_*.png"})
    {
        Animation a(TestParams::testDataDir + "/animation_test/" + filename);

        REQUIRE(a.getFrameCount() == 3);

        {
            a.setFrame(0);
            auto pixel = *a.getData();
            REQUIRE(pixel == rgb(255, 0, 0));
        }
        {
            a.setFrame(1);
            auto pixel = *a.getData();
            REQUIRE(pixel == rgb(0, 255, 0));
        }
        {
            a.setFrame(2);
            auto pixel = *a.getData();
            REQUIRE(pixel == rgb(0, 0, 255));
        }
    }
}


TEST_CASE("Filesystem Stuff")
{
    auto filenames = getAnimationFilenames(TestParams::testDataDir + "/animation_test/rgb_anim_*.png");
    REQUIRE(filenames.size() == 3);
    REQUIRE(filenames.at(1) == TestParams::testDataDir + "/animation_test/rgb_anim_1.png");
    REQUIRE(filenames.at(2) == TestParams::testDataDir + "/animation_test/rgb_anim_2.png");
    REQUIRE(filenames.at(3) == TestParams::testDataDir + "/animation_test/rgb_anim_3.png");
}
