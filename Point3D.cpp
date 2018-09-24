#include <math.h>
#include "Point3D.h"
#include "Vector3D.h"

Point3D::Point3D() {
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D(const Point3D& p) {
    x = p.x;
    y = p.y;
    z = p.z;
}

Point3D::Point3D(const Vector3D& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Point3D& Point3D::operator=(const Point3D& p) {
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}
Point3D& Point3D::operator=(const Vector3D& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Point3D::~Point3D() {

}

Point3D::Point3D(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

Point3D Point3D::operator+(const Vector3D& v) const {
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D& v) const {
    return Point3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Point3D::operator-(const Point3D& p) const {
    return Vector3D(x - p.x, y - p.y, z - p.z);
}

double Point3D::distance(const Point3D& p) {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z));
}

double Point3D::distance_squared(const Point3D& p) {
    return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z);
}

Point3D Point3D::operator*(const double a) const{
    return Point3D(x * a, y * a, z * a);
}

Point3D operator*(const double a, const Point3D& p){
    return Point3D(p.x * a, p.y * a, p.z * a);
}
