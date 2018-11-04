#include "Geometry.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Ray.h"
#include "ObjectIntersection.h"
#include <cmath>

Sphere::Sphere(Point3D center, double radius) {
    this->center = center;
    this->radius = radius;
}

Point3D Sphere::getPoint() const {
    return this->center;
}

bool Sphere::intersect(const Ray &r, ObjectIntersection* info) const{
    double a = r.getDirection() * r.getDirection();
    Vector3D center_as_vector = this->center;
    Vector3D w = r.getOrigin() - center_as_vector;
    double b = (2* r.getDirection())*w;
    double c = (r.getOrigin().x - this->center.x) * (r.getOrigin().x - this->center.x) +
               + (r.getOrigin().y - this->center.y) * (r.getOrigin().y - this->center.y)
               + (r.getOrigin().z - this->center.z) * (r.getOrigin().z - this->center.z) 
               - this->radius*this->radius;
    double delta = b*b + 4*a*c;
    if(delta < 0) return false;
    else {
        double t0, t1;
        t0 = (-b+sqrt(delta))/a;
        t1 = (-b-sqrt(delta))/a;
        info->t = (t0 < t1)? t0 : t1;
        return true;
    }

}


