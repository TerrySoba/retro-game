#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdint>

struct Point
{
    Point(auto _x, auto _y) : x(_x), y(_y) {}
    Point() {}
    int32_t x = 0;
    int32_t y = 0;
};

class Rectangle
{
public:
    /**
     * Creates a rectangle with given dimensions.
     *
     * @param x x coordinate of top left corner
     * @param y y coordinate of top left corner
     * @param width width of rectangle
     * @param height height of rectangle
     */
    Rectangle(int32_t x, int32_t y, int32_t width, int32_t height);

    int32_t getWidth() const
    {
        return m_width;
    }

    int32_t getHeight() const
    {
        return m_height;
    }

    Point getTopLeft() const
    {
        return Point(m_x, m_y);
    }

    Point getBottomRight() const
    {
        return Point(m_x + m_width, m_y + m_height);
    }

    Rectangle intersection(const Rectangle& other) const;


private:
    int32_t m_x;
    int32_t m_y;
    int32_t m_width;
    int32_t m_height;
};

#endif // RECTANGLE_H
