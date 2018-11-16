#pragma once

#include "Object.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Ray.h"
#include "ObjectIntersection.h"
#include <cmath>
#include <string>

class Geometry{
    public:
        virtual bool intersect(const Ray& r, ObjectIntersection* info = nullptr) const = 0;

        virtual Point3D getPoint() const = 0;

        virtual std::string toString() const = 0;
};

class Sphere : public Geometry {
    public:
        Point3D center;
        double radius;
        
        Sphere(Point3D center, double radius);
        bool intersect(const Ray& r, ObjectIntersection* info = nullptr) const override;
        Point3D getPoint() const override;
        std::string toString() const override;
};