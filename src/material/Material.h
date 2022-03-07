//
// Created by Bay Foley-Cox on 3/5/22.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H


#include <opencv2/core/matx.hpp>
#include "../types.h"

class Material {
public:

    Material(const Color &emittance);

    const Color &getEmittance() const;

    Vec3 sampleIncomingDir(Vec3 outgoingDir, Vec3 normal);

private:
    Color emittance;


};


#endif //PATH_TRACER_MATERIAL_H
