#include <vector>

#include "Object.h"
#include "ObjectIntersection.h"
#include "Ray.h"
#include "Scene.h"
#include <float.h>

/**
 *  chama método intersect para cada objeto da cena e retorna verdadeiro caso haja interseção.
 *  Se houver mais de uma interseção, a informação do primeiro hit é guardado no endereço info.
**/
bool Scene::intersect(const Ray &r, ObjectIntersection* info) const {
    ObjectIntersection *temp_info;
    bool hit_anyone = false;
    double t_max = DBL_MAX;
    for(auto obj : objects) {
        if(obj->intersect(r, temp_info)) { 
            hit_anyone = true;
            if(temp_info->t < t_max) { // queremos interseção mais perto da origem do raio.
                info = temp_info;
                t_max = info->t;
            }
        }
    }
    return hit_anyone;
}

Vector3D Scene::trace(const Ray &r, int recursionLevel) const {
    
}

void Scene::add(Object *object) {
    this->objects.push_back(object);
}

