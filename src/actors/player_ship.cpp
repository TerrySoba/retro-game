#include "actors/player_ship.h"

#include "gfx_engine.h"
#include "bullet.h"
#include "exception.h"

PlayerShip::PlayerShip(std::shared_ptr<Image> image, Eigen::Vector2i initialPos) :
    m_image(image),
    m_pos(initialPos)
{
}

Eigen::Vector2i PlayerShip::getPos()
{
    return m_pos;
}

std::shared_ptr<Image> PlayerShip::getImage()
{
    return m_image;
}

void PlayerShip::leftPressed()
{
    m_deltaX -= 2;
}

void PlayerShip::leftReleased()
{
    m_deltaX += 2;
}

void PlayerShip::rightPressed()
{
    m_deltaX += 2;
}

void PlayerShip::rightReleased()
{
    m_deltaX -= 2;
}

void PlayerShip::upPressed()
{
    m_deltaY -= 2;
}

void PlayerShip::upReleased()
{
    m_deltaY += 2;
}

void PlayerShip::downPressed()
{
    m_deltaY += 2;
}

void PlayerShip::downReleased()
{
    m_deltaY -= 2;
}

void PlayerShip::buttonPressed()
{
    if (m_bullet)
    {
        auto bullet = std::dynamic_pointer_cast<Bullet>(m_bullet);
        if (bullet)
        {
            auto boundingBox = getBoundingBox();
            Eigen::Vector2f shipPosMiddle =
                    boundingBox.getTopLeft().cast<float>() +
                    Eigen::Vector2f(boundingBox.getWidth() / 2.0, 0);

            auto bulletBoundingBox = m_bullet->getBoundingBox();

            Eigen::Vector2f bulletCenterOffset(-bulletBoundingBox.getWidth() / 2.0,0);


            bullet->setTrajectory(shipPosMiddle + bulletCenterOffset, {0,-5});
        }
    }
}

void PlayerShip::buttonReleased()
{

}

MyRectangle PlayerShip::getBoundingBox()
{
    return MyRectangle(m_pos[0], m_pos[1], m_image->getWidth(), m_image->getHeight());
}

void PlayerShip::init(EngineAccess &engine)
{
    m_bullet = engine.getActorByName("Bullet");
    if (!m_bullet)
    {
        throw Exception("Did not find actor named \"Bullet\".");
    }
}

void PlayerShip::act(EngineAccess& engine)
{
    m_pos[0] += m_deltaX;
    m_pos[1] += m_deltaY;
}
