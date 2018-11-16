#include <vector>

#include "Object.h"
#include "ObjectIntersection.h"
#include "Ray.h"
#include "Scene.h"

bool Scene::intersect(const Ray &r, ObjectIntersection* info) const {
    return true;
}

Vector3D Scene::trace(const Ray &r, int recursionLevel) const {
    return Vector3D(0, 0, 0);
}

void Scene::add(Object *object) {
    this->objects.push_back(object);
}

