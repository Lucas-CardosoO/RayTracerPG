#include "Vector3D.h"
#include "Ray.h"
#include "Camera.h"
#include "Point3D.h"

#include <cmath>
#include <string>

Camera::Camera(Point3D pos, Vector3D target, Vector3D up, double FOV, double d) {
    this->position = pos;
    this->axisZ = target*(-1); this->axisZ.normalize();
    this->axisY = up; this->axisY.normalize();
    this->fov = FOV;
    this->near = d;
    this->axisX = this->axisZ ^ up; this->axisX.normalize();
    this->axisY = this->axisX ^ this->axisZ; this->axisY.normalize();
}

Ray Camera::getRay(double x, double y, int width, int height) const {
    // Point3D corner = Point3D(this->position.x, this->position.y, this->near);
    double ndc_x = (x + 0.5)/double(width);
    double ndc_y = (y + 0.5)/double(height);
    double screen_x = 2 * ndc_x - 1;
    double screen_y = 1 - 2 * ndc_y;
    double ratio = double(width)/double(height);
    // double cam_x = (2 * screen_x - 1) * ratio * std::tan(fov/2);
    double cam_x = (2 * screen_x - 1) * ratio;
    double cam_y = 1 - 2 * screen_y;

    Ray r = Ray(this->position, Vector3D(cam_x, cam_y, this->near)); 
    return r;
}

std::string Camera::toString() const {
    std::string r = "";
    r += "axisX: " + axisX.toString() + "\naxisY: " + axisY.toString() +"\naxisZ: " + axisZ.toString();
    r += "\nposition: " + position.toString() + "\n fov = " + std::to_string(fov) + " near = " + std::to_string(near) +"\n";
    return r;
}


