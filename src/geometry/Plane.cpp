//
// Created by Bay Foley-Cox on 3/6/22.
//

#include "Plane.h"

Vec3 Plane::getMinCords() const {
    return bbox.first;
}

Vec3 Plane::getMaxCords() const {
    return bbox.second;
}

double Plane::intersect(Ray *ray) const {
    double t = t1.intersect(ray);
    if (t >= 0) {
        return t;
    }
    return t2.intersect(ray);
}

Vec3 Plane::getNormal(Vec3 pos) const {
    return normal;
}

Plane::Plane(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, Material &material)
        : Object(Vec3(0, 0, 0), material), t1(p0, p1, p2, material), t2(p1, p2, p3, material) {

    this->setPos((p0 + p1 + p2 + p3)/4);
    Vec3 basis1 = (p1 - p0);
    Vec3 basis2 = (p2 - p0);
    normal = basis1.cross(basis2);
    c = normal.dot(p3);

    bbox = {p0.cwiseMin(p1).cwiseMin(p2).cwiseMin(p3),
            p0.cwiseMax(p1).cwiseMax(p2).cwiseMax(p3)};
}
