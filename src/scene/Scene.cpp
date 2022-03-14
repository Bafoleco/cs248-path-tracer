//
// Created by Bay Foley-Cox on 3/4/22.
//

#include "Scene.h"
#include "../render/PathIntegrator.h"
#include "../util.h"
#include "../constants.h"
#include "../lights/AreaLight.h"
#include<iostream>

void find_closest_hit_r(Bvh* bvh, Ray *ray, hit_info *closest) {
    Vec3 pos = ray->pos;
    Vec3 dir = ray->dir;

    if(bvh->isLeaf()) {
        for (auto &o : bvh->getObjects()) {
            double t = o->intersect(ray);
            if (t > 0 + EPS && t < closest->t) {
                closest->t = t;
                closest->object = o;
            }
        }
    } else {
        bbox_isect_info hit1 = bvh->getA()->intersect(ray);
        bbox_isect_info hit2 = bvh->getB()->intersect(ray);

        if (hit1.hit && hit2.hit) {
            Bvh* first = (hit1.t <= hit2.t) ? bvh->getA() : bvh->getB();
            Bvh* second = (hit1.t <= hit2.t) ? bvh->getB() : bvh->getA();
            find_closest_hit_r(first, ray, closest);
            if (std::max(hit2.t, hit1.t) < closest->t) {
                find_closest_hit_r(second, ray, closest);
            }
        } else if(hit1.hit) {
            find_closest_hit_r(bvh->getA(), ray, closest);
        } else if(hit2.hit) {
            find_closest_hit_r(bvh->getB(), ray, closest);
        }
    }
}

bool is_obstructed_r(Bvh* bvh, Vec3 a, Vec3 b) {
    Ray ray(a, (b-a).normalized());
    if(bvh->isLeaf()) {
        for (auto &o : bvh->getObjects()) {
            double t = o->intersect(&ray);
            if (t >= 0 && t <= (b-a).norm()) {
//                printf("%f \n", t);
//                printf("-----\n");
//                std::cout << ray.posAt(t) << std::endl;
//                double huh = (b-a).norm();
                return true;
            }
        }
        return false;
    } else {
        bbox_isect_info hit1 = bvh->getA()->intersect(&ray);
        bbox_isect_info hit2 = bvh->getB()->intersect(&ray);

        if (hit1.hit && hit2.hit) {
            return is_obstructed_r(bvh->getA(), a, b) || is_obstructed_r(bvh->getB(), a, b);
        } else if(hit1.hit) {
            return is_obstructed_r(bvh->getA(), a, b);
        } else if(hit2.hit) {
            return is_obstructed_r(bvh->getB(), a, b);
        }
    }
    return false;
}

bool Scene::is_obstructed(Vec3 a, Vec3 b) {
    Vec3 dir = (b-a).normalized();
    a = a + dir * EPS;
    b = b - dir * EPS;

    return is_obstructed_r(bvh, a, b);
}

void Scene::find_closest_hit(Ray *ray, hit_info *closest) {
    closest->t = 10000;
    closest->object = nullptr;
    find_closest_hit_r(bvh, ray, closest);
}

Scene::Scene(std::vector<Object *> &objects, std::vector<LightSource*> lights, Camera camera) :
    objects(objects), lights(std::move(lights)), camera(camera) {

    for (auto &l : this->lights) {
        if (l->getLightSourceType() == AREA_LIGHT) {
            objects.push_back(((AreaLight *) l)->getPlane());
        }
    }
    bvh = new Bvh(objects);
}

void Scene::printBvh() {
    bvh->printBVH();
}

const std::vector<LightSource*> &Scene::getLights() const {
    return lights;
}

const Camera &Scene::getCamera() const {
    return camera;
}
