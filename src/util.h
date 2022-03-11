//
// Created by Bay Foley-Cox on 3/6/22.
//

#include <cstdlib>
#include "types.h"
#include <opencv2/core/matx.hpp>

#ifndef PATH_TRACER_UTIL_H
#define PATH_TRACER_UTIL_H

double rand_double();
cv::Vec3b rgbFromColor(Color c);

Vec3 toSpherical(Vec3 cartesian);
Vec3 toCartesian(Vec3 spherical);

#endif //PATH_TRACER_UTIL_H
