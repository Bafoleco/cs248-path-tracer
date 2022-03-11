//
// Created by Bay Foley-Cox on 3/8/22.
//

#ifndef PATH_TRACER_TRANSPARENT_H
#define PATH_TRACER_TRANSPARENT_H


#include "BSDF.h"

class Transparent : public BSDF {

public:
    void sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

    Transparent(const Color &color, double ior);

    void getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

private:
    double ior;
    Color color;
};


#endif //PATH_TRACER_TRANSPARENT_H
