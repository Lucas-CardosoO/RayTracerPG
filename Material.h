#pragma once

#include "RGBColor.h"


class Material {
    public:
        RGBColor color;
        double Kd, Ks, Ka, alpha;
        Material(RGBColor c, double kd, double Ks, double ka, double a) : color(c), Kd(kd), Ks(Ks), Ka(a), alpha(a) {}

};