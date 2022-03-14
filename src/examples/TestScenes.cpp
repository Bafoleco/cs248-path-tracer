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
Diffuse diffuseBlue(Color(0.1, 0.1, .8));
Diffuse diffuseBlack(Color(0.01, 0.01, 0.01));
Diffuse diffuseGreen(Color(0.1, 0.8, 0.1));
Diffuse diffuseWhite(Color(.5, .5, .5));
Diffuse diffusePurple(Color(.8, .1, .8));

Material m1 = Material(&diffuseWhite);
Material m2 = Material(&diffuseBlue);
Material green = Material(&diffuseGreen);
Material white = Material( &diffuseWhite);
Material red = Material( &diffuseRed);
Material blue = Material(&diffuseBlue);
Material purple = Material(&diffusePurple);

Specular specular(Color(1, 1, 1));
Material specularMat = Material(&specular);
Transparent transparent(Color(1, 1, 1), 3);
Material transparentMat = Material(&transparent);

void TestScenes::testSpecular(int num_samples) {

    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), red, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), green, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), specularMat, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere toReflect(Vec3(0, -.6, 0.5), 0.3, green, "");
    Sphere toReflect2(Vec3(-0.5, .6, 0.4), 0.2, red, "");

    //mirror testing
    objects.push_back(&toReflect);
    objects.push_back(&toReflect2);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, num_samples, true, "wall_mirror.jpg");
}

void TestScenes::testTransmission() {
    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), red, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), green, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

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
    renderer.render(6, 100, true, "render.jpg");
}

void TestScenes::classicScene(double lr, std::string filename, int num_samples, double yOff) {
    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), red, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), green, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

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

    Plane lightPlane(Vec3(-lr, yOff,  s - EPS), Vec3(lr, yOff, s - EPS), Vec3(lr, lr + yOff, s - EPS), Vec3(-lr, lr + yOff, s - EPS), blue,"lightPlane");

    AreaLight areaLight(Color(1, 1, 1), 0.25, lightPlane);

    std::vector<LightSource*> lights;
    lights.push_back(&areaLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, num_samples, false, filename);
}

void TestScenes::classicSceneHard(std::string filename, int num_samples) {
    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), red, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), green, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

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


    PointLight pointLight(Vec3(0, 0.4, s - EPS), Vec3(1, 1, 1), 0.25);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, num_samples, false, filename);
}

void TestScenes::testFresnel() {
    double s = 1.6;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), red, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), green, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere b(Vec3(0, 1.6, 0.4), 0.3, purple, "");

    Fresnel fresnel(1.5, Color(1,1,1), Color(1,1,1));
    Material glass(&fresnel);
    Sphere transparentS(Vec3(0, 0.7, 0.6), 0.4, glass, "transparent");

    objects.push_back(&b);
    objects.push_back(&transparentS);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.05);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, 1000, true, "fresnel1.jpg");
}

void TestScenes::testFresnelCornell() {
    double s = 2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), white, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), white, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere a(Vec3(-0.4, 1.7, 0.4), 0.4, green, "");
    Sphere b(Vec3(0.4, 1.7, 0.4), 0.4, red, "");

    Fresnel fresnel(1.00, Color(1,1,1), Color(1,1,1));
    Material glass(&fresnel);
    Sphere transparentS(Vec3(0, 1.0, 0.4), 0.4, glass, "transparent");

    objects.push_back(&a);
    objects.push_back(&b);
    objects.push_back(&transparentS);

    PointLight pointLight(Vec3(0, 0.5, 1), Color(1, 1, 1), 0.1);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0.01, 0.7), Vec3(0, 1, -0.1), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, 30, true, "fresnel/fresnel.jpg");
}

void TestScenes::bigSmall(int num_samples) {
    double s = 1.5;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), white, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), white, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere a(Vec3(-0.4, 1.3, 0.1), 0.1, green, "");
    Sphere b(Vec3(0, 1.6, 0.1), 0.1, red, "");
    Sphere c(Vec3(-0.7, 0.4, 0.1), 0.1, blue, "");
    Sphere d(Vec3(-0.7, 0.4, 0.1), 0.1, purple, "");

    Fresnel fresnel(1.5, Color(1,1,1), Color(1,1,1));
    Material glass(&fresnel);
    Sphere transparentS(Vec3(0, 0.7, 0.5), 0.5, glass, "transparent");

    objects.push_back(&a);
    objects.push_back(&b);
    objects.push_back(&c);
    objects.push_back(&d);
    objects.push_back(&transparentS);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, -0.1), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, 20, true, "big_small.jpg");
}

void TestScenes::testExtraSpecular(int num_samples) {

    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), specularMat, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), specularMat, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), specularMat, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), specularMat, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), specularMat, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), specularMat, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere toReflect(Vec3(0.3, .6, 0.5), 0.3, green, "");
    Sphere toReflect2(Vec3(-0.5, .6, 0.4), 0.2, red, "");

    objects.push_back(&toReflect);
    objects.push_back(&toReflect2);


    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.2);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, num_samples, true, "many_wall_mirror.jpg");
}

void TestScenes::testFresnel2() {
    double s = 1.6;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), white, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), white, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere a(Vec3(-0.4, 1.3, 0.8), 0.25, green, "");
    Sphere b(Vec3(0, 1.3, 0.4), 0.25, red, "");
    Sphere c(Vec3(-0.7, 0.4, 0.4), 0.2, blue, "");

    Fresnel fresnel(1.8, Color(1,1,1), Color(1,1,1));
    Material glass(&fresnel);
    Sphere transparentS(Vec3(0, 0.4, 0.6), 0.15, glass, "transparent");

    objects.push_back(&a);
    objects.push_back(&b);
//    objects.push_back(&c);
//    objects.push_back(&d);
    objects.push_back(&transparentS);

    PointLight pointLight(Vec3(0, 0.4, 1), Color(1, 1, 1), 0.05);
    std::vector<LightSource*> lights;
    lights.push_back(&pointLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, 1000, true, "fresnel1.jpg");
}

void TestScenes::classicSceneAndFresnel(int num_samples) {
    double s = 1.2;

    std::vector<Object*> objects;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, s, 0), Vec3(s, s, 0), Vec3(s, -1 * s, 0), white, "bottom");
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, -1 * s, s), white, "top");
    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, 0), Vec3(-1*s, -1 * s, s),  Vec3(-1*s, s, s),Vec3(-1*s, s, 0), red, "left");
    Plane p3(Vec3(s, -1 * s, 0), Vec3(s, -1 * s, s), Vec3(s, s, s),Vec3(s, s, 0), green, "right");
    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, 0), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, s), Vec3(s, -1 * s, 0), white, "back");
    Plane p5(Vec3(-1 * s, s, 0), Vec3(-1 * s, s, s), Vec3(s, s, s), Vec3(s, s, 0), white, "front");

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);

    Sphere a(Vec3(-0.3,  0.7, 0.6), 0.3, white, "");
    Sphere b(Vec3(.3, 0.6, 0.4), 0.2, specularMat, "");
    Fresnel fresnel(1.8, Color(1,1,1), Color(1,1,1));
    Material glass(&fresnel);
    Sphere c(Vec3(0.2, 0.4, 0.6), 0.15, glass, "transparent");

    objects.push_back(&a);
    objects.push_back(&b);
    objects.push_back(&c);

    double lr = 0.2;
    double yOff = 0.2;
    Plane lightPlane(Vec3(-lr, yOff,  s - EPS), Vec3(lr, yOff, s - EPS), Vec3(lr, lr + yOff, s - EPS), Vec3(-lr, lr + yOff, s - EPS), blue,"lightPlane");

    AreaLight areaLight(Color(1, 1, 1), 0.1, lightPlane);

    std::vector<LightSource*> lights;
    lights.push_back(&areaLight);

    Camera camera(Vec3(0, 0, 0.5), Vec3(0, 1, 0), 160 * ((2 * PI) / 360), 1, 1200, 600);

    Scene scene(objects, lights, camera);

    Renderer renderer(&scene);
    renderer.render(6, num_samples, false, "classicFresnel.jpg");
}
