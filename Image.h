#pragma once

#include <vector>
#include <string>
#include "RGBColor.h"

class Image {
public:
    int width, height;
    std::vector<RGBColor> buffer;
    Image(int width, int height);
    void setPixel(int x, int y, const RGBColor& color);
    void saveAsPBM(const std::string& filePath) const;
};