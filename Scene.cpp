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

RGBColor Scene::trace(const Ray &r, int recursionLevel, double curRefractionIndice) const {
    ObjectIntersection info;
    RGBColor col(0,0,0);
    if(this->intersect(r, &info)) {
        double difuseScalar = 0, specularScalar = 0;
        Material *material = info.o->material;
        Point3D intersectionPoint = info.point;
        Vector3D normal = info.normal;
        col += material->color*material->Ka;

        

        for(auto l : this->lights) {
            Vector3D lightDir = l.position - intersectionPoint;
            lightDir.normalize();
            if(material->willRefract) {
                // to remember: n_l*sen(teta_i) = n_2*sen(teta_t), Total Internal Reflection (TIR) when sen(teta_i) > n_2/n_1
                double n1 = curRefractionIndice, n2 = material->refractiveIndice;
                double cos_teta_i = lightDir * normal;
                double sen_teta_i = std::sqrt(1 - cos_teta_i*cos_teta_i);

                // check if TIR
                if(n2/n1 > sen_teta_i) {
                    return RGBColor(255, 255, 255); // não sei o que colocar
                }
                // if not TIR
                Vector3D t_a, t_o, t; // t adjacente, t ortogonal e t, vetor da direção da transmissão
                t_a =  n1/n2 * (-lightDir + ( cos_teta_i ) * normal);
                t_o = -std::sqrt(1 - t_a.len_squared())*normal;
                t = t_a + t_o;
                col = 0.3* col;
                col += 0.7*trace(Ray(intersectionPoint, t), recursionLevel, n2);
                return col;
            }
            ObjectIntersection infoLight;

            Ray lightRay = Ray(l.position, -lightDir);

            this->intersect(lightRay, &infoLight);

            if(infoLight.point == intersectionPoint){
                difuseScalar += std::max(normal * lightDir, 0.0) * l.intensity;
                Vector3D proj = ((lightDir * normal)/(normal * normal))*normal;
                Vector3D R = lightDir + 2 * proj;
                R.normalize();
                specularScalar += std::pow(std::max(R*(-1*r.direction), 0.0), material->alpha) * l.intensity;
                col += (material->Kd*difuseScalar)*l.color + (material->Ks*specularScalar)*l.color;
            }
        }
         
        col.toInt();
    } else {
        // col = backgroundColor;
    }
    return col;
}

void Scene::addObject(Object *object) {
    this->objects.push_back(object);
}

void Scene::addLight(LightPoint light) {
    this->lights.push_back(light);
}

