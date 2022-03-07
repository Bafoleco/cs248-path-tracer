//
// Created by Bay Foley-Cox on 3/5/22.
//

#include "Material.h"

Vec3 Material::sampleIncomingDir(Vec3 outgoingDir, Vec3 normal) {
    return Vec3();
}

Material::Material(const Color &emittance) : emittance(emittance) {}

const Color &Material::getEmittance() const {
    return emittance;
}
