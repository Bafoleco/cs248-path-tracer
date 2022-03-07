//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_TRIANGLE_H
#define PATH_TRACER_TRIANGLE_H


#include "../types.h"
#include "Object.h"

class Triangle : public Object {

public:
    Triangle(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, Material &material);

    Vec3 getMinCords() const override;
    Vec3 getMaxCords() const override;
    double intersect(Ray *ray) const override;
    Vec3 getNormal(Vec3 pos) const override;

private:
    Vec3 normal;
    double c;
    Vec3 p0;
    Vec3 p1;
    Vec3 p2;
    Vec3 basis1;
    Vec3 basis2;
    std::pair<Vec3, Vec3> bbox;
};


#endif //PATH_TRACER_TRIANGLE_H
