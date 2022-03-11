//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_PLANE_H
#define PATH_TRACER_PLANE_H

#include "Object.h"
#include "Triangle.h"

class Plane : public Object {
public:
    Plane(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, Material &material, std::string name);

    Vec3 getMinCords() const override;
    Vec3 getMaxCords() const override;
    double intersect(Ray *ray) const override;
    Vec3 getNormal(Vec3 pos) const override;
    Vec3 getRandomPoint();
    double getArea() const;

private:
    Vec3 p0;
    Vec3 p1;
    Vec3 p2;
    Vec3 p3;

    Vec3 normal;
    double c;
    Triangle t1;
    Triangle t2;
    std::pair<Vec3, Vec3> bbox;
};


#endif //PATH_TRACER_PLANE_H
