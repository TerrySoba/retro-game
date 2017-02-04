#ifndef GFX_OBJECT_H
#define GFX_OBJECT_H

#include "image.h"
#include "rectangle.h"

#include <memory>

class GfxObject
{
public:
    /**
     * Returns the position of the top left corner of the GfxObject.
     */
    virtual Point getPos() = 0;

    /**
     * Returns the image that should be shown to represent this GfxObject.
     */
    virtual std::shared_ptr<Image> getImage() = 0;
};


#endif // GFX_OBJECT_H
