//
// Created by Bay Foley-Cox on 3/4/22.
//

#include "Ray.h"

Vec3 Ray::posAt(double t) {
    return pos + dir * t;
}

Ray::Ray(const Vec3 &pos, const Vec3 &dir) : pos(pos), dir(dir) {}
