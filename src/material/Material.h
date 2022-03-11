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

    Material(const Color &emittance, BSDF *bsdf);

    const Color &getEmittance() const;

    Vec3 sampleIncomingDir(Vec3 outgoingDir, Vec3 normal);

    BSDF *getBsdf() const;

private:
    Color emittance;
    BSDF* bsdf;


    //where do we want to sampleReflection surface reflectance
    //object can use material information to handle reflectance requests

};


#endif //PATH_TRACER_MATERIAL_H
