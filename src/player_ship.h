#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "actor.h"
#include "input_listener.h"

class PlayerShip : public Actor, public InputListener
{
public:
    PlayerShip(std::shared_ptr<Image> image, Point initialPos);

    // GfxObject interface
public:
    Point getPos() override;
    std::shared_ptr<Image> getImage() override;

    // InputListener interface
public:
    void leftPressed() override;
    void leftReleased() override;
    void rightPressed() override;
    void rightReleased() override;
    void upPressed() override;
    void upReleased() override;
    void downPressed() override;
    void downReleased() override;
    void buttonPressed() override;
    void buttonReleased() override;

    // Actor interface
public:
    Rectangle getBoundingBox() override;
    void act(EngineAccess& engine) override;


private:
    std::shared_ptr<Image> m_image;
    Point m_pos;

    int32_t m_deltaX = 0;
    int32_t m_deltaY = 0;

};

#endif // PLAYER_SHIP_H
