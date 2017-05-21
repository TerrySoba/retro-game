/*
 * TextureFont.cpp
 *
 *  Created on: 27.03.2012
 *      Author: yoshi252
 */

#include "texture_font.h"
#include "exception.h"
#include "memory_image.h"

#include "fmt/format.h"

#include <cstring>
#include <stdint.h>
#include <fstream>


inline void checked_fread(void* dest, size_t size, size_t nmemb, std::fstream& fp) {
    fp.read(static_cast<char*>(dest), size * nmemb);
    if (fp.fail()) {
        THROW_EXCEPTION("read number of elements did not match requested number of elements.");
    }
}

TextureFont::TextureFont() {

}

TextureFont::~TextureFont() {
    // TODO Auto-generated destructor stub
}

bool TextureFont::hasCharacter(uint32_t unicode) {
    return (characterMap.count(unicode) >= 1);
}

CharacterInformation* TextureFont::getCharacter(uint32_t unicode) {
    if (hasCharacter(unicode)) {
        return &characterMap[unicode];
    } else {
        return NULL;
    }
}



bool TextureFont::load(const std::string& path) {
    std::fstream fp(path, std::ios_base::in | std::ios_base::binary);

    if (!fp.is_open()) {
        THROW_EXCEPTION(fmt::format("Could not open font file: {}", path));
    }

    // now read file signature
    char buffer[7];
    buffer[6] = 0;
    checked_fread(buffer, 1, 6, fp);
    // check if signature matches
    if (memcmp(buffer, "ytf252", 6) != 0) {
        THROW_EXCEPTION(fmt::format("Font file did not have matching signature: {}", buffer));
    }

    // read version of file
    uint16_t version;
    checked_fread(&version, sizeof(uint16_t), 1, fp);

    // this parser is for version 4. Check if version matches.
    if (version != 4) {
        THROW_EXCEPTION(fmt::format("This parser only supports version 4, but version {} was found in fontfile.", version));
    }

    // read font name
    uint32_t nameLength;
    checked_fread(&nameLength, sizeof(uint32_t), 1, fp);
    std::string fontName(nameLength, 0);
    checked_fread(&(fontName[0]), nameLength, sizeof(char), fp);

    // read width and height of texture
    uint32_t width, height;
    checked_fread(&width, sizeof(uint32_t), 1, fp);
    checked_fread(&height, sizeof(uint32_t), 1, fp);

    // now read texture data
    std::vector<uint8_t> textureTmp(width * height * sizeof(uint8_t));

    checked_fread(&textureTmp[0], sizeof(uint8_t), width * height, fp);

    // now create LuminanceAlpha texture
    auto texture = std::make_shared<MemoryImage>(width, height);
    auto texturePtr = texture->getData();

    for (size_t i = 0; i < width * height; ++i)
    {
        auto& pixel = textureTmp[i];
        texturePtr[i] = pixel << 16 | pixel << 8 | pixel << 0;
    }

    m_image = texture;

    // now read how many characters this font contains
    uint32_t noOfCharacters;
    checked_fread(&noOfCharacters, sizeof(uint32_t), 1, fp);

    // now read information about each character
    for (uint32_t n = 0; n < noOfCharacters; n++) {
        CharacterInformation info;

        checked_fread(&info.unicode, sizeof(uint32_t), 1, fp);
        checked_fread(&info.bearingLeft, sizeof(int32_t), 1, fp);
        checked_fread(&info.bearingTop, sizeof(int32_t), 1, fp);
        checked_fread(&info.horiAdvance, sizeof(double), 1, fp);
        checked_fread(&info.vertAdvance, sizeof(double), 1, fp);
        checked_fread(&info.imageLeft, sizeof(int32_t), 1, fp);
        checked_fread(&info.imageTop, sizeof(int32_t), 1, fp);
        checked_fread(&info.imageWidth, sizeof(uint32_t), 1, fp);
        checked_fread(&info.imageHeight, sizeof(uint32_t), 1, fp);

        characterMap.insert(std::make_pair(info.unicode, info));
    }

    // now log some debug information
    // LOG("loaded font file ", path);
    // LOG("loaded texture of size ", width, "x", height);
    // LOG("found ", noOfCharacters, " characters.");

    return true;
}
