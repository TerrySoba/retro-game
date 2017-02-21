#include "player_ship.h"

PlayerShip::PlayerShip(std::shared_ptr<Image> image, Point initialPos) :
    m_image(image),
    m_pos(initialPos)
{
}

Point PlayerShip::getPos()
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

}

void PlayerShip::buttonReleased()
{

}

Rectangle PlayerShip::getBoundingBox()
{
    return Rectangle(m_pos.x, m_pos.y, m_image->getWidth(), m_image->getHeight());
}

void PlayerShip::act(EngineAccess& engine)
{
    m_pos.x += m_deltaX;
    m_pos.y += m_deltaY;
}
