//
// Created by Bay Foley-Cox on 3/10/22.
//

#include "Fresnel.h"
#include "../util.h"
#include "../constants.h"


double fresnelReflectance(double nI, double nT, double cosThetaI, double cosThetaT) {
    double rParallel = (nT * cosThetaI - nI * cosThetaT) / (nT * cosThetaI + nI * cosThetaT);
    double rPerpendicular = (nT * cosThetaT - nI * cosThetaI) / (nT * cosThetaT + nI * cosThetaI);
    return (0.5) * (rParallel * rParallel + rPerpendicular * rPerpendicular);
}

void Fresnel::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    Vec3 outgoing = bsdfSampleInfo->outgoing;
    Vec3 oSpherical = toSpherical(outgoing);

    double thetaI = oSpherical[0];
    double phiI = oSpherical[1];

    //fresnel reflectance
    double nI = ior;
    double nT = 1;
    double sinThetaI = sin(thetaI);
    if (flipped_normal) {
        //entering material
        std::swap(nI, nT);
    }

    double sinThetaT = nI * sinThetaI / nT;

    double cosThetaI = cos(thetaI);
    double cosThetaT = 1.0 - sinThetaT * sinThetaT;

    //if total internal reflection, we reflect all light
    double F = (sinThetaT > 1.0) ? 1 : fresnelReflectance(nI, nT, cosThetaI, cosThetaT);

    if (rand_double() < F) {
        //reflect
        bsdfSampleInfo->incoming = toCartesian(Vec3(thetaI, phiI + PI, 1));
        bsdfSampleInfo->reflectivity = color;
        bsdfSampleInfo->density = F;
    } else {
        //transmit
        bsdfSampleInfo->incoming = Vec3(1,1,-1).cwiseProduct(toCartesian(Vec3(asin(sinThetaT), phiI + PI, 1)));
        bsdfSampleInfo->reflectivity = ((nT * nT) / (nI * nI)) * (1 - F) * color;
        bsdfSampleInfo->density = 1 - F;
    }
    bsdfSampleInfo->reflectivity /= cosThetaI;

}

void Fresnel::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    bsdfSampleInfo->density = 0;
    bsdfSampleInfo->reflectivity = Color(0, 0, 0);
}

Fresnel::Fresnel(double ior, const Color &color) : ior(ior), color(color) {}
