#ifndef MEMORY_IMAGE_H
#define MEMORY_IMAGE_H

#include "image.h"
#include "retrogame_export.h"

#include <vector>

class RETROGAME_EXPORT MemoryImage : public Image
{
public:
    MemoryImage(uint32_t width, uint32_t height);
    virtual uint32_t* getData() override;
    virtual const uint32_t* getData() const override;
    virtual uint32_t getWidth() const override;
    virtual uint32_t getHeight() const override;

public:
    uint32_t m_width;
    uint32_t m_height;
    std::vector<uint32_t> m_data;
};

#endif // MEMORY_IMAGE_H
