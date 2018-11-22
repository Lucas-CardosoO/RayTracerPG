#pragma once

#include "Vector3D.h"
#include "Point3D.h"
#include "Ray.h"
#include <cmath>
#include <string>

class Camera {
    public:
        Vector3D axisX, axisY, axisZ;
        Point3D position;
        double fov, near, tam_hor, tam_ver;

        Camera() {};
        Camera(Point3D position, Vector3D target, Vector3D up, double fov, double near, double ratio);
        Ray getRay(double x, double y, int width, int height) const;
        std::string toString() const;
};