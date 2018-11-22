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
    ObjectIntersection temp_record;
    ObjectIntersection *temp_info = &temp_record;
    bool hit_anyone = false;
    double t_max = DBL_MAX;
    for(auto obj : objects) {
        if(obj->intersect(r, temp_info)) { 
            hit_anyone = true;
            if(temp_record.t < t_max) { // queremos interseção mais perto da origem do raio.
                info = temp_info;
                t_max = temp_record.t;
            }
        }
    }
    return hit_anyone;
}

RGBColor Scene::trace(const Ray &r, int recursionLevel) const {
    ObjectIntersection* info;
    if(this->intersect(r, info)) {
        return RGBColor(92,3,111);
    } else {
        return RGBColor(216,191,216);
    }
}

void Scene::add(Object *object) {
    this->objects.push_back(object);
}

