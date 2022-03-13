//
// Created by Bay Foley-Cox on 3/6/22.
//

#include "Triangle.h"
#include "../constants.h"

Vec3 Triangle::getMinCords() const {
    return bbox.first;
}

Vec3 Triangle::getMaxCords() const {
    return bbox.second;
}

double Triangle::intersect(Ray *ray) const {
    double t = (c - normal.dot(ray->pos)) / (normal.dot(ray->dir));
    if (!std::isfinite(t) || t < 0) {
        return -1;
    }

    Vec3 collisionPos = ray->posAt(t);
    Vec3 collisionInTri = (collisionPos - p0);

    double alpha = basis1.cross(collisionInTri).dot(normal);
    double beta = collisionInTri.cross(basis2).dot(normal);

    if (alpha >= 0 && beta >= 0 && (alpha + beta) / (basis1.cross(basis2).dot(normal)) < 1) {
        return t;
    }

    return -1;
}

Vec3 Triangle::getNormal(Vec3 pos) const {
    return normal;
}

Triangle::Triangle(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, Material &material) : Object(pos, material, ""),
                                                                                                          p0(p0),
                                                                                                          p1(p1),
                                                                                                          p2(p2) {
    this->setPos((p0 + p1 + p2) / 3);
    basis1 = (p1 - p0);
    basis2 = (p2 - p0);
    normal = basis1.cross(basis2).normalized();
    c = normal.dot(p1);

    Vec3 minCords = p0.cwiseMin(p1).cwiseMin(p2);
    Vec3 maxCords = p1.cwiseMax(p1).cwiseMax(p2);
    bbox = {minCords, maxCords};
}
