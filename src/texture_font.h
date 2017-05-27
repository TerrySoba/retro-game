/*
 * TextureFont.h
 *
 *  Created on: 27.03.2012
 *      Author: yoshi252
 */

#ifndef TEXTUREFONT_H_
#define TEXTUREFONT_H_

#include "paint_surface.h"
#include "image.h"

#include <map>
#include <vector>
#include <cstdint>
#include <memory>

struct CharacterInformation {
    uint32_t unicode;
    int32_t bearingLeft;
    int32_t bearingTop;
    double horiAdvance;
    double vertAdvance;
    int32_t imageLeft;
    int32_t imageTop;
    uint32_t imageWidth;
    uint32_t imageHeight;
};

class TextureFont {
public:
    TextureFont();
    virtual ~TextureFont();

    bool load(const std::string& path);

    std::shared_ptr<Image> getImage() { return m_image; }

    bool hasCharacter(uint32_t unicode);
    CharacterInformation* getCharacter(uint32_t unicode);

    /**
     * Renders the given text to the given surface at the given position (x,y).
     *
     * @param surface The Surface to render to.
     * @param x The x position of the text.
     * @param y The y position of the text.
     * @param text The utf8 encoded text.
     */
    void renderToImage(PaintSurface& surface, int32_t x, int32_t y, const std::string& text);

private:
    std::map<uint32_t, CharacterInformation> characterMap;
    std::shared_ptr<Image> m_image;
};

#endif /* TEXTUREFONT_H_ */
