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
            cam = Camera(Point3D(px, py, pz), Vector3D(tx, ty, tz), Vector3D(ux, uy, uz), fov, f);
        } else if(str == "material") {
            string name;
            double r, g, b, kd, ks, ke, alpha;
            in >> name >> r >> g >> b >> kd >> ks >> ke >> alpha;
            // materials[name] = Material(RGBColor(r, g, b), ... )
        } else if(str == "sphere") {
            double cx, cy, cz, r;
            string materialName;
            in >> cx >> cy >> cz >> r >> materialName;
            Geometry *sp = new Sphere(Point3D(cx, cy, cz), r);
            Material *m = new Material();
            Object obj = Object(sp, m);
            scene.add(&obj);
            // Material m = materials[materialName];
            // Object obj = Object(&sp, &m);
            // scene.add(&obj);
        }
    }
}

#define p3 Point3D
#define v3 Vector3D
int main(int args, char** argv) {
    cam = Camera(Point3D(0, 0, 0), Vector3D(1, 1, 0), Vector3D(0, 1, 0), 200, 10);
    res_w = 200, res_h = 100;
    Image img(res_w, res_h);

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