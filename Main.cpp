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
map<string, Material*> materials;

const double pi = 3.14159265;

// recebe o caminho do arquivo de entrada como uma string, e lê como a especificação sugere, sendo as variáveis da cena globais
void read(const string &path_in) {
    string str;
    cout << path_in << endl;
    fstream in(path_in);
    
    while(in >> str) {
        if(str == "res") {
            in >> res_w >> res_h;
        } else if(str == "camera") {
            double px, py, pz, tx, ty, tz, ux, uy, uz, fov, f;
            in >> px >> py >> pz >> tx >> ty >> tz >> ux >> uy >> uz >> fov >> f;
            cam = Camera(Point3D(px, py, pz), Vector3D(tx, ty, tz), Vector3D(ux, uy, uz), fov, f, 1.7);
        } else if(str == "material") {
            string name;
            double r, g, b, kd, ks, ke, alpha, kt, kr;
            int isRefra, isRefle;
            in >> name >> r >> g >> b >> kd >> ks >> ke >> alpha >> isRefra >> kr >> isRefle >> kt;
            materials[name] = new Material(RGBColor(r, g, b), kd, ks, ke, alpha, isRefra, kr, isRefle);
        } else if(str == "sphere") {
            double cx, cy, cz, r;
            string materialName;
            in >> cx >> cy >> cz >> r >> materialName;
            Geometry *sp = new Sphere(Point3D(cx, cy, cz), r);
            Object *obj = new Object(sp, materials[materialName]);
            scene.addObject(obj);
        }
    }
    cout << "finished reading.\n";
}


int main(int args, char** argv) {
   read("./in2.txt");
    LightPoint light2(Point3D(10, -20, 0), 0.5, white);
    scene.addLight(light2);
    
    Image img(res_w, res_h);

    cout << "CAMERA: "<<endl;
    cout << cam.toString();

    cout << "objects(" << scene.objects.size() <<"):\n";
    for(auto objPtr : scene.objects) {
        cout << "{ ";
        cout << objPtr->geometry->toString() << "}\n\n";
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