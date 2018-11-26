#pragma once

#include "Point3D.h"
#include "Vector3D.h"
#include "RGBColor.h"

class LightPoint {
    public:
        Point3D position;
        double intensity;
        RGBColor color;

        LightPoint(Point3D pos, double i, RGBColor c) : position(pos), intensity(i), color(c) { }
};
