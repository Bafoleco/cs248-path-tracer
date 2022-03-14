//
// Created by Bay Foley-Cox on 3/5/22.
//

#include "Material.h"

#include <utility>

BSDF *Material::getBsdf() const {
    return bsdf;
}

Material::Material(BSDF *bsdf) : bsdf(bsdf) {
    emissionIntensity = 0;
    emissionColor = Color(0, 0, 0);
}

Material::Material(BSDF *bsdf, Color emissionColor, double emissionIntensity) : bsdf(bsdf),
                                                                                       emissionColor(std::move(emissionColor)),
                                                                                       emissionIntensity(
                                                                                               emissionIntensity) {}
Light Material::getEmittedLight() {
    return emissionColor * emissionIntensity;
}
