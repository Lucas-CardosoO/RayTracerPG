#pragma once
#include "Vector3D.h"

class Ray {
private:
    Vector3D direction;
    Point3D origin
public:
    mutable double tmin = DBL_EPSILON, tmax = DBL_MAX;
    Ray(Point3D origin, Vector3D direction);
    Point3D sample(const double &t) const;
    Point3D getOrigin() const;
    Vector3D getDirection() const;
}