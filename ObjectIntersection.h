#pragma once

#include "Object.h"
#include "Vector3D.h"
#include "Point3D.h"

class Object;

struct ObjectIntersection{
    double t;
    Vector3D normal;
    Point3D point;
    Object* o;
};