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
    cam = Camera(Point3D(0, 0, 0), Vector3D(0, 0, 1), Vector3D(0, 1, 0), pi/2, 1, 1.7);

    Geometry *E1 = new Sphere(Point3D(0, 0, 9), 1);
    Material M1 = Material(RGBColor(198, 78, 71), 0.50754,0.8, 0.3, 0.4, false, 1.8, false);
    Object obj =  Object(E1, &M1);
    scene.addObject(&obj);

    Geometry *E2 = new Sphere(Point3D(0, 1605, 50), 1600);
    Material M2 = Material(RGBColor(0, 255, 0), 0.5, 0.50, 0.5, 0.25, false, 1, false);
    Object obj2 = Object(E2, &M2);
    scene.addObject(&obj2);

    Geometry *E3 = new Sphere(Point3D(-3, 0, 9), 1);
    Material M3 = Material(RGBColor(255, 255, 255), 0, 0.1, 0.1, 3, true, 1.33, false);
    Object obj3 = Object(E3, &M3);
    scene.addObject(&obj3);

    Geometry *E5 = new Sphere(Point3D(-4.3, 0, 14), 1);
    Material M5= Material(RGBColor(0, 0, 255), 0.8, 0.6, 0.8, 3, false, 0.5, false);
    Object obj5 = Object(E5, &M5);
    scene.addObject(&obj5);

    Geometry *E6 = new Sphere(Point3D(4.3, 0, 14), 1);
    Material M6= Material(RGBColor(255, 0, 0), 0.8, 0.6, 0.8, 3, false, 0.5, false);
    Object obj6 = Object(E6, &M6);
    scene.addObject(&obj6);

    // REFRACTIVE OBJECT
    Geometry *E4 = new Sphere(Point3D(3, 0, 9), 1);
    Material M4 = Material(RGBColor(255, 0, 0), 0.45, 1, 0.8, 3, true, -0.5, false);
    Object obj4 = Object(E4, &M4);
    scene.addObject(&obj4);

    // Add Light
    LightPoint light1(Point3D(-10, -20, 0), 0.3, white);
    scene.addLight(light1);

    res_w = 1280, res_h = 720;
    Image img(res_w, res_h);

    cout << "CAMERA: "<<endl;
    cout << cam.toString();

    cout << "objects(" << scene.objects.size() <<"):\n";
    for(auto objPtr : scene.objects) {
        cout << "{ ";
        Object o = *objPtr;
        cout << o.geometry->toString() << "}\n\n";
    }

    cout << "starting to throw rays";
    for(int i = 0; i < img.height; i++) {
        if(i == img.height/3) cout << ".";
        if(i == 2*img.height/3) cout << ".";
        if(i == img.height-1) cout << ". ";
        for(int j = 0; j < img.width; j++) {
            Ray r   = cam.getRay(double(j), double(i), res_w, res_h);
            img.setPixel(i, j, scene.trace(r, 0, 1));
        }
    }

    cout << "done.\n";

    img.saveAsPBM(""); // saving as out

    return 0;
}