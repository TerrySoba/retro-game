#ifndef ANIMATION_H
#define ANIMATION_H

#include "exception.h"
#include "png_image.h"

#include "fmt/format.h"

#include <string>
#include <vector>
#include <iostream>

class Animation : public Image
{
public:
    Animation(const std::string& directory, uint32_t start, uint32_t stop)
    {
        for (uint32_t i = start; i <= stop; ++i)
        {
            auto path = fmt::format("{}{:04}.png", directory, i);
            std::cout << path << std::endl;
            m_images.emplace_back(path);
        }

        if (m_images.empty())
        {
            throw Exception("Too few images in animation.");
        }
    }

    void setFrame(uint32_t frame)
    {
        m_currentFrame = frame;
    }

    virtual uint32_t* getData()
    {
        return m_images[m_currentFrame % m_images.size()].getData();
    }

    virtual uint32_t getWidth()
    {
        return m_images[m_currentFrame % m_images.size()].getWidth();
    }

    virtual uint32_t getHeight()
    {
        return m_images[m_currentFrame % m_images.size()].getHeight();
    }

private:
    std::vector<PngImage> m_images;
    uint32_t m_currentFrame = 0;
};



#endif // ANIMATION_H
