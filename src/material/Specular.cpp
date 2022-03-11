//
// Created by Bay Foley-Cox on 3/8/22.
//

#include "Specular.h"
#include "../constants.h"
#include "../util.h"

Specular::Specular(const Color &color) : color(color) {}

void Specular::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    Vec3 outgoing = bsdfSampleInfo->outgoing;
    Vec3 oSpherical = toSpherical(outgoing);

    double theta = oSpherical[0];
    double phi = oSpherical[1];

    if (!std::isfinite(phi)) {
        phi = 0;
        printf("bad phi\n");
    }

    Vec3 incoming = toCartesian(Vec3(theta, phi + PI, 1));
    bsdfSampleInfo->incoming = incoming;
    bsdfSampleInfo->density = 1;
    bsdfSampleInfo->reflectivity = color / std::abs(cos(theta));
    bsdfSampleInfo->delta = true;
}

void Specular::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    bsdfSampleInfo->density = 0;
    bsdfSampleInfo->reflectivity = Vec3(0, 0, 0);
    bsdfSampleInfo->delta = true;
}
