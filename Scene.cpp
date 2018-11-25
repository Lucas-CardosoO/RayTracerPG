#include <vector>
#include <iostream>
#include <float.h>
#include <cmath>
#include <algorithm>

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
                info->normal.normalize();
                info->point = temp_info.point;
                info->o = obj;
                t_max = temp_info.t;
            }
        }
    }
    return hit_anyone;
}

bool Scene::shadow(Point3D point, ObjectIntersection* infoLight, ObjectIntersection* infoObject) const{
    Vector3D direction = point - this->lightPoint;
    direction.normalize();
    Ray rayToLight = Ray(this->lightPoint, direction);

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
        // if ((this->shadow(info.point, &infoLight, &info))) {
        //     col = RGBColor(0,0,0);
        //     return col;
        // }
        Material *m = info.o->material;
        Vector3D lightDir = (this->lightPoint-info.point);
        lightDir.normalize();
        double difuseScalar = std::max(info.normal * lightDir, 0.0);
        Vector3D proj = ((lightDir * info.normal)/(info.normal * info.normal))*info.normal;
        Vector3D R = lightDir + 2 * proj;
        R.normalize();
        double specularScalar = std::pow(std::max(R*(-1*r.direction), 0.0), m->alpha); 

        col = m->color + (m->Kd*difuseScalar)*RGBColor(255, 255, 255) + (m->Ks*specularScalar)*RGBColor(255, 255, 255);
        col.toInt();
    } else {
        col = RGBColor(0,0,0);
    }
    return col;
}

void Scene::add(Object *object) {
    this->objects.push_back(object);
}

