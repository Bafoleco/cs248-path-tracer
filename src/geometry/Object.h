//
// Created by Bay Foley-Cox on 3/4/22.
//

#ifndef PATH_TRACER_OBJECT_H
#define PATH_TRACER_OBJECT_H

#include <Eigen/Dense>
#include "Ray.h"
#include "../material/Material.h"

class Object {
public:
    Object(Vec3 pos, Material &material, std::string name);

    const std::string &getName() const;

    Vec3 getPos() const;
    void setPos(const Vec3 &pos);
    Material getMaterial(Vec3 pos);

    void sampleReflection(BSDFSampleInfo* bsdfSampleInfo, Vec3 &hitPos);
    void getReflectionInfo(BSDFSampleInfo* bsdfSampleInfo, Vec3 &hitPos);

    virtual Vec3 getMinCords() const = 0;
    virtual Vec3 getMaxCords() const = 0;
    virtual double intersect(Ray* ray) const = 0;
    virtual Vec3 getNormal(Vec3 pos) const = 0;
    virtual ~Object() {}
private:
    Material& material;

protected:
    std::string name;
    Vec3 pos;
};


#endif //PATH_TRACER_OBJECT_H
