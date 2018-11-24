#include <vector>
#include <iostream>
#include <float.h>

#include "Object.h"
#include "ObjectIntersection.h"
#include "Ray.h"
#include "Material.h"
#include "Scene.h"
#include "RGBColor.h"

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
                info->o = obj;
                t_max = temp_info.t;
            }
        }
    }
    return hit_anyone;
}

bool Scene::shadow(Point3D point, ObjectIntersection* infoLight, ObjectIntersection* infoObject) const{
    Point3D lightPoint = Point3D(-10, -10, 0);
    Vector3D direction = point - lightPoint;
    direction.normalize();
    Ray rayToLight = Ray(lightPoint, direction);

    if(!intersect(rayToLight, infoLight) ) return true;

    if(infoLight->point == infoObject->point){
        return false;
    }

    // std::cout << "luz: " << infoLight->point.toString() << std::endl;
    // std::cout << "obj: " << infoLight->point.toString() << std::endl;

    return true;        
}


RGBColor Scene::trace(const Ray &r, int recursionLevel) const {
    ObjectIntersection info;
    RGBColor col;
    if(this->intersect(r, &info)) {
        ObjectIntersection infoLight;
        if ((this->shadow(info.point, &infoLight, &info))) {
            col = RGBColor(0,0,0);
            return col;
        }
        Material *m = info.o->material;
        col = m->color;
    } else {
        col = RGBColor(216,191,216);
    }
    return col;
}

void Scene::add(Object *object) {
    this->objects.push_back(object);
}

