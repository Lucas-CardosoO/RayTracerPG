#include "Image.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    this->buffer.resize(this->width*this->height);
}
void Image::setPixel(int x, int y, const RGBColor& color) {
    this->buffer[x*this->width + y] = color;
}

void Image::saveAsPBM(const std::string& filePath) const {
    std::ofstream out("cena.ppm");
    out << "P3\n" << this->width << " " << this->height  << "\n255\n";
    std::cout << "Saving file";
    for(int i = 0; i < this->height; i++) {
        if(i == this->height/3) std::cout << ".";
        if(i == 2*this->height/3) std::cout << '.';
        if(i == this->height-1) std::cout << ". ";
        for(int j = 0; j < this->width; j++) {
            // std::cout << "Putting px in (" << i <<", " << j<<")\nbuffer["<<i*this->width+j<<"] is the buffer pos\n";
            out << this->buffer[i*this->width+j].r << ' ' << this->buffer[i*this->width+j].g << ' ' << this->buffer[i*this->width+j].b << '\n';
        }
    }
    out.close();
    std::cout << "done";
}

