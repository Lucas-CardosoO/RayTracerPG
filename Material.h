#pragma once

#include "RGBColor.h"


class Material {
    public:
        RGBColor color;
        double Kd, Ke, Ka, alpha;
        Material(RGBColor c, double kd, double ke, double ka, double a) : color(c), Kd(kd), Ke(ke), Ka(a), alpha(a) {}

};