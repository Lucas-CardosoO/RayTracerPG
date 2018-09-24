#pragma once

class RGBColor {
public:

    float r, g, b;

    RGBColor(); // default constructor
    RGBColor& operator= (const RGBColor& color); // assignment operator
    RGBColor(const RGBColor& color); // copy constructor
    ~RGBColor(); // destructor

    RGBColor(float grey);
    RGBColor(float red, float green, float blue);
    RGBColor operator+ (const RGBColor& color) const;
    RGBColor operator* (const RGBColor& color) const;
    RGBColor& operator+= (const RGBColor& color);

    RGBColor operator* (const float a) const;
    RGBColor operator/ (const float a) const;
    RGBColor operator^ (const float a) const;
};

RGBColor operator* (const float a, const RGBColor& color) ;