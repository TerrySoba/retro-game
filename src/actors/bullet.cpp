#include "bullet.h"

#include "png_image.h"

Bullet::Bullet() :
    m_image(new PngImage("assets/images/projectile.png")),
    m_pos(0,0)
{

}

void Bullet::setTrajectory(const Eigen::Vector2f &pos, const Eigen::Vector2f &speed)
{
    m_pos = pos;
    m_speed = speed;
}

Eigen::Vector2i Bullet::getPos()
{
    return m_pos.cast<int>();
}

std::shared_ptr<Image> Bullet::getImage()
{
    return m_image;
}

Rectangle Bullet::getBoundingBox()
{
    return Rectangle(m_pos[0], m_pos[1], m_image->getWidth(), m_image->getHeight());
}

void Bullet::init(EngineAccess &engine)
{
    // nothing
}

void Bullet::act(EngineAccess &engine)
{
    m_pos += m_speed;
}
