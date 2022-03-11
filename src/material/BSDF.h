//
// Created by Bay Foley-Cox on 3/5/22.
//

#ifndef PATH_TRACER_BSDF_H
#define PATH_TRACER_BSDF_H

#include "../types.h"

struct BSDFSampleInfo {
    Vec3 outgoing;
    Vec3 incoming;
    double density;
    Color reflectivity;
    bool delta;
};

class BSDF {

public:
    /*
     * We will operate in the frame of reference of the surface, where z is the surface normal
     */
    virtual void sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const = 0;
    virtual void getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const = 0;

    virtual ~BSDF();

private:


};


#endif //PATH_TRACER_BSDF_H
