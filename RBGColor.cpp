#include <math.h>
#include "RGBColor.h"

RGBColor::RGBColor() {
    r = 0;
    g = 0;
    b = 0;
}

RGBColor& RGBColor::operator=(const RGBColor& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    return *this;
}

RGBColor::RGBColor(const RGBColor& color) {
    r = color.r;
    g = color.g;
    b = color.b;
}

RGBColor::~RGBColor() {

}

RGBColor::RGBColor(float grey) {
    r = grey;
    g = grey;
    b = grey;
}

RGBColor::RGBColor(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
}

RGBColor RGBColor::operator+(const RGBColor& color) const{
    return RGBColor(r + color.r, g + color.g, b + color.b);
}

RGBColor RGBColor::operator*(const RGBColor& color) const{
    return RGBColor(r * color.r, g * color.g, b * color.b);
}

RGBColor& RGBColor::operator+=(const RGBColor& color){
    r += color.r;
    g += color.g;
    b += color.b;
    return *this;
}

RGBColor RGBColor::operator*(const float a) const{
    return RGBColor(r * a, g * a, b * a);
}

RGBColor RGBColor::operator/(const float a) const{
    return RGBColor(r / a, g / a, b / a);
}

RGBColor RGBColor::operator^(const float a) const{
    return RGBColor(powf(b, a), powf(g, a), powf(b, a));
}

RGBColor operator*(const float a, const RGBColor& color) {
    return RGBColor(color.r * a, color.g * a, color.b * a);
}
