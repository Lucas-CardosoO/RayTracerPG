#pragma once

#include "Object.h"
#include "ObjectIntersection.h"
#include <vector>
#include "Ray.h"

class Scene {
    public:
        std::vector<Object*> objects;
        bool intersect(const Ray &r, ObjectIntersection* info = nullptr) const;
        Vector3D trace(const Ray &r, int recursionLevel = 0) const;
        void add(Object *object);
};