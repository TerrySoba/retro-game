#ifndef PNG_IMAGE_H
#define PNG_IMAGE_H

#include "retrogame_export.h"
#include "image.h"

#include <string>
#include <vector>

class RETROGAME_EXPORT PngImage : public Image
{
public:
    PngImage(const std::string& filename);

    virtual uint32_t* getData() override;
    virtual const uint32_t* getData() const override;
    virtual uint32_t getWidth() const override;
    virtual uint32_t getHeight() const override;

private:
    // raw image data
    std::vector<uint8_t> m_imageData;

    // dimensions of image in pixels
    uint32_t m_width;
    uint32_t m_height;
};

#endif // PNG_IMAGE_H
