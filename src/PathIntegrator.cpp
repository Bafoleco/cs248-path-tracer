//
// Created by Bay Foley-Cox on 3/6/22.
//

#include "PathIntegrator.h"
#include "scene/Scene.h"

#define MAX_BOUNCES 3

Light getIncomingLight(Vec3) {

}

//https://www.pbr-book.org/3ed-2018/Light_Transport_I_Surface_Reflection/Path_Tracing
Light PathIntegrator::sample(Scene scene, Ray *ray) {

    int bounces = 0;

    hit_info hi = hit_info();
    scene.find_closest_hit(ray, &hi);

    Light light(0, 0, 0);

    double beta = 1;
    while (bounces < MAX_BOUNCES) {

        Object* hit_object = hi.object;
        if(hit_object == nullptr) {
            //we're done, sample lighting
//            getIncomingLight()

            //TODO lighting
        }

        Vec3 hitPos = ray->posAt(hi.t);

        //contribution of this path


        //sample next direction
        Material m = hit_object->getMaterial(hitPos);
        Vec3 nextRayDir = m.sampleIncomingDir(-1 * ray->dir, hit_object->getNormal(hitPos));

        ray->pos = hitPos;
        ray->dir = nextRayDir;
        scene.find_closest_hit(ray, &hi);


        bounces++;
    }

    return light;
}
