#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"


#include "main.h"
#include <iostream>
#include <string>

std::string TestParams::testDataDir;

std::string getTestDataDir(int argc, char* argv[])
{
    std::string testDataDir = "test/test_data/";

    for (int i = 0; i < argc; ++i)
    {
        std::string param(argv[i]);
        std::string parameterName = "--test-data-dir=";
        auto pos = param.find(parameterName, 0);

        if (pos != std::string::npos)
        {
            testDataDir = param.substr(pos + parameterName.size(), param.size() - parameterName.size() - pos);
        }

    }

    if (!testDataDir.empty())
    {
        if (testDataDir.back() != '/')
        {
            testDataDir += "/";
        }
    }

    return testDataDir;
}


int main(int argc, char* argv[])
{
    TestParams::testDataDir = getTestDataDir(argc, argv);

    std::cout << "TestDataDir: " << TestParams::testDataDir << std::endl;

    int result = Catch::Session().run( argc, argv );
    return ( result < 0xff ? result : 0xff );
}
