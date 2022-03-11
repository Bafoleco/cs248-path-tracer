//
// Created by Bay Foley-Cox on 3/4/22.
//

#ifndef PATH_TRACER_SCENE_H
#define PATH_TRACER_SCENE_H

#include <vector>
#include "../geometry/Object.h"
#include "Bvh.h"
#include "../geometry/Ray.h"
#include "Camera.h"
#include "../lights/PointLight.h"

class Scene {
public:
    Scene(const std::vector<Object*> &objects, std::vector<LightSource*> lights, Camera camera);

    const Camera &getCamera() const;

    void printBvh();
    void find_closest_hit(Ray* ray, hit_info* closest);
    bool is_obstructed(Vec3 a, Vec3 b);
    const std::vector<LightSource*> &getLights() const;

private:
        Camera camera;
        std::vector<Object*> objects;
        std::vector<LightSource*> lights;
        Bvh* bvh;
};

#endif //PATH_TRACER_SCENE_H
