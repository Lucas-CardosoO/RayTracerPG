#pragma once

#include "RGBColor.h"


class Material {
    public:
        RGBColor color;
        double Kd, Ks, Ka, alpha, refractiveIndice;
        bool isRefracted, isReflective; // 1 if surface will refract ray
        Material(RGBColor c, double kd, double Ks, double ka, double a, bool isRefracted, double refractiveindice, bool isReflective) : color(c), Kd(kd), Ks(Ks), Ka(a), alpha(a), isRefracted(isRefracted), refractiveIndice(refractiveindice), isReflective(isReflective) {}

};