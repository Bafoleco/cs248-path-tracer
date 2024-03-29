//
// Created by Bay Foley-Cox on 3/10/22.
//

#ifndef PATH_TRACER_FRESNEL_H
#define PATH_TRACER_FRESNEL_H


#include "BSDF.h"

class Fresnel : public BSDF {

public:
    void sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

    void getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

    Fresnel(double ior, const Color &reflectionColor, const Color &transmissionColor);

private:
    double ior;
    Color reflectionColor;
    Color transmissionColor;
};


#endif //PATH_TRACER_FRESNEL_H
