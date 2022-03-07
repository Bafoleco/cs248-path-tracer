//
// Created by Bay Foley-Cox on 3/4/22.
//

#ifndef PATH_TRACER_BVH_H
#define PATH_TRACER_BVH_H


#include <vector>
#include "../geometry/Object.h"
#include "../geometry/Ray.h"

struct object_loc {
    object_loc(Object *pObject, double pos) : object(pObject), pos(pos){}
    Object* object;
    double pos;
};

struct hit_info {
    hit_info();

    Object* object{};
    double t{};
};

struct bbox_isect_info {

    bbox_isect_info(bool hit, double t);

    bool hit;
    double t;
};

class Bvh {
public:
    explicit Bvh(std::vector<Object*> objects);
    bbox_isect_info intersect(Ray* ray);

    std::vector<Object *> & getObjects();

    void printBVH();
    unsigned long numObjects();

    bool isLeaf() const;
    Bvh *getA() const;
    Bvh *getB() const;

private:
    Bvh* a;
    Bvh* b;
    std::vector<Object*> objects;
    bool is_leaf;

    static std::pair<Vec3, Vec3> getBoundingBox(std::vector<object_loc>::iterator start, std::vector<object_loc>::iterator end);
    static double getSurfaceArea(const std::pair<Vec3, Vec3>& prism);
    std::pair<Vec3, Vec3> bbox;
    std::pair<Vec3, Vec3> getBoundingBox(const std::vector<Object*>&);
};


#endif //PATH_TRACER_BVH_H
