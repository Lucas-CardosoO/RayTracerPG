#include <cmath>
#include <string>
#include <iostream>
#include "Object.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Ray.h"
#include "ObjectIntersection.h"

Sphere::Sphere(Point3D center, double radius) {
    this->center = center;
    this->radius = radius;
}

bool Sphere::intersect(const Ray &r, ObjectIntersection *info) const {
    Vector3D oc = r.getOrigin() - this->center;
    double a = r.getDirection()*r.getDirection();
    double b = 2*(oc*r.getDirection());
    double c = (oc * oc) - this->radius*this->radius;

    double delta = b*b-4*a*c;
    if(delta < 0) return false;
    double t1 =(-b + std::sqrt(delta))/2*a, t2 = (-b - std::sqrt(delta))/2*a;
    // std::cout<<"t1:"<<t1<<" " <<"t2:"<<t2<<std::endl;
    // ObjectIntersection record;
    // info = &record;
    info->t = (t1 < t2)? t1 : t2;
    info->point = r.sample(info->t);
    info->normal = (info->point - this->center);
    info->normal.normalize();

    // std::cout << "But I returned true\n";
    info->t = info->t - 0.0000001;
    if(info->t < 0){
        return false;
    }

    return true;
}

Point3D Sphere::getPoint() const {
    return this->center;
}

std::string Sphere::toString() const {
    std::string r = "";
    r += "center = " + this->center.toString();
    r += "\nradius = " + std::to_string(this->radius);
    return r;
}