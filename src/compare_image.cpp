#include "compare_image.h"

#include "exception.h"

#include <cstring>

bool compareImage(const Image& imageA, const Image& imageB)
{
    if (imageA.getHeight() != imageB.getHeight() ||
        imageA.getWidth() != imageB.getWidth())
    {
        return false;
    }

    auto res = std::memcmp(imageA.getData(), imageB.getData(), sizeof(uint32_t) * imageA.getHeight() * imageA.getWidth());

    return (res == 0);
}
