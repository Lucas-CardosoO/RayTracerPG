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
    std::cout<<"a\n";
    /*
        Substitui 't' (tirado da eq. de 'r' na forma paramétrica) na eq. da esfera.
        Acha interseções analizando as raizes do polinômio
        r = r.origem + t * r.direção
        E = (x - x0)^2 + (y - y0)^2 + (z - z0)^2 = R^2
    */
    Vector3D oc = r.getOrigin() - this->center;
    double a = r.getDirection()*r.getDirection();
    double b = 2*(oc*r.getDirection());
    double c = (oc * oc) - this->radius*this->radius;

    double delta = b*b-4*a*c;
    std::cout<<"b\n";
    if(delta < 0) return false;
    // double t1 = (-b + std::sqrt(delta))/2*a, t2 = (-b - std::sqrt(delta))/2*a;
    // info->t = (t1 < t2)? t1 : t2;
    // info->point = r.sample(info->t);
    // info->normal = (info->point - this->center);
    // std::cout << "But I returned true\n";
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