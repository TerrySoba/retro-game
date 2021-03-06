#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "retrogame_export.h"

#include "Eigen/Core"

#include <cstdint>

class RETROGAME_EXPORT MyRectangle
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
    MyRectangle(int32_t x, int32_t y, int32_t width, int32_t height);

    int32_t getWidth() const
    {
        return m_width;
    }

    int32_t getHeight() const
    {
        return m_height;
    }

    Eigen::Vector2i getTopLeft() const
    {
        return Eigen::Vector2i(m_x, m_y);
    }

    Eigen::Vector2i getBottomRight() const
    {
        return Eigen::Vector2i(m_x + m_width, m_y + m_height);
    }

    MyRectangle intersection(const MyRectangle& other) const;

    int32_t area()
    {
        // width and height are always positive!
        return m_width * m_height;
    }

    bool empty()
    {
        return (m_width == 0 || m_height == 0);
    }

private:
    int32_t m_x;
    int32_t m_y;
    int32_t m_width;
    int32_t m_height;
};

#endif // RECTANGLE_H
