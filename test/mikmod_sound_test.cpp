#include "catch/catch.hpp"

#include "mikmod_sound.h"
#include "main.h"
#include "exception.h"
#include "stdio.h"

std::vector<uint8_t> loadFromFile(const std::string& filePath)
{
    auto f = fopen(filePath.c_str(), "rb");
    if (!f) return std::vector<uint8_t>();
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);
    std::vector<uint8_t> data(fsize);
    auto bytesRead = fread(data.data(), fsize, 1, f);
    data.resize(bytesRead);
    fclose(f);
    return data;
}

TEST_CASE("MikmodSoundTest")
{
    MikmodSound sound;

    SECTION("Exception on non existing file")
    {
        REQUIRE_THROWS_AS(sound.playModule("non_existing_file.xm");, Exception);
        REQUIRE_THROWS_AS(sound.loadSample("non_existing_file.wav");, Exception);
    }

    SECTION("Check rendered music output")
    {
        sound.playModule(TestParams::testDataDir + "test_music.xm");
        size_t frames = 1000;
        std::vector<uint8_t> data(frames * 4);
        sound.renderAudioFrames(frames, data.data());

        // auto fp = fopen("test_music_render.raw", "wb");
        // REQUIRE(fp != nullptr);

        // fwrite(data.data(), 1, data.size(), fp);
        // fclose(fp);

        // auto refData = loadFromFile(TestParams::testDataDir + "test_music_render.raw");
        // REQUIRE(refData == data);
		// @todo check against reference
    }

    SECTION("Play invalid sample")
    {
        REQUIRE_THROWS_AS(sound.playSample(0);, Exception);
        REQUIRE_THROWS_AS(sound.playSample(10);, Exception);
        REQUIRE_THROWS_AS(sound.playSample(100000);, Exception);
    }

    SECTION("Play Samples")
    {
        auto id = sound.loadSample(TestParams::testDataDir + "sample.wav");
        sound.playSample(id);
        size_t frames = 1000;
        std::vector<uint8_t> data(frames * 4);
        sound.renderAudioFrames(frames, data.data());

        //@todo check against reference
    }
}
