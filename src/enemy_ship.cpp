#include "enemy_ship.h"

#include "exception.h"

#include <cmath>

EnemyShip::EnemyShip(std::shared_ptr<Image> image) :
    m_image(image),
    m_pos(0,0)
{
    if (!image)
    {
        throw Exception("Image pointer is invalid.");
    }
}

void EnemyShip::setInitialPos(const Point& pos)
{
    m_pos = pos;
}

Point EnemyShip::getPos()
{
    auto s = std::sin(m_actCounter / 50.0);
    s *= s;

    return Point(m_pos.x + s * 150.0, m_pos.y);
}

std::shared_ptr<Image> EnemyShip::getImage()
{
    return m_image;
}

Rectangle EnemyShip::getBoundingBox()
{
    return Rectangle(m_pos.x, m_pos.y, m_image->getWidth(), m_image->getHeight());
}

void EnemyShip::act()
{
    m_actCounter++;
}
