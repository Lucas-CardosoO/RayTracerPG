#pragma once

#include "Vec3.h"
#include "Ray.h"
#include <cmath>

class Camera {
private:
    Vec3 position, axisX, axisY, axisZ;
    double fov, near;

public:
    Camera(Vec3 position, Vec3 target, Vec3 up, double fov, double near);

    Ray GetRay(double x, double y, int width, int height) const;
};