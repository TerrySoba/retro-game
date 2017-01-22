#include "png_image.h"

#include "png.h"
#include "exception.h"

#include "fmt/format.h"


#include "boost/scope_exit.hpp"

#include <cstdio>
#include <iostream>


PngImage::PngImage(const std::string& filename)
{
    uint8_t header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(filename.c_str(), "rb");
    BOOST_SCOPE_EXIT_ALL(&)
    {
        fclose(fp);
    };

    if (!fp)
    {
        throw Exception(fmt::format("Could not open file \"{}\".",  filename));
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        throw Exception(fmt::format("File \"{}\" is not a PNG-File.",  filename));
    }

    png_infop info_ptr = nullptr;

    /* initialize stuff */
    auto png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    BOOST_SCOPE_EXIT_ALL(&)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    };

    if (!png_ptr)
    {
        throw Exception("creation of png_create_read_struct failed.");
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        throw Exception("creation of png_create_info_struct failed.");
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        throw Exception("Error during init_io.");
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    auto width = png_get_image_width(png_ptr, info_ptr);
    auto height = png_get_image_height(png_ptr, info_ptr);
    auto colorType = png_get_color_type(png_ptr, info_ptr);
    auto bitDepth = png_get_bit_depth(png_ptr, info_ptr);

    auto number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    auto bytesPerRow = png_get_rowbytes(png_ptr,info_ptr);

    // get required space for image
    std::vector<uint8_t> imageData(bytesPerRow * height);

    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        throw Exception("Error during read_image.");
    }

    std::vector<png_bytep> rowPointers(height);
    for (int y = 0; y < height; ++y)
    {
        rowPointers[y] = &imageData[bytesPerRow * y];
    }

    png_read_image(png_ptr, rowPointers.data());


    /// now convert to target image format XRGB

    if (bitDepth != 8)
    {
        throw Exception(fmt::format("Only 8-bit images are supported, but given image has {} bits.", bitDepth));
    }

    if (colorType != PNG_COLOR_TYPE_RGB && colorType != PNG_COLOR_TYPE_RGBA)
    {
        throw Exception(fmt::format("Only RGB(A) images are supported, but given image has color type {}.", colorType));
    }

    m_imageData.resize(sizeof(uint32_t) * width * height);

    if (colorType & PNG_COLOR_MASK_ALPHA)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                auto r = imageData[y * bytesPerRow + (4 * x) + 0];
                auto g = imageData[y * bytesPerRow + (4 * x) + 1];
                auto b = imageData[y * bytesPerRow + (4 * x) + 2];
                m_imageData[y * width + x] = (r << 16) | (g << 8) | (b << 0);
            }
        }
    }
    else
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                auto r = imageData[y * bytesPerRow + (3 * x) + 0];
                auto g = imageData[y * bytesPerRow + (3 * x) + 1];
                auto b = imageData[y * bytesPerRow + (3 * x) + 2];
                m_imageData[y * width + x] = (r << 16) | (g << 8) | (b << 0);
            }
        }
    }

    m_height = height;
    m_width = width;
}

uint32_t* PngImage::getData()
{
    return m_imageData.data();
}

uint32_t PngImage::getWidth()
{
    return m_width;
}

uint32_t PngImage::getHeight()
{
    return m_height;
}
