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
    Vec3 getPos() const;
    void setPos(const Vec3 &pos);
    Material getMaterial(Vec3 pos);

    virtual Vec3 getMinCords() const = 0;
    virtual Vec3 getMaxCords() const = 0;
    virtual double intersect(Ray* ray) const = 0;
    virtual Vec3 getNormal(Vec3 pos) const = 0;
    virtual ~Object() {}
private:
    Material& material;

protected:
    Vec3 pos;
    Object(Vec3 pos, Material &material);
};


#endif //PATH_TRACER_OBJECT_H
