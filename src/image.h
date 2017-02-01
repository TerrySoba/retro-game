#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

/**
 * Base class for images.
 *
 * The image format is XRGB that means that each pixel is 32bits wide.
 * The first byte is ignored (X) the follwing bytes represent red (R),
 * green (G) and blue (B).
 *
 * Images begin at the top left corner.
 */
class Image
{
public:
    virtual uint32_t* getData() = 0;
    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;
};


#endif // IMAGE_H
