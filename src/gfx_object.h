#ifndef GFX_OBJECT_H
#define GFX_OBJECT_H

#include "image.h"
#include "rectangle.h"

#include <memory>

class GfxObject
{
public:
    virtual Point getPos() = 0;
    virtual std::shared_ptr<Image> getImage() = 0;
};


#endif // GFX_OBJECT_H
