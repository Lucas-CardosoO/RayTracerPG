#pragma once

#include "Object.h"
#include "ObjectIntersection.h"
#include <vector>

class Scene {
private:
    std::vector<Object*> objects;
public:
    bool intersect(const &Ray r, ObjectItersection* info = nullptr) const;
    Vector3D trace(const Ray &r, int recursionLevel = 0) const;
    void add(Object *object);
}