//
// Created by Bay Foley-Cox on 3/9/22.
//

#include "AreaLight.h"
#include "../material/Diffuse.h"

bool AreaLight::isDeltaLight() {
    return false;
}

void AreaLight::sampleLight(LightSampleInfo *lightSampleInfo, Vec3 pos) {

    //first lets sample random point in plane
    Vec3 randPoint = plane.getRandomPoint();

    Vec3 lightDir = (randPoint - pos).normalized();

    lightSampleInfo->color = color;
    lightSampleInfo->dir = lightDir;
    lightSampleInfo->sourcePos = randPoint;
    lightSampleInfo->density = 1.0 / area;
    lightSampleInfo->isDelta = false;
    lightSampleInfo->intensity = intensity / area;
}

AreaLight::AreaLight(const Color &color, double intensity, Plane plane) : LightSource(AREA_LIGHT), color(color), intensity(intensity),
                                                                          plane(plane) {
    area = plane.getArea();
    auto* diffuse = new Diffuse(Color(0, 0, 0));
    auto* emissive = new Material(diffuse, color, intensity / area);
    plane.setMaterial(*emissive);
}

Plane *AreaLight::getPlane() {
    return &plane;
}
