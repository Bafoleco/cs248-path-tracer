//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_POINTLIGHT_H
#define PATH_TRACER_POINTLIGHT_H


#include "../types.h"

class PointLight {
public:
    PointLight(const Vec3 &pos, const Color &color, double intensity);

    Vec3 pos;
    Color color;
    double intensity;
};


#endif //PATH_TRACER_POINTLIGHT_H
