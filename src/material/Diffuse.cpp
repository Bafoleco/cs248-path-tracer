//
// Created by Bay Foley-Cox on 3/6/22.
//

#include "Diffuse.h"
#include "../util.h"
#include "../constants.h"

void Diffuse::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    //randomly sampleReflection direction in hemisphere
    double phi = rand_double() * 2 * PI;
    double theta = acos(rand_double());
//    Vec3 rand_dir = Vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
    Vec3 rand_dir = toCartesian(Vec3(theta, phi, 1));

    bsdfSampleInfo->incoming = rand_dir;
    //set probability density
    bsdfSampleInfo->density = 1.0 / (2 * PI);
    //set reflectivity
    bsdfSampleInfo->reflectivity = color;

    bsdfSampleInfo->delta = false;
}

Diffuse::Diffuse(const Color &color) : color(color) {}

void Diffuse::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, bool flipped_normal) const {
    bsdfSampleInfo->density = 1.0 / (2 * PI);
    bsdfSampleInfo->reflectivity = color;
    bsdfSampleInfo->delta = false;
}
