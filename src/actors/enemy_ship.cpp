#include "actors/enemy_ship.h"

#include "exception.h"
#include "engine_access.h"

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

void EnemyShip::setInitialPos(const Eigen::Vector2i& pos)
{
    m_pos = pos.cast<float>();
}

Eigen::Vector2i EnemyShip::getPos()
{
    auto s = std::sin(m_actCounter / 50.0);
    s *= s;

    Eigen::Vector2i wobble(s * 30, 0);


    return m_pos.cast<int>() + wobble;
}

std::shared_ptr<Image> EnemyShip::getImage()
{
    return m_image;
}

Rectangle EnemyShip::getBoundingBox()
{
    auto pos = getPos();
    return Rectangle(pos[0], pos[1], m_image->getWidth(), m_image->getHeight());
}

void EnemyShip::act(EngineAccess& engine)
{
    auto player = engine.getActorByName("ThePlayer");
    auto intersection = player->getBoundingBox().intersection(getBoundingBox());

    // find direction to player ship
    Eigen::Vector2f direction = (player->getPos() - getPos()).cast<float>();

    direction.normalize();

    if (intersection.area() == 0)
    {
        m_pos += direction * 0.5;
    }

    m_actCounter++;
}

