#ifndef COMPARE_IMAGE_H
#define COMPARE_IMAGE_H

#include "image.h"
#include "retrogame_export.h"

#include <memory>

/**
 * Compares the two given images and returns true, if the images a equal.
 * If the images differ false is returned.
 */
bool RETROGAME_EXPORT compareImage(const Image& imageA, const Image& imageB);

#endif // COMPARE_IMAGE_H
