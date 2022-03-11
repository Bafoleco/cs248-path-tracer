//
// Created by Bay Foley-Cox on 3/6/22.
//

#include "Sphere.h"
#include "Eigen/Geometry"
#include "Eigen/Core"

Vec3 Sphere::getMaxCords() const {
    return pos + Vec3(radius, radius, radius);
}

Vec3 Sphere::getMinCords() const {
    Vec3 minCords = pos - Vec3(radius, radius, radius);
    return minCords;
}

Sphere::Sphere(const Vec3 &pos, double radius, Material &material, std::string name) : Object(pos, material, name), radius(radius) {}

double Sphere::intersect(Ray *ray) const {
    Vec3 origin = ray->pos;
    Vec3 dir = ray->dir;

    double underRoot = std::pow(dir.dot(origin - pos), 2) - ((origin - pos).squaredNorm() - radius * radius);

    if (underRoot < 0) {
        return -1;
    }

    double solution1 = -1 * dir.dot(origin - pos) + std::sqrt(underRoot);
    double solution2 = -1 * dir.dot(origin - pos) - std::sqrt(underRoot);

    if (std::min(solution1, solution2) >= 0) {
        return std::min(solution1, solution2);
    }
    return std::max(solution1, solution2);
}

Vec3 Sphere::getNormal(Vec3 pos) const {
    //we trust this position is on the sphere
    return (pos - this->pos).normalized();
}

