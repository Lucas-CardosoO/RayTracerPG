#include <math.h>
#include "Vector3D.h"
#include "Point3D.h"

Vector3D::Vector3D() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vector3D::~Vector3D() {

}

Vector3D& Vector3D::operator=(const Vector3D& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vector3D::Vector3D(const Vector3D& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3D::Vector3D(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

Vector3D Vector3D::operator+(const Vector3D& v) const{
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D& v) const{
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator*(const double a) const{
    return Vector3D(x * a, y * a, z * a);
}

Vector3D Vector3D::operator/(const double a) const{
    return Vector3D(x / a, y / a, z / a);
}

double Vector3D::len() {
    return sqrt(x * x + y * y + z * z);
}

double Vector3D::len_squared() {
    return x * x + y * y + z * z;
}

Vector3D& Vector3D::operator=(const Point3D& p) {
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

Vector3D::Vector3D(const Point3D& p) {
    x = p.x;
    y = p.y;
    z = p.z;
}

double Vector3D::operator*(const Vector3D& v) const{
    return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::operator-() const{
    return Vector3D(-x, -y, -z);
}

Vector3D& Vector3D::operator+=(const Vector3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3D Vector3D::operator^(const Vector3D& v) const{
    return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

void Vector3D::normalize() {
    double length = sqrt(x*x + y*y + z*z);
    x /= length;
    y /= length;
    z /= length;
}

Vector3D Vector3D::hat() {
    double length = sqrt(x*x + y*y + z*z);
    return Vector3D(x / length, y / length, z / length);
}

Vector3D operator*(const double a, const Vector3D& v){
    return Vector3D(v.x * a, v.y * a, v.z * a);
}

Vector3D proj(const Vector3D &u, const Vector3D &v) {
    double coef = (u * v) / (v * v);
    return coef*v;
}