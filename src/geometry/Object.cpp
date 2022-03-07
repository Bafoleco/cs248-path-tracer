//
// Created by Bay Foley-Cox on 3/4/22.
//

#include "Object.h"

#include <utility>

void Object::setPos(const Vec3 &pos) {
    Object::pos = pos;
}

Vec3 Object::getPos() const {
    return pos;
}

Object::Object(Vec3 pos, Material &material)
        : pos(std::move(pos)), material(material) {}


Material Object::getMaterial(Vec3 pos) {
    return material;
}

double Object::intersect(Ray *ray) const{
    return 0;
}

Vec3 Object::getMaxCords() const {
    return Vec3();
}

