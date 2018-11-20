#include "Vector3D.h"
#include "Ray.h"
#include "Camera.h"
#include "Point3D.h"

#include <cmath>
#include <string>

Camera::Camera(Point3D pos, Vector3D target, Vector3D up, double FOV, double d) {
    this->position = pos;
    this->axisZ = target; this->axisZ.normalize();
    this->axisY = up; this->axisY.normalize();
    this->fov = FOV;
    this->near = d;
    this->axisX = up ^ this->axisZ; this->axisX.normalize();
    this->axisY = this->axisX ^ this->axisZ; this->axisY.normalize();
}

Ray Camera::getRay(double x, double y, int width, int height) const {
    Point3D corner = Point3D(this->position.x, this->position.y, this->near);
    Vector3D dir = Vector3D(x, y, 0) + corner;
    Ray r = Ray(this->position, dir); 
    return r;
}

std::string Camera::toString() const {
    std::string r = "";
    r += "axisX: " + axisX.toString() + "\naxisY: " + axisY.toString() +"\naxisZ: " + axisZ.toString();
    r += "\nposition: " + position.toString() + "\n fov = " + std::to_string(fov) + " near = " + std::to_string(near) +"\n";
    return r;
}


