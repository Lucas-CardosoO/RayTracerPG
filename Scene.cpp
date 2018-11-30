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
    
    if (recursionLevel > 10) {
        return RGBColor(0,0,0);
    }

    ObjectIntersection info;
    RGBColor col(0,0,0);
    if(this->intersect(r, &info)) {
        double difuseScalar = 0, specularScalar = 0;
        Material *material = info.o->material;
        Point3D intersectionPoint = info.point;
        Vector3D normal = info.normal;
        if(curRefractionIndice != 1) normal = -normal;
        col += material->color*material->Ka;

        

        for(auto l : this->lights) {
            Vector3D lightDir = l.position - intersectionPoint;
            lightDir.normalize();
            ObjectIntersection infoLight;

            Ray lightRay = Ray(l.position, -lightDir);

            this->intersect(lightRay, &infoLight);

            if(infoLight.point == intersectionPoint){
                difuseScalar += std::max(normal * lightDir, 0.0) * l.intensity;
                Vector3D proj = ((lightDir * normal)/(normal * normal))*normal;
                Vector3D R = -lightDir +( 2 * proj);
                R.normalize();
                specularScalar += std::pow(std::max(R*(-1*r.direction), 0.0), material->alpha) * l.intensity;

                col += (material->Kd*difuseScalar)*l.color + (material->Ks*specularScalar)*l.color;
            }
        }

        if(material->isReflective){
            Vector3D proj = ((-r.direction * normal)/(normal * normal))*normal;
            Vector3D R = r.direction +( 2 * proj);
            R.normalize();

            RGBColor reflection = trace(Ray(intersectionPoint, R), recursionLevel + 1, curRefractionIndice);
            // tvz pra reflexão perfeita a cor seja só o que foi refletido
            col = material->Ks*reflection;
        }

        if(material->isRefracted){
            // std::cout << "indice: " << material->refractiveIndice << std::endl;

            // double n1 = (curRefractionIndice == 1)? curRefractionIndice: material->refractiveIndice;
            // double n2 = (n1 == 1)? material->refractiveIndice: 1;
            // double cos_teta = -r.direction * normal;
            // double sen_teta = std::sqrt(1 - cos_teta*cos_teta);
            // // std::cout << "teta ok" << std::endl;
            // if(sen_teta > n2/n1) {
            //     Vector3D proj = ((-r.direction * normal)/(normal * normal))*normal;
            //     Vector3D R = r.direction +( 2 * proj);
            //     R.normalize();
            //     RGBColor reflection = trace(Ray(intersectionPoint, R), recursionLevel+1, curRefractionIndice);
            //     col = material->Ks*reflection;
            //     return col;
            // }
            // double sen_alfa = n1*sen_teta/n2;
            // double cos_alfa = std::sqrt(1 - sen_alfa*sen_alfa);
            // Vector3D t_par = n1/n2*(r.direction + cos_teta*normal);
            // Vector3D t_ort = - std::sqrt(1 - t_par.len_squared())*normal;
            // Vector3D t = t_par + t_ort;
            // t.normalize();
            // RGBColor colorFromRefraction = trace(Ray(intersectionPoint, t), recursionLevel+1, n2);

            double nDotr = normal * r.direction;
            double n1 = 1;
            double n2 = material->refractiveIndice;
            
            Vector3D normalRef = normal;

            if(nDotr < 0){
                nDotr = -nDotr;
            } else {
                normalRef = -normal;

                std::swap(n1,n2);
            }

            double nRatio = n1/n2;

            double cosi = nDotr;

            double k = 1 - nRatio*nRatio*(1- cosi*cosi);

            RGBColor colorFromReflection1 = RGBColor(0,0,0);
            RGBColor colorFromRefraction = RGBColor(0,0,0);

            if (k < 0){
                Vector3D proj = (-r.direction * normalRef)*normalRef;
                Vector3D R = r.direction +( 2 * proj);
                R.normalize();
                colorFromReflection1 = trace(Ray(intersectionPoint, R), recursionLevel + 1, curRefractionIndice);
            } else {
                Vector3D refrVec = nRatio*r.direction + (nRatio*cosi - std::sqrt(k))*normalRef;
                refrVec.normalize();
                colorFromRefraction = trace(Ray(intersectionPoint, refrVec), recursionLevel + 1, curRefractionIndice);
            }

            Vector3D proj = ((-r.direction * normal)/(normal * normal))*normal;
            Vector3D R = r.direction +( 2 * proj);
            R.normalize();
            RGBColor colorFromReflection = trace(Ray(intersectionPoint, R), recursionLevel + 1, curRefractionIndice);

            col = 0.2*colorFromReflection + 0.8*colorFromRefraction + 0.8*colorFromReflection1;
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

