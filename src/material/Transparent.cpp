//
// Created by Bay Foley-Cox on 3/8/22.
//

#include "Transparent.h"
#include "../util.h"
#include "../constants.h"

void Transparent::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    Vec3 outgoing = bsdfSampleInfo->outgoing;

    //TODO total internal reflection
    Vec3 sphericalOutgoing = toSpherical(outgoing);
    double theta = sphericalOutgoing[0];
    double phi = sphericalOutgoing[1];

    double n1 = 1;
    double n2 = ior;
    double sinThetaO = sin(theta);
    if (flipped_normal) {
        //entering material
        std::swap(n1, n2);
    }
    double sinThetaI = n1 * sinThetaO / n2;

    if (sinThetaI > 1.0) {
        //total internal reflection
        bsdfSampleInfo->incoming = toCartesian(Vec3(theta, phi + PI, 1));
        bsdfSampleInfo->reflectivity = color / cos(theta);
    } else {
        double newTheta = asin(sinThetaI);
        bsdfSampleInfo->reflectivity = color / cos(theta);
        bsdfSampleInfo->incoming = Vec3(1,1,-1).cwiseProduct(toCartesian(Vec3(newTheta, phi + PI, 1)));
    }

    bsdfSampleInfo->delta = true;
    bsdfSampleInfo->density = 1;
}

void Transparent::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    bsdfSampleInfo->density = 0;
    bsdfSampleInfo->reflectivity = Vec3(0, 0, 0);
    bsdfSampleInfo->delta = true;
}

Transparent::Transparent(const Color &color, double ior) : ior(ior), color(color) {}
