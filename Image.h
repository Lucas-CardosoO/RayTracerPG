#pragma once

#include <vector>
#include "Vec3.h"

class Image{
private:
    int width, height;
    std::vector<Vec3> buffer;

public:
    Image(int width, int height);

    void SetPixel(int x, int y, const Vec3& color);

    void SaveAsPBM(const std::string& filePath) const;
};