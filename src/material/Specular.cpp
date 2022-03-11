//
// Created by Bay Foley-Cox on 3/8/22.
//

#include "Specular.h"
#include "../constants.h"
#include "../util.h"

Specular::Specular(const Color &color) : color(color) {}

void Specular::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    Vec3 outgoing = bsdfSampleInfo->outgoing;
    double theta = acos(outgoing[2]);
    double phi = atan(outgoing[0] / outgoing[1]);

    if (!std::isfinite(phi)) {
        phi = 0;
        printf("bad phi\n");
    }

    double newTheta = theta;
    double newPhi = phi + PI;

    Vec3 incoming = toCartesian(Vec3(newTheta, newPhi, 1));
    bsdfSampleInfo->incoming = incoming;
    bsdfSampleInfo->density = 1;
    bsdfSampleInfo->reflectivity = color;
    bsdfSampleInfo->delta = true;
}

void Specular::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    bsdfSampleInfo->density = 0;
    bsdfSampleInfo->reflectivity = Vec3(0, 0, 0);
    bsdfSampleInfo->delta = true;
}
