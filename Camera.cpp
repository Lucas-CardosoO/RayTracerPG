#include "Vector3D.h"
#include "Ray.h"
#include "Camera.h"
#include "Point3D.h"

#include <cmath>
#include <string>
typedef Vector3D v3;
Camera::Camera(Point3D pos, Vector3D target, Vector3D up, double FOV, double d, double ratio) {
    this->position = pos;
    this->axisZ = target; this->axisZ.normalize();
    this->fov = FOV;
    this->near = d;
    this->axisX = up^this->axisZ; this->axisX.normalize();
    this->axisY = this->axisZ^this->axisX;
    this->tam_hor = 2*tan(fov/2)*near;
    this->tam_ver = this->tam_hor/ratio;
}

Ray Camera::getRay(double x, double y, int width, int height) const {
    v3 point = v3(this->position.x - this->tam_hor/2 + x * tam_hor/width,
                  this->position.y - this->tam_ver/2 + y * tam_ver/height,
                  this->position.z + this->near);
    v3 dir = point-this->position;
    dir.normalize();

    Ray r = Ray(this->position, dir); 
    return r;
}

std::string Camera::toString() const {
    std::string r = "";
    r += "axisX: " + axisX.toString() + "\naxisY: " + axisY.toString() +"\naxisZ: " + axisZ.toString();
    r += "\nposition: " + position.toString() + "\n fov = " + std::to_string(fov) + " near = " + std::to_string(near) +"\n";
    return r;
}


