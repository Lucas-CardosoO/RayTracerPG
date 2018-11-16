#include "Object.h"
#include "Geometry.h"
#include "Material.h"
#include "ObjectIntersection.h"
#include "Ray.h"

Object::Object(Geometry* g, Material* m) {
    this->geometry = g;
    this->material = m;
}

bool Object::intersect(const Ray& r, ObjectIntersection *info) {
    return this->geometry->intersect(r, info);
}