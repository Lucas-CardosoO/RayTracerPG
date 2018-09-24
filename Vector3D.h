#pragma once

class Point3D;
class NormalV;

class Vector3D {
public:
    double x, y, z;

    Vector3D();
    ~Vector3D();

    Vector3D& operator= (const Vector3D& v);
    Vector3D& operator= (const Point3D& p);

    Vector3D(const Vector3D& v);
    Vector3D(const Point3D& p);

    Vector3D(double _x, double _y, double _z);

    Vector3D operator+ (const Vector3D& v) const;
    Vector3D operator- (const Vector3D& v) const;
    Vector3D operator* (const double a) const;
    Vector3D operator/ (const double a) const;

    double operator* (const Vector3D& v) const;
    Vector3D operator^ (const Vector3D& v) const;

    Vector3D operator- () const;
    Vector3D& operator+= (const Vector3D& v);

    double len();
    double len_squared();

    void normalize();
    Vector3D hat();

};

Vector3D operator* (const double a, const Vector3D& v);
