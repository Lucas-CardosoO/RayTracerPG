#pragma once
#include "Vector3D.h"
#include <float.h>
#include <string>

class Ray {

public:
    Vector3D direction;
    Point3D origin;
    mutable double tmin = DBL_EPSILON, tmax = DBL_MAX;
    Ray(Point3D origin, Vector3D direction);
    Point3D sample(const double &t) const;
    Point3D getOrigin() const;
    Vector3D getDirection() const;
    std::string toString();
};