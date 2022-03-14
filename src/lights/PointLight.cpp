//
// Created by Bay Foley-Cox on 3/6/22.
//

#include "PointLight.h"

PointLight::PointLight(const Vec3 &pos, const Color &color, double intensity) : LightSource(POINT_LIGHT), pos(pos), color(color),
                                                                                intensity(intensity) {}

void PointLight::sampleLight(LightSampleInfo *lightSampleInfo, Vec3 samplePos) {
    lightSampleInfo->color = color;
    lightSampleInfo->dir = (samplePos - pos).normalized();
    lightSampleInfo->sourcePos = pos;
    lightSampleInfo->density = 1.0;
    lightSampleInfo->intensity = intensity;
    lightSampleInfo->isDelta = true;
}

bool PointLight::isDeltaLight() {
    return true;
}
