//
// Created by Bay Foley-Cox on 3/10/22.
//

#include "TestScenes.h"

#include "../scene/Scene.h"
#include "../material/Specular.h"
#include "../material/Diffuse.h"
#include "../material/Transparent.h"
#include "../geometry/Plane.h"
#include "../constants.h"
#include "../geometry/Sphere.h"
#include "../render/Renderer.h"
#include "../lights/AreaLight.h"
#include "../material/Fresnel.h"

Diffuse diffuseRed(Color(.9, 0.1, 0.1));
Diffuse diffuseBlue(Color(0.1, 0.1, .9));
Diffuse diffuseBlack(Color(0.01, 0.01, 0.01));
Diffuse diffuseGreen(Color(0.1, 0.9, 0.1));
Diffuse diffuseWhite(Color(.5, .5, .5));

Material m1 = Material(Vec3(1,0,0), &diffuseWhite);
Material m2 = Material(Vec3(0,0,1), &diffuseBlue);
Material green = Material(Vec3(0,0,1), &diffuseGreen);
Material white = Material(Vec3(0,0,1), &diffuseWhite);
Material red = Material(Vec3(0,0,1), &diffuseRed);
Material blue = Material(&diffuseBlue);

Specular specular(Color(1, 1, 1));
Material specularMat = Material(Vec3(0,0,1), &specular);
Transparent transparent(Color(1, 1, 1), 3);
Material transparentMat = Material(Vec3(1,0,0), &transparent);

Fresnel fresnel(1.5, Color(1,1,1));
Material glass(&fresnel);

void TestScenes::testSpecular() {

    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, -1 * s, 0), Vec3(s, s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, -1 * s, s), Vec3(s, s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s), Vec3(-1*s, s, 0), Vec3(-1*s, s, s), white, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, 0), Vec3(s, s, s), white, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, 0), Vec3(s, s, s), specularMat, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere toReflect(Vec3(0, -.6, 0.5), 0.3, green, "");
    Sphere toReflect2(Vec3(-0.5, .6, 0.4), 0.2, red, "");

    Sphere mirror(Vec3(0, 0.6, 0.5), 0.3, specularMat, "mirror");

    //mirror testing
    objects.push_back(&toReflect);
    objects.push_back(&toReflect2);

//    objects.push_back(&mirror);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6,  200, true);
}


void TestScenes::testTransmission() {
    double s = 1.2;

    std::vector<Object*> objects;

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

    Sphere a(Vec3(-0.6, 1.2, 0.5), 0.4, green, "");
    Sphere b(Vec3(0, 1, 0.2), 0.2, red, "");

    Sphere transparentS(Vec3(0, 0.4, 0.5), 0.3, transparentMat, "transparent");

    objects.push_back(&a);
    objects.push_back(&b);
    objects.push_back(&transparentS);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6,  100, true);
}

void TestScenes::classicScene() {
    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, -1 * s, 0), Vec3(s, s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, -1 * s, s), Vec3(s, s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s), Vec3(-1*s, s, 0), Vec3(-1*s, s, s), red, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, 0), Vec3(s, s, s), green, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, 0), Vec3(s, s, s), white, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere a(Vec3(-0.3,  0.7, 0.6), 0.3, white, "");
    Sphere b(Vec3(.3, 0.6, 0.4), 0.2, specularMat, "");


    objects.push_back(&a);
    objects.push_back(&b);

    Plane lightPlane(Vec3(-0.2, 0.2, 0.8), Vec3(0.2, 0.2, 0.8),
                     Vec3(0.2, 0.4, 0.8), Vec3(-0.2, 0.4, 0.8), blue,"");

    AreaLight areaLight(Color(1, 1, 1), 0.15, lightPlane);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);
//    lights.push_back(&areaLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);


    Renderer renderer(&scene);
    renderer.render(6,  100, true);
}

void TestScenes::testFresnel() {
    double s = 1.2;

    std::vector<Object*> objects;

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

    Sphere a(Vec3(-0.6, 1.2, 0.5), 0.4, green, "");
    Sphere b(Vec3(0, 1, 0.2), 0.2, red, "");
    Sphere c(Vec3(-0.7, 0.4, 0.4), 0.2, blue, "");

    Sphere transparentS(Vec3(0, 0.5, 0.5), 0.3, glass, "transparent");

    objects.push_back(&a);
    objects.push_back(&b);
    objects.push_back(&c);
    objects.push_back(&transparentS);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6,  50, true);
}