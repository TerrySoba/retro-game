#ifndef PNG_IMAGE_H
#define PNG_IMAGE_H

#include "image.h"

#include <string>
#include <vector>

class PngImage : public Image
{
public:
    PngImage(const std::string& filename);

    virtual uint32_t* getData() override;
    virtual uint32_t getWidth() override;
    virtual uint32_t getHeight() override;

public:
    // raw image data
    std::vector<uint8_t> m_imageData;

    // dimensions of image in pixels
    uint32_t m_width;
    uint32_t m_height;
};

#endif // PNG_IMAGE_H
