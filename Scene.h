#pragma once

#include "Object.h"
#include "ObjectIntersection.h"
#include "RGBColor.h"
#include "Ray.h"
#include "LightPoint.h"
#include <vector>

class Scene {
    public:
        std::vector<Object*> objects;
        std::vector<LightPoint> lights;
        Scene() { }
        bool intersect(const Ray &r, ObjectIntersection* info = nullptr);
        RGBColor trace(const Ray &r, int recursionLevel, double curRefractionIndice);
        void addObject(Object *object);
        void addLight(LightPoint light);
        bool shadow(Point3D point, ObjectIntersection* infoLight, ObjectIntersection* infoObject);
        double fresnel(Vector3D ray, Vector3D normal, double n, double kr);
};