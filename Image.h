#pragma once

#include <vector>
#include <string>
#include "RGBColor.h"

class Image{
private:
    int width, height;
    std::vector<RGBColor> buffer;

public:
    Image(int width, int height);
    int getWidth();
    int getHeight();
    void setPixel(int x, int y, const RGBColor& color);
    void saveAsPBM(const std::string& filePath) const;
};