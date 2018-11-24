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
#include "ObjectIntersection.h"
using namespace std;

Scene scene;
Camera cam;
int res_w, res_h;
map<string, Material> materials;

const double pi = 3.14159265;

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
            cam = Camera(Point3D(px, py, pz), Vector3D(tx, ty, tz), Vector3D(ux, uy, uz), fov, f, 1.25);
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
            Object obj = Object(sp, nullptr);
            scene.add(&obj);
            // Material m = materials[materialName];
            // Object obj = Object(&sp, &m);
            // scene.add(&obj);
        }
    }
    cout << "finished reading.\n";
}

RGBColor white(216,191,216);
RGBColor blue(67,100,230);

int main(int args, char** argv) {

    // read("./t1.txt");
    // center, target, up, fov, near, ratio
    cam = Camera(Point3D(0, 0, 0), Vector3D(0, 0, 1), Vector3D(0, 1, 0), pi/2, 1, 2);
    Geometry *E1 = new Sphere(Point3D(7, -3, 9), 1);
    Material M1 = Material(RGBColor(198, 78, 71), 0.3, 0.5, 0.3, 2);
    Object obj =  Object(E1, &M1);
    scene.add(&obj);

    // Geometry *E2 = new Sphere(Point3D(4, 0, 7), 0.5);
    // Object obj2 = Object(E2, nullptr);
    // scene.add(&obj2);

    // Geometry *E3 = new Sphere(Point3D(-4, 0, 7), 0.5);
    // Object obj3 = Object(E3, nullptr);
    // scene.add(&obj3);

    res_w = 500, res_h = 250;
    Image img(res_w, res_h);


    cout << "CAMERA: "<<endl;
    cout << cam.toString();

    cout << "objects(" << scene.objects.size() <<"):\n";
    for(auto objPtr : scene.objects) {
        cout << "{ ";
        Object o = *objPtr;
        cout << o.geometry->toString() << "} " << endl;
    }

    cout << "starting to print\n";
    for(int i = 0; i < img.height; i++) {
        for(int j = 0; j < img.width; j++) {
            Ray r = cam.getRay(double(j), double(i), res_w, res_h);
            img.setPixel(i, j, scene.trace(r, 0));
        }
    }

    cout << "done printing\n";

    img.saveAsPBM(""); // saving as out

    return 0;
}