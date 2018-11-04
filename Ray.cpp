#include "Ray.h"
#include "Vector3D.h"
#include "Point3D.h"

Ray::Ray(Point3D origin, Vector3D direction) {
    this->origin = origin;
    this->direction = direction;
}

Point3D Ray::getOrigin() const {
    return this->origin;
}

Vector3D Ray::getDirection() const {
    return this->direction;
}

Point3D Ray::sample(const double &t) const {
    return this->origin+(this->direction*t);
}