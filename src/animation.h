#ifndef ANIMATION_H
#define ANIMATION_H

#include "retrogame_export.h"

#include "exception.h"
#include "png_image.h"

#include "fmt/format.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

std::map<int, std::string> RETROGAME_EXPORT getAnimationFilenames(const std::string& filename);

class RETROGAME_EXPORT Animation : public Image
{
public:
    Animation(const std::string& globName);

    void setFrame(uint32_t frame);
    uint32_t getFrameCount();

    virtual uint32_t* getData() override;
    virtual const uint32_t* getData() const override;
    virtual uint32_t getWidth() const override;
    virtual uint32_t getHeight() const override;

private:
    std::vector<PngImage> m_images;
    uint32_t m_currentFrame = 0;
};

#endif // ANIMATION_H
