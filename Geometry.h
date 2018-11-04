#pragma once

#include "Vector3D.h"
#include "Point3D.h"
#include "Ray.h"
#include "ObjectIntersection.h"
#include <cmath>

class Geometry{
    public:
        virtual bool intersect(const Ray& r, ObjectIntersection* info = nullptr) const = 0;

        virtual Point3D getPoint() const = 0;
};

class Sphere : public Geometry {
    private:
        Vector3D center;
        double radius;

    public:
        Sphere(Point3D center, double radius );
        
        bool intersect(const Ray& r, ObjectIntersection* info = nullptr) const;

        Point3D getPoint() const override;
};