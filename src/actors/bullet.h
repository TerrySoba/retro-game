#ifndef BULLET_H
#define BULLET_H

#include "actor.h"

class Bullet : public Actor
{
public:
    Bullet();

    // GfxObject interface
public:
    Eigen::Vector2i getPos();
    std::shared_ptr<Image> getImage();

    // Actor interface
public:
    Rectangle getBoundingBox();
    void act(EngineAccess &engine);
};

#endif // BULLET_H
