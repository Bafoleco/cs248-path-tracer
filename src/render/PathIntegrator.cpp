//
// Created by Bay Foley-Cox on 3/6/22.
//

#include <iostream>
#include "PathIntegrator.h"
#include "../scene/Scene.h"
#include "../util.h"

#define MAX_BOUNCES 8

//TODO verify all path tracing math, particularly use of densities

Light sampleIncomingLight(Scene *scene, Object* object, Vec3 hitPos, Vec3 outgoing) {

    int numLights = scene->getLights().size();
    int randIndex = std::floor(rand_double() * numLights);
    LightSource* lightSource = scene->getLights()[randIndex];

    LightSampleInfo lightSampleInfo;
    lightSource->sampleLight(&lightSampleInfo, hitPos);

    Vec3 lightDir = -1 * (((PointLight*) lightSource)->pos - hitPos).normalized();

    BSDFSampleInfo reflectionInfo;
    reflectionInfo.outgoing = outgoing;
    reflectionInfo.incoming = lightSampleInfo.dir;
    object->getReflectionInfo(&reflectionInfo, hitPos);

    if (scene->is_obstructed(hitPos, lightSampleInfo.sourcePos)) {
        return Light(0, 0, 0);
    }

    if (lightSource->isDeltaLight()) {
        Light incomingLight = lightSampleInfo.color * lightSampleInfo.intensity / (lightSampleInfo.sourcePos - hitPos).squaredNorm();
        incomingLight = incomingLight.cwiseProduct(reflectionInfo.reflectivity *
                                                   std::abs(lightSampleInfo.dir.dot(object->getNormal(hitPos))));

        return numLights * incomingLight;
    } else {
        Light incomingLight = lightSampleInfo.color * lightSampleInfo.intensity / (lightSampleInfo.sourcePos - hitPos).squaredNorm();
        incomingLight = incomingLight.cwiseProduct(reflectionInfo.reflectivity *
                                                   std::abs(lightSampleInfo.dir.dot(object->getNormal(hitPos)))) ;
        incomingLight /= lightSampleInfo.density;
        return numLights * incomingLight;
    }

}

//https://www.pbr-book.org/3ed-2018/Light_Transport_I_Surface_Reflection/Path_Tracing
Light PathIntegrator::sample(Scene *scene, const Ray& initial) {

    hit_info hi = hit_info();
    BSDFSampleInfo incomingSample;

    Color beta(1,1,1);
    Light light(0, 0, 0);
    int bounces = 0;

    Ray ray(initial.pos, initial.dir);
    while (bounces < MAX_BOUNCES) {
        //Intersect ray with scene
        scene->find_closest_hit(&ray, &hi);
        Object* hit_object = hi.object;
        Vec3 hitPos = ray.posAt(hi.t);

        //End path if necessary
        if(hit_object == nullptr) {
            //we're done
            break;
        }

        //add emitted light if necessary
        if (bounces == 0 || incomingSample.delta) {
            Light emittedLight = hit_object->getMaterial(hitPos).getEmittedLight();
            light += beta.cwiseProduct(emittedLight);
        }


        //contribution of this path
        light += beta.cwiseProduct(sampleIncomingLight(scene, hit_object, hitPos, -1 * ray.dir));

        //get next direction
        incomingSample.outgoing = -1 * ray.dir;
        hit_object->sampleReflection(&incomingSample, hitPos);
        Vec3 nextRayDir = incomingSample.incoming;
        beta = beta.cwiseProduct(incomingSample.reflectivity *
                std::abs(nextRayDir.dot(hit_object->getNormal(hitPos))) / incomingSample.density);

        if (beta.norm() <= 0.0001) {
            break;
        }

        ray.pos = hitPos;
        ray.dir = nextRayDir;

        //russian roulette
        if (bounces > 3) {
            double q = std::max(0.05, 1 - beta[1]);
            if (rand_double() < q) {
                break;
            }
            beta /= 1 - q;
        }

        bounces++;
    }

    return light;
}
