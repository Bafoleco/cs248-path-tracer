//
// Created by Bay Foley-Cox on 3/4/22.
//

#include "Scene.h"
#include<opencv2/opencv.hpp>
#include<iostream>

void find_closest_hit_r(Bvh* bvh, Ray *ray, hit_info *closest) {
    Vec3 pos = ray->pos;
    Vec3 dir = ray->dir;

    if(bvh->isLeaf()) {
        for (auto &o : bvh->getObjects()) {
            double t = o->intersect(ray);
            if (t >= 0 && t < closest->t) {
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

void Scene::find_closest_hit(Ray *ray, hit_info *closest) {
    find_closest_hit_r(bvh, ray, closest);
}

Scene::Scene(const std::vector<Object*> &objects, Camera camera) : objects(objects), camera(camera) {
    bvh = new Bvh(objects);
}

void Scene::printBvh() {
    bvh->printBVH();
}



cv::Vec3b rgbFromColor(Color c) {
    return cv::Vec3b(c[2] * 255, c[1] * 255, c[0] * 255);
}

void Scene::render() {

    int num_cols = camera.getNumCols();
    int num_rows = camera.getNumRows();
    cv::Mat render(num_rows, num_cols, CV_8UC3);
    for (int i = 0; i < num_rows; i++) {
        if (i % 5 == 0) {
            printf("row %d\n", i);
        }
        for (int j = 0; j < num_cols; j++) {
            Vec3 ray_dir = camera.getPixelDir(j + 0.5, i + 0.5);
            Ray r(camera.getPos(), ray_dir);

            hit_info hi = hit_info();
            find_closest_hit(&r, &hi);

            if (hi.object != nullptr) {
                render.at<cv::Vec3b>(i,j) = (2.0 / (hi.t + 1)) * rgbFromColor(hi.object->getMaterial(Vec3()).getEmittance());
            }
        }
    }

    namedWindow("render output",cv::WINDOW_AUTOSIZE);
    cv::imshow("render output", render);

    cv::waitKey(0);
    cv::destroyWindow("render output");
    imwrite("render.jpg", render);

}

const std::vector<PointLight> &Scene::getLights() const {
    return lights;
}
