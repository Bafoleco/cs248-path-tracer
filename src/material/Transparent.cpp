//
// Created by Bay Foley-Cox on 3/8/22.
//

#include "Transparent.h"
#include "../util.h"
#include "../constants.h"

void Transparent::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    Vec3 outgoing = bsdfSampleInfo->outgoing;
    bsdfSampleInfo->reflectivity = color;
    bsdfSampleInfo->delta = true;
    bsdfSampleInfo->density = 1;

    //TODO total internal refletion
    Vec3 sphericalOutgoing = toSpherical(outgoing);

    double theta = sphericalOutgoing[0];
    double phi = sphericalOutgoing[1];

    double new_theta;
    double new_phi = phi + PI;
    if (flipped_normal) {
        //entering material
        new_theta = asin(ior * sin(theta));
    } else {
        //leaving material
        new_theta = asin(sin(theta) / ior);
    }

    bsdfSampleInfo->incoming = Vec3(1,1,-1).cwiseProduct(toCartesian(Vec3(new_theta, new_phi, 1)));

    assert(bsdfSampleInfo->incoming.dot(outgoing) < 0);
}

void Transparent::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {

}

Transparent::Transparent(const Color &color, double ior) : ior(ior), color(color) {}
