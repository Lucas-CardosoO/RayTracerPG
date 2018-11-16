#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include "Scene.h"
#include "Material.h"
#include "Geometry.h"
#include "Camera.h"
#include "Image.h"
#include "RGBColor.h"

using namespace std;

const int width = 200, height = 100;

Scene scene;
Camera cam;
int res_w, res_h;
map<string, Material> materials;


// recebe o caminho do arquivo de entrada como uma string, e lê como a especificação sugere, sendo as variáveis da cena globais
void read(const string &path_in) {
    string str;
    cout << path_in << endl;
    fstream in(path_in);
    
    while(in >> str) {
        if(str[0] == '#') getline(cin, str);
        else if(str == "res") {
            in >> res_w >> res_h;
        } else if(str == "camera") {
            double px, py, pz, tx, ty, tz, ux, uy, uz, fov, f;
            in >> px >> py >> pz >> tx >> ty >> tz >> ux >> uy >> uz >> fov >> f;
            // cam = Camera(...)
        } else if(str == "material") {
            string name;
            double r, g, b, kd, ks, ke, alpha;
            in >> r >> g >> b >> kd >> ks >> ke >> alpha;
            // materials[name] = Material(RGBColor(r, g, b), ... )
        } else if(str == "sphere") {
            double cx, cy, cz, r;
            string materialName;
            in >> cx >> cy >> cz >> r >> materialName;
            // Geometry sp = Sphere(Point3D(cx, cy, cz), r);
            // Material m = materials[materialName];
            // Object obj = Object(&sp, &m);
            // scene.add(&obj);
        }
    }

    cout << "fim da leitura.\n";
}

int main(int args, char** argv) {
    cout << args << " args:" << endl;
    for(int i = 0; i < args; i++) {
        cout << argv[i] << endl;
    }

    read(argv[1]);

    Image img(width, height);
    RGBColor white(216,191,216);
    RGBColor blue(67,100,230);

    for(int i = 0; i < img.height; i++) {
        for(int j = 0; j < img.width; j++) {
            if(j > i) img.setPixel(i, j, blue);
            else img.setPixel(i, j, white);
        }
    }

    img.saveAsPBM(""); // saving as out

    return 0;
}