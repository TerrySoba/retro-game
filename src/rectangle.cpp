#include "rectangle.h"

Rectangle::Rectangle(int32_t x, int32_t y, int32_t width, int32_t height) :
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height)
{
}

Rectangle Rectangle::intersection(const Rectangle& other) const
{
    return Rectangle(1,2,3,4);
}
