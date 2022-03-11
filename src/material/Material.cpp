//
// Created by Bay Foley-Cox on 3/5/22.
//

#include "Material.h"

const Color &Material::getEmittance() const {
    return emittance;
}

BSDF *Material::getBsdf() const {
    return bsdf;
}

Material::Material(const Color &emittance, BSDF *bsdf) : emittance(emittance), bsdf(bsdf) {}
