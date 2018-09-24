#pragma once

#include <vector>
#include "Vector3D.h"

class Image{
private:
    int width, height;
    std::vector<Vector3D> buffer;

public:
    Image(int width, int height);

    void SetPixel(int x, int y, const Vector3D& color);

    void SaveAsPBM(const std::string& filePath) const;
};