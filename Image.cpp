#include "Image.h"
#include <vector>
#include <string>
#include <fstream>

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    this->buffer.resize(this->width*this->height);
}
void Image::setPixel(int x, int y, const RGBColor& color) {
    this->buffer[x*this->width+y] = color;
}

void Image::saveAsPBM(const std::string& filePath) const {
    std::ofstream out(filePath+"\\out.ppm");
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            out << this->buffer[this->width*i+j].r << ' ' << this->buffer[this->width*i+j].g << ' ' << this->buffer[this->width*i+j].b << '\n';
        }
    }
    out.close();
}

int Image::getWidth() {
    return this->width;
}

int Image::getHeight() {
    return this->height;
}
