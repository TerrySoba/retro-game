#ifndef ACTOR_H
#define ACTOR_H

#include "gfx_object.h"

class Actor : public GfxObject
{
public:
    Rectangle getBoundingBox();
    void act();
};

#endif // ACTOR_H
