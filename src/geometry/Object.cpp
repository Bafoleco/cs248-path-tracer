//
// Created by Bay Foley-Cox on 3/4/22.
//

#include "Object.h"
#include "../util.h"
#include <utility>

void Object::setPos(const Vec3 &pos) {
    Object::pos = pos;
}

Vec3 Object::getPos() const {
    return pos;
}

Object::Object(Vec3 pos, Material &material, std::string name) : material(material), name(name),
                                                                               pos(pos) {}

Material Object::getMaterial(Vec3 pos) {
    return material;
}

Eigen::Matrix3d constructNormal2World(const Vec3& normal) {
    Vec3 random(rand_double(), rand_double(), rand_double());
    Vec3 tangent1 = (random - random.dot(normal) * normal).normalized();
    Vec3 tangent2 = normal.cross(tangent1);

    Eigen::Matrix3d normal2World;
    normal2World.col(0) = tangent1;
    normal2World.col(1) = tangent2;
    normal2World.col(2) = normal;

    return normal2World;
}

void Object::sampleReflection(BSDFSampleInfo *bsdfSampleInfo, Vec3 &hitPos) {
    //first we compute transform into normal space
    Vec3 normal = getNormal(hitPos);
    bool flipped_normal = normal.dot(bsdfSampleInfo->outgoing) < 0;
    Vec3 samesideNormal = (flipped_normal) ? -1 * normal : normal;
    Eigen::Matrix3d normal2World = constructNormal2World(samesideNormal);
    Eigen::Matrix3d world2Normal = normal2World.inverse();

    //transform outgoing
    bsdfSampleInfo->outgoing = world2Normal * bsdfSampleInfo->outgoing;

    //invoke BSDF sample
    getMaterial(hitPos).getBsdf()->sampleReflection(bsdfSampleInfo, flipped_normal);

    //translate back to world coordinates
    bsdfSampleInfo->incoming = normal2World * bsdfSampleInfo->incoming;
    bsdfSampleInfo->outgoing = normal2World * bsdfSampleInfo->outgoing;

//    assert(bsdfSampleInfo->incoming.dot(samesideNormal) > 0);

//    printf("comp in n: %f, %f\n", bsdfSampleInfo->incoming.dot(normal), bsdfSampleInfo->outgoing.dot(normal));


}

void Object::getReflectionInfo(BSDFSampleInfo *bsdfSampleInfo, Vec3 &hitPos) {
    //first we compute transform into normal space
    Vec3 normal = getNormal(hitPos);
    bool flipped_normal = normal.dot(bsdfSampleInfo->outgoing) < 0;
    Vec3 samesideNormal = (flipped_normal) ? -1 * normal : normal;
    Eigen::Matrix3d normal2World = constructNormal2World(samesideNormal);
    Eigen::Matrix3d world2Normal = normal2World.inverse();


    assert(normal2World.determinant() < 1.01 || normal2World.determinant() > 0.999);

    //transform outgoing and incoming
    bsdfSampleInfo->outgoing = world2Normal * bsdfSampleInfo->outgoing;
    bsdfSampleInfo->incoming = world2Normal * bsdfSampleInfo->incoming;

    //invoke BSDF sample
    getMaterial(hitPos).getBsdf()->getReflectionInfo(bsdfSampleInfo, flipped_normal);

    //translate back to world coordinates
    bsdfSampleInfo->outgoing = normal2World * bsdfSampleInfo->outgoing;
    bsdfSampleInfo->incoming = normal2World * bsdfSampleInfo->incoming;
}

const std::string &Object::getName() const {
    return name;
}

