//
// Created by Bay Foley-Cox on 3/4/22.
//

#ifndef PATH_TRACER_RAY_H
#define PATH_TRACER_RAY_H

#include <Eigen/Dense>
#include "../types.h"

class Ray {
public:
    Ray(const Vec3 &pos, const Vec3 &dir);
    Vec3 posAt(double t);
    Vec3 pos;
    Vec3 dir;
};


#endif //PATH_TRACER_RAY_H
