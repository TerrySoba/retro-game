#include "png_image.h"

#include "lodepng/lodepng.h"
#include "exception.h"

#include "fmt/format.h"

#include "boost/scope_exit.hpp"

#include <cstdio>
#include <iostream>

PngImage::PngImage(const std::string& filename)
{
    std::vector<unsigned char> buffer;

    auto error = lodepng::load_file(buffer, filename); //load the image file with given filename

    if (error)
    {
        throw Exception(fmt::format("PNG loading error {}: {}", error, lodepng_error_text(error)));
    }

    lodepng::State state;

    error = lodepng::decode(m_imageData, m_width, m_height, state, buffer);
    if (error)
    {
        throw Exception(fmt::format("PNG decoder error {}: {}", error, lodepng_error_text(error)));
    }

    if (m_imageData.size() % 4 != 0)
    {
        throw Exception(fmt::format("Image data size needs to be a multiple of 4, but actually it is {}. {} % 4 == {}", m_imageData.size(), m_imageData.size(), m_imageData.size() % 4));
    }

    // convert to XRGB
    for (size_t i = 0; i < m_imageData.size(); i += 4)
    {
        uint32_t& pixel = reinterpret_cast<uint32_t&>(m_imageData[i]);
        pixel = m_imageData[i + 2] << 0 | m_imageData[i + 1] << 8 | m_imageData[i + 0] << 16;
    }

}

uint32_t* PngImage::getData()
{
    return reinterpret_cast<uint32_t*>(m_imageData.data());
}

const uint32_t* PngImage::getData() const
{
    return reinterpret_cast<const uint32_t*>(m_imageData.data());
}

uint32_t PngImage::getWidth() const
{
    return m_width;
}

uint32_t PngImage::getHeight() const
{
    return m_height;
}
