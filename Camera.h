#pragma once

#include "Vector3D.h"
#include "Ray.h"
#include <cmath>

class Camera {
private:
    Vector3D position, axisX, axisY, axisZ;
    double fov, near;

public:
    Camera(Vector3D position, Vector3D target, Vector3D up, double fov, double near);

    Ray GetRay(double x, double y, int width, int height) const;
};