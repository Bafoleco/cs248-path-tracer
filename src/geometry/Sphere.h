//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_SPHERE_H
#define PATH_TRACER_SPHERE_H


#include "Object.h"

class Sphere : public Object {
public:
    Vec3 getMinCords() const override;
    Vec3 getMaxCords() const override;
    double intersect(Ray *ray) const override;
    Vec3 getNormal(Vec3 pos) const override;

    Sphere(const Vec3 &pos, double radius, Material &material);

private:
    double radius;

};


#endif //PATH_TRACER_SPHERE_H
