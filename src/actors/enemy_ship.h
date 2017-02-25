#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

#include "actor.h"
#include "image.h"

#include "Eigen/Core"

class EnemyShip : public Actor
{
public:
    EnemyShip(std::shared_ptr<Image> image);

    void setInitialPos(const Eigen::Vector2i& pos);

    // GfxObject interface
public:
    Eigen::Vector2i getPos() override;
    std::shared_ptr<Image> getImage() override;

    // Actor interface
public:
    Rectangle getBoundingBox() override;
    void act(EngineAccess& engine) override;


private:
    std::shared_ptr<Image> m_image;
    Eigen::Vector2f m_pos;

    size_t m_actCounter = 0;

};

#endif // ENEMY_SHIP_H
