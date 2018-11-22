#pragma once

#include "Vector3D.h"
#include "RGBColor.h"
#include "Point3D.h"

class PointLight {
    public:
        double intensity;
        RGBColor color;
        Point3D position;

        PointLight() { }
        PointLight(double i, RGBColor c, Point3D p) : intensity(i), color(c), position(p) {}
};

class DistantLight {
    public:
        double intensity;
        Vector3D direction;
        RGBColor color;

        DistantLight() { }
        DistantLight(double i, RGBColor c, Vector3D dir) : intensity(i), color(c), direction(dir) {}
};