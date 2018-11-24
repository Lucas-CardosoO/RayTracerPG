#pragma once

#include "Object.h"
#include "ObjectIntersection.h"
#include "RGBColor.h"
#include "Ray.h"

#include <vector>

class Scene {
    public:
        std::vector<Object*> objects;
        bool intersect(const Ray &r, ObjectIntersection* info = nullptr) const;
        RGBColor trace(const Ray &r, int recursionLevel = 0) const;
        void add(Object *object);
        bool shadow(Point3D point, ObjectIntersection* infoLight, ObjectIntersection* infoObject) const;
};