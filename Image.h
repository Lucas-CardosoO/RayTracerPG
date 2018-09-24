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

    void SetPixel(int x, int y, const RGBColor& color);

    void SaveAsPBM(const std::string& filePath) const;
};