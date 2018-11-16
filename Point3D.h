#pragma once

#include <string>

class Vector3D;

class Point3D {
public:
    double x, y, z;

    Point3D();
    Point3D(const Point3D& p);
    Point3D(const Vector3D& v);
    Point3D& operator= (const Point3D& p);
    Point3D& operator= (const Vector3D& v);
    ~Point3D();

    Point3D(double _x, double _y, double _z);

    Point3D operator+ (const Vector3D& v) const;
    Point3D operator- (const Vector3D& v) const;
    Vector3D operator- (const Point3D& p) const;

    double distance(const Point3D& p);
    double distance_squared(const Point3D& p);

    Point3D operator* (const double a) const;

    std::string toString() const;
};

Point3D operator* (const double a, const Point3D& p);