#include <iostream>
#include <vector>
#include "geometry/Object.h"
#include "scene/Scene.h"
#include "constants.h"
#include "geometry/Sphere.h"
#include "geometry/Triangle.h"
#include "geometry/Plane.h"
#include "material/Diffuse.h"
#include "render/Renderer.h"
#include "material/Specular.h"
#include "material/Transparent.h"
#include "lights/AreaLight.h"
#include <math.h>

int main() {
//    std::time_t result = std::time(nullptr);
//    srand(result);
    srand(14);

    std::vector<Object*> objects;

    Diffuse diffuseRed(Color(.9, 0.1, 0.1));
    Diffuse diffuseBlue(Color(0.1, 0.1, .3));
    Diffuse diffuseBlack(Color(0, 0, 0));
    Diffuse diffuseGreen(Color(0.1, 0.9, 0.1));
    Diffuse diffuseWhite(Color(.5, .5, .5));

    Specular specular(Color(1, 1, 1));
    Transparent transparent(Color(.8, .8, .8), 1.5);

    Material m1 = Material(Vec3(1,0,0), &diffuseWhite);
    Material m2 = Material(Vec3(0,0,1), &diffuseBlue);
    Material green = Material(Vec3(0,0,1), &diffuseGreen);
    Material white = Material(Vec3(0,0,1), &diffuseWhite);
    Material red = Material(Vec3(0,0,1), &diffuseRed);
    Material blue = Material(Vec3(0,0,1), &diffuseBlue);
    Material specularMat = Material(Vec3(0,0,1), &specular);
    Material transparentMat = Material(Vec3(1,0,0), &transparent);

    double s = 1.2;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, -1 * s, 0), Vec3(s, s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, -1 * s, s), Vec3(s, s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s), Vec3(-1*s, s, 0), Vec3(-1*s, s, s), white, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, 0), Vec3(s, s, s), white, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, 0), Vec3(s, s, s), white, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere o4(Vec3(0, -.6, 0.5), 0.5, green, "");
    Sphere mirror(Vec3(0, 0.6, 0.5), 0.5, specularMat, "mirror");

    //mirror testing
//    objects.push_back(&o4);
//    objects.push_back(&mirror);

    //transparent testing
    Sphere transparentS(Vec3(0, 0.2, 0.5), 0.5, blue, "transparent");
//    objects.push_back(&o3);
//    objects.push_back(&transparentS);






    //diffuse objects
    Sphere dif1(Vec3(0, .6, 0.5), 0.25, green, "");
    Sphere dif2(Vec3(-.5, .6, 0.5), 0.25, red, "");
    Sphere dif3(Vec3(0.5, .6, 0.5), 0.25, blue, "");

    objects.push_back(&dif1);
    objects.push_back(&dif2);
    objects.push_back(&dif3);

    //lights

    Plane lightPlane(Vec3(-0.2, 0.2, 0.9), Vec3(0.2, 0.2, 0.9),
                     Vec3(0.2, 0.6, 0.9), Vec3(-0.2, 0.6, 0.9), blue,"");

    AreaLight areaLight(Color(1, 1, 1), 0.2, lightPlane);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
//    lights.push_back(&pointLight);
    lights.push_back(&areaLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);
    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6,  1000, true);

//    Vec3 dir(0, -1, 0);


    return 0;
}
