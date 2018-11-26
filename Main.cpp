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
#include "LightPoint.h"

using namespace std;

RGBColor white(255,255,255);
RGBColor blue(67,100,230);

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
            scene.addObject(&obj);
            // Material m = materials[materialName];
            // Object obj = Object(&sp, &m);
            // scene.addObject(&obj);
        }
    }
    cout << "finished reading.\n";
}


int main(int args, char** argv) {
    cam = Camera(Point3D(0, 0, 0), Vector3D(0, 0, 1), Vector3D(0, 1, 0), pi/2, 1, 2);

    Geometry *E1 = new Sphere(Point3D(-3, 0, 9), 1);
    Material M1 = Material(RGBColor(198, 78, 71), 0.50754,0.508273, 0.3, 0.4);
    Object obj =  Object(E1, &M1);
    scene.addObject(&obj);

    Geometry *E2 = new Sphere(Point3D(0, 1605, 50), 1600);
    Material M2 = Material(RGBColor(0, 255, 0), 0.01, 0.50, 0.5, 0.25);
    Object obj2 = Object(E2, &M2);
    scene.addObject(&obj2);

    Geometry *E3 = new Sphere(Point3D(3, 0, 9), 1);
    Material M3 = Material(RGBColor(0, 0, 255), 0.45, 0.1, 0.8, 3);
    Object obj3 = Object(E3, &M3);
    scene.addObject(&obj3);

    // Add Light
    LightPoint light1(Point3D(-10, -20, 0), 0.5, white);
    // scene.addLight(light1);
    LightPoint light2(Point3D(10, -20, 0), 1, white);
    scene.addLight(light2);

    res_w = 600, res_h = 300;
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