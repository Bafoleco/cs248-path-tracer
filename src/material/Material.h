//
// Created by Bay Foley-Cox on 3/5/22.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include <opencv2/core/matx.hpp>
#include "../types.h"
#include "BSDF.h"

class Material {
public:

    Material(BSDF *bsdf);
    BSDF *getBsdf() const;

    Light getEmittedLight();

    Material(BSDF *bsdf, Color emissionColor, double emissionIntensity);

private:
    BSDF* bsdf;
    Color emissionColor;
    double emissionIntensity;
};

#endif //PATH_TRACER_MATERIAL_H
