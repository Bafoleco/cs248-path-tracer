//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_DIFFUSE_H
#define PATH_TRACER_DIFFUSE_H


#include "BSDF.h"
#include "Eigen/Core"
#include "Eigen/Geometry"

class Diffuse : public BSDF {
public:
    Diffuse(const Color &color);

    void sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

    void getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

private:
    Color color;
};


#endif //PATH_TRACER_DIFFUSE_H
