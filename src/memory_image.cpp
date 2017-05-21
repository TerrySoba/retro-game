#include "memory_image.h"

MemoryImage::MemoryImage(uint32_t width, uint32_t height) :
    m_width(width),
    m_height(height),
    m_data(width * height)
{
}

uint32_t* MemoryImage::getData()
{
    return m_data.data();
}

uint32_t MemoryImage::getWidth()
{
    return m_width;
}

uint32_t MemoryImage::getHeight()
{
    return m_height;
}
