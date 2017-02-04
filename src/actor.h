#ifndef ACTOR_H
#define ACTOR_H

#include "gfx_object.h"

class Actor : public GfxObject
{
public:
    /**
     * This method returns the bounding box of the Actor.
     *
     * Be aware that the bounding box may not be the same
     * as the position and the size of the image that
     * represents the actor.
     *
     * \sa getPos() \sa getImage()
     */
    virtual Rectangle getBoundingBox() = 0;

    /**
     * Each time this method is called the actor may act.
     *
     * The idea is that the actor may change it's position,
     * bounding box or even it's image.
     */
    virtual void act() = 0;
};

#endif // ACTOR_H
