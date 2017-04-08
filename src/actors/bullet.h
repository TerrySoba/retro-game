#ifndef BULLET_H
#define BULLET_H

#include "actor.h"

class Bullet : public Actor
{
public:
    Bullet();

    void setTrajectory(const Eigen::Vector2f& pos, const Eigen::Vector2f& speed);

    // GfxObject interface
public:
    Eigen::Vector2i getPos() override;
    std::shared_ptr<Image> getImage() override;

    // Actor interface
public:
    MyRectangle getBoundingBox() override;
    void init(EngineAccess &engine) override;
    void act(EngineAccess &engine) override;

private:
    std::shared_ptr<Image> m_image;
    Eigen::Vector2f m_pos;
    Eigen::Vector2f m_speed;
};

#endif // BULLET_H
