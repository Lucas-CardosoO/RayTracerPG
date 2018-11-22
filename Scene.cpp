#include <vector>
#include <iostream>

#include "Object.h"
#include "ObjectIntersection.h"
#include "Ray.h"
#include "Scene.h"
#include "RGBColor.h"
#include <float.h>

/**
 *  chama método intersect para cada objeto da cena e retorna verdadeiro caso haja interseção.
 *  Se houver mais de uma interseção, a informação do primeiro hit é guardado no endereço info.
**/
bool Scene::intersect(const Ray &r, ObjectIntersection* info) const {
    ObjectIntersection temp_info;
    bool hit_anyone = false;
    double t_max = DBL_MAX;
    for(auto obj : objects) {
        if(obj->intersect(r, &temp_info)) { 
            hit_anyone = true;
            if(temp_info.t < t_max) { // queremos interseção mais perto da origem do raio.
                info->t = temp_info.t;
                info->normal = temp_info.normal;
                info->point = temp_info.point;
                info->o = temp_info.o;
                t_max = temp_info.t;
            }
        }
    }
    return hit_anyone;
}

RGBColor Scene::trace(const Ray &r, int recursionLevel) const {
    ObjectIntersection info;
    if(this->intersect(r, &info)) {
        // std::cout << "normal: " << info.normal.toString() << std::endl;
        return RGBColor(255 * 0.5 * (info.normal.x+1),255 * 0.5 * (info.normal.y+1),255 * 0.5 * (info.normal.z+1));
    } else {
        return RGBColor(216,191,216);
    }
}

void Scene::add(Object *object) {
    this->objects.push_back(object);
}

