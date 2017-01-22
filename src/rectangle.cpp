#include "rectangle.h"

#include <algorithm>

Rectangle::Rectangle(int32_t x, int32_t y, int32_t width, int32_t height) :
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height)
{
    // check if rectangle is normalized and correct if needed
    if (width < 0)
    {
        m_x += m_width;
        m_width = -m_width;
    }
    if (height < 0)
    {
        m_y += m_height;
        m_height = -m_height;
    }
}

Rectangle Rectangle::intersection(const Rectangle& other) const
{
    auto x1 = m_x;
    auto y1 = m_y;
    auto x2 = m_x + m_width;
    auto y2 = m_y + m_height;

    auto x3 = other.m_x;
    auto y3 = other.m_y;
    auto x4 = other.m_x + other.m_width;
    auto y4 = other.m_y + other.m_height;

    // code thanks to http://stackoverflow.com/a/19754915
    auto x5 = std::max(x1, x3);
    auto y5 = std::max(y1, y3);
    auto x6 = std::min(x2, x4);
    auto y6 = std::min(y2, y4);

    // check if rectangles actually intersected
    if (x5 >= x6 || y5 >= y6)
    {
        return Rectangle(0,0,0,0);
    }
    else
    {
        return Rectangle(x5, y5, x6 - x5, y6 - y5);
    }
}
