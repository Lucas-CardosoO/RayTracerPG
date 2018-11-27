#pragma once

#include "RGBColor.h"


class Material {
    public:
        RGBColor color;
        double Kd, Ks, Ka, alpha, refractiveIndice;
        bool willRefract; // 1 if surface will refract ray
        Material(RGBColor c, double kd, double Ks, double ka, double a, bool willrefract, double refractiveindice) : color(c), Kd(kd), Ks(Ks), Ka(a), alpha(a), willRefract(willrefract), refractiveIndice(refractiveindice) {}

};