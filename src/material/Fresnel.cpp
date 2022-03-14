//
// Created by Bay Foley-Cox on 3/10/22.
//

#include "Fresnel.h"

#include <utility>
#include "../util.h"
#include "../constants.h"


double fresnelReflectance(double nI, double nT, double cosThetaI, double cosThetaT) {
    double rParallel = (nT * cosThetaI - nI * cosThetaT) / (nT * cosThetaI + nI * cosThetaT);
    double rPerpendicular = (nT * cosThetaT - nI * cosThetaI) / (nI * cosThetaI + nT * cosThetaT);
    return (0.5) * (rParallel * rParallel + rPerpendicular * rPerpendicular);
}


/*
 *
 */
Vec3 refract(Vec3 incoming, double iorCurrent, double iorNext, double *F) {
    Vec3 incomingSpherical = toSpherical(std::move(incoming));

    double sinThetaIncoming = sin(incomingSpherical[0]);
    assert(sinThetaIncoming > 0);

    double sinThetaOutgoing = (iorCurrent / iorNext) * sinThetaIncoming;
//    printf("ration %f, %f \n", iorCurrent / iorNext, sinThetaIncoming);
    if (sinThetaOutgoing > 1) {
        //total internal reflection
//        printf("tir \n");

        *F = 1;
        return Vec3(0, 0, 0);
    }
    double thetaOutgoing = asin(sinThetaOutgoing);
    assert(thetaOutgoing >= 0);

    //otherwise, compute fresnelReflectance
    double cosThetaIncoming = std::sqrt(1 - sinThetaIncoming * sinThetaIncoming);
    double cosThetaOutgoing = std::sqrt(1 - sinThetaOutgoing * sinThetaOutgoing);
    assert(cosThetaIncoming >= 0);
    assert(cosThetaOutgoing >= 0);
    *F = fresnelReflectance(iorCurrent, iorNext, cosThetaIncoming, cosThetaOutgoing);
//    *F = 0;

    Vec3 outgoing = toCartesian(Vec3(PI - thetaOutgoing, incomingSpherical[1] + PI, 1));

    //verify outgoing

    Vec3 incomingS = toSpherical(incoming);
    Vec3 outgoingS = toSpherical(outgoing);

    assert(std::abs(iorCurrent * sin(incomingS[0]) - iorNext * sin(outgoingS[0])) < 0.001);

    return outgoing;
}

void Fresnel::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    Vec3 outgoing = bsdfSampleInfo->outgoing;
    Vec3 outgoingSpherical = toSpherical(bsdfSampleInfo->outgoing);

    //fresnel reflectance
    double nI = 1;
    double nT = ior;
    if (flipped_normal) {
        //entering material, so outgoing ray
        std::swap(nI, nT);
        outgoing = outgoing.cwiseProduct(Vec3(1,1,-1));
    }

    //compute incoming direction assuming transmission
    double F;
    Vec3 incoming = refract(outgoing, nI, nT, &F);

    //translate back
    if (flipped_normal) {
        outgoing.cwiseProduct(Vec3(1,1,-1));
        incoming.cwiseProduct(Vec3(1,1,-1));
    }

    if (rand_double() < F) {
        //reflect
        bsdfSampleInfo->incoming = toCartesian(Vec3(outgoingSpherical[0], outgoingSpherical[1] + PI, 1));
        bsdfSampleInfo->reflectivity = reflectionColor;
        bsdfSampleInfo->reflectivity /= std::abs(cos(outgoingSpherical[0]));
        bsdfSampleInfo->density = F;
    } else {
        //transmit
        Vec3 incomingSpherical = toSpherical(incoming);
        bsdfSampleInfo->incoming = incoming;
//        bsdfSampleInfo->reflectivity = ((nT * nT) / (nI * nI)) * (1 - F) * color;
        bsdfSampleInfo->reflectivity = (1 - F) * transmissionColor;

        bsdfSampleInfo->reflectivity /= std::abs(cos(incomingSpherical[0]));
        bsdfSampleInfo->density = 1 - F;
    }
}

void Fresnel::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    bsdfSampleInfo->density = 0;
    bsdfSampleInfo->reflectivity = Color(0, 0, 0);
}

Fresnel::Fresnel(double ior, const Color &reflectionColor, const Color &transmissionColor) : ior(ior), reflectionColor(
        reflectionColor), transmissionColor(transmissionColor) {}
