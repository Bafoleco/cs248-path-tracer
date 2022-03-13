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
#include "examples/TestScenes.h"
#include <math.h>

int main() {

    TestScenes::classicScene();
//    TestScenes::testFresnel();
//    TestScenes::testFresnelCornell();
//    TestScenes::testSpecular();

    return 0;
}
