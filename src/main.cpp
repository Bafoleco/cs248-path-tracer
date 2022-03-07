#include <iostream>
#include <vector>
#include "geometry/Object.h"
#include "scene/Bvh.h"
#include "scene/Scene.h"
#include "constants.h"
#include "geometry/Sphere.h"
#include "geometry/Triangle.h"
#include "geometry/Plane.h"
#include <random>
#include <math.h>

double rand_double() {
    return ((double) rand() / (RAND_MAX));
}

int main() {
//    std::time_t result = std::time(nullptr);
    srand(12);

    std::vector<Object*> objects;

    Material m1 = Material(Vec3(0,0,1));
    Material m2 = Material(Vec3(1,0,0));

    double s = 10;

    //constant z
    Plane p0(Vec3(-1 * s, -1 * s, -1), Vec3(-1 * s, s, -1), Vec3(s, -1 * s, -1), Vec3(s, s, -1), m1);
    Plane p1(Vec3(-1 * s, -1 * s, s), Vec3(-1 * s, s, s), Vec3(s, -1 * s, s), Vec3(s, s, s), m1);

    //constant x
    Plane p2(Vec3(-1 * s, -1 * s, -1), Vec3(-1*s, -1 * s, s), Vec3(-1*s, s, -1), Vec3(-1*s, s, s), m1);
    Plane p3(Vec3(s, -1 * s, -1), Vec3(s, -1 * s, s), Vec3(s, s, 0), Vec3(s, s, s), m1);

    //constant y
    Plane p4(Vec3(-1 * s, -1 * s, -1), Vec3(-1 * s, -1 * s, s), Vec3(s, -1 * s, -1), Vec3(s, -1 * s, s), m1);
    Plane p5(Vec3(-1 * s, s, -1), Vec3(-1 * s, s, s), Vec3(s, s, -1), Vec3(s, s, s), m1);

    objects.push_back(&p0);
    objects.push_back(&p1);
    objects.push_back(&p2);
    objects.push_back(&p3);
    objects.push_back(&p4);
    objects.push_back(&p5);


    Sphere o3(Vec3(3, 8, 2), 0.5, m2);
    Sphere o4(Vec3(-1, 12, 1), 0.5, m2);
    Sphere o5(Vec3(0, 4, 0), 0.5, m2);

    objects.push_back(&o3);
    objects.push_back(&o4);
    objects.push_back(&o5);

    Camera camera(ORIGIN, Vec3(0, 1, 0), M_PI / 3, M_PI / 2, 1, 1000, 500);
    Scene scene(objects, camera);
//    scene.printBvh();

    scene.render();
    return 0;
}
