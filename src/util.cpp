//
// Created by Bay Foley-Cox on 3/7/22.
//

#include <random>
#include "util.h"
#include "constants.h"

double rand_double() {
    static thread_local std::mt19937 generator;
    std::uniform_real_distribution<> dist(0, 1);
    return dist(generator);
}

cv::Vec3b rgbFromColor(Color c) {
    return cv::Vec3b(std::min(c[2], 1.0) * 255, std::min(c[1], 1.0) * 255, std::min(c[0], 1.0) * 255);
}

Vec3 toSpherical(Vec3 cartesian) {
    double x = cartesian[0];
    double y = cartesian[1];

    double r = cartesian.norm();
    double theta = acos(cartesian[2] / r);
    double phi;
    if (x > 0) {
        phi = atan(y/x);
    } else if (x < 0 && y >= 0) {
        phi = atan(y/x) + PI;
    } else if (x < 0 && y < 0) {
        phi = atan(y/x) - PI;
    } else if (x == 0 && y > 0) {
        phi = PI / 2;
    } else if (x == 0 && y < 0) {
        phi = -1 * PI / 2;
    } else {
        printf("BAD\n");
    }

    Vec3 spherical(theta, phi,cartesian.norm());

    assert((toCartesian(spherical) - cartesian).norm() < 0.001);

    return spherical;
}

Vec3 toCartesian(Vec3 spherical) {
    double theta = spherical[0];
    double phi = spherical[1];
    double r = spherical[2];

    return r * Vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}
