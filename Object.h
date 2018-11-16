#pragma once

#include "Geometry.h"
#include "Material.h"
#include "ObjectIntersection.h"
#include "Ray.h"

class Object {
    public:
        Geometry* geometry;
        Material* material;

        Object(Geometry* geometry, Material* material);
        bool intersect(const Ray& r, ObjectIntersection* info = nullptr);
};