//
// Created by Bay Foley-Cox on 3/8/22.
//

#ifndef PATH_TRACER_SPECULAR_H
#define PATH_TRACER_SPECULAR_H


#include "../types.h"
#include "BSDF.h"

class Specular : public BSDF {
public:
    Specular(const Color &color);

    void sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

    void getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const override;

private:
    Color color;


};


#endif //PATH_TRACER_SPECULAR_H
