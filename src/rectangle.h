#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdint>

struct Point
{
    int32_t x;
    int32_t y;
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
        Point p;
        p.x = m_x;
        p.y = m_y;
        return p;
    }

    Point getBottomRight() const
    {
        Point p;
        p.x = m_x + m_width;
        p.y = m_y + m_height;
        return p;
    }

private:
    int32_t m_x;
    int32_t m_y;
    int32_t m_width;
    int32_t m_height;
};

#endif // RECTANGLE_H
