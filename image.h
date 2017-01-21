#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

class Image
{
public:
    virtual uint32_t* getData() = 0;
    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;
};


#endif // IMAGE_H
