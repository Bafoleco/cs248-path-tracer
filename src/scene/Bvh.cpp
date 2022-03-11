//
// Created by Bay Foley-Cox on 3/4/22.
//

#include "Bvh.h"
#include "../constants.h"

#define C_TRAV 120
#define C_ISECT 50

Bvh::Bvh(std::vector<Object*> objects) : objects(objects) {

    printf("constructing Bvh from %lu objects\n", objects.size());

    bbox = getBoundingBox(objects);
    if (objects.size() < 2) {
        is_leaf = true;
        return;
    }

    double min_cost = objects.size() * C_ISECT;
    int min_axis;
    int min_index;

    double surfaceArea = getSurfaceArea(bbox);

    std::vector<object_loc> ordered_objects_x;
    std::vector<object_loc> ordered_objects_y;
    std::vector<object_loc> ordered_objects_z;
    for (auto& o : objects) {
        ordered_objects_x.emplace_back(o, o->getPos()[0]);
        ordered_objects_y.emplace_back(o, o->getPos()[1]);
        ordered_objects_z.emplace_back(o, o->getPos()[2]);
    }

    for (int axis = 0; axis < 3; axis++) {
        std::vector<object_loc>* ordered_objects;
        if (axis == 0) {
            ordered_objects = &ordered_objects_x;
        } else if (axis == 1) {
            ordered_objects = &ordered_objects_y;
        } else {
            ordered_objects = &ordered_objects_z;
        }

        std::sort(ordered_objects->begin(), ordered_objects->end(),
                  [](const object_loc& a, const object_loc& b) -> bool
                        {
                            return a.pos > b.pos;
                        }
        );

        auto end = ordered_objects->end();
        auto start = ordered_objects->begin();
        int numLeft = 0;
        for(auto it = start; it != end; it++) {
            unsigned long numRight = objects.size() - numLeft;

            if (numLeft > 0 && numRight > 0) {
                auto a = getBoundingBox(start, it);
                auto b = getBoundingBox(it, end);

                double surfaceAreaA = getSurfaceArea(a);
                double surfaceAreaB = getSurfaceArea(b);

                double cost = C_TRAV + (surfaceAreaA / surfaceArea) * numLeft * C_ISECT +
                              (surfaceAreaB / surfaceArea) * numRight * C_ISECT;

                if (cost < min_cost) {
                    min_axis = axis;
                    min_cost = cost;
                    min_index = numLeft;
                }
            }

            numLeft++;
        }
    }

    if (min_cost < objects.size() * C_ISECT) {
        printf("split at %d of %lu\n", min_index, objects.size());
        std::vector<object_loc>* ordered_objects;
        if (min_axis == 0) {
            ordered_objects = &ordered_objects_x;
        } else if (min_axis == 1) {
            ordered_objects = &ordered_objects_y;
        } else {
            ordered_objects = &ordered_objects_z;
        }

        std::vector<Object*> objectListA;
        std::vector<Object*> objectListB;
        for (int i = 0; i < ordered_objects->size(); i++) {
            if (i < min_index) {
                objectListA.emplace_back(ordered_objects->at(i).object);
            } else {
                objectListB.emplace_back(ordered_objects->at(i).object);
            }
        }

        a = new Bvh(objectListA);
        b = new Bvh(objectListB);
        is_leaf = false;
    } else {
        is_leaf = true;
    }
}

std::pair<Vec3, Vec3> Bvh::getBoundingBox(std::vector<object_loc>::iterator start,
                                                                std::vector<object_loc>::iterator end) {

    Vec3 min(INT_MAX, INT_MAX, INT_MAX);
    Vec3 max(INT_MIN, INT_MIN, INT_MIN);

    for (auto it = start; it != end; it++) {
        Object* o = it->object;
        Vec3 objectMin = o->getMinCords();
        Vec3 objectMax = o->getMaxCords();

        max[0] = std::max(objectMax[0], max[0]);
        max[1] = std::max(objectMax[1], max[1]);
        max[2] = std::max(objectMax[2], max[2]);
        min[0] = std::min(objectMin[0], min[0]);
        min[1] = std::min(objectMin[1], min[1]);
        min[2] = std::min(objectMin[2], min[2]);
    }

    return {min, max};
}

std::pair<Vec3, Vec3> Bvh::getBoundingBox(const std::vector<Object*>&) {

    Vec3 min(INT_MAX, INT_MAX, INT_MAX);
    Vec3 max(INT_MIN, INT_MIN, INT_MIN);

    for (auto const &o : objects) {
        Vec3 objectMin = o->getMinCords();
        Vec3 objectMax = o->getMaxCords();

        max[0] = std::max(objectMax[0], max[0]);
        max[1] = std::max(objectMax[1], max[1]);
        max[2] = std::max(objectMax[2], max[2]);
        min[0] = std::min(objectMin[0], min[0]);
        min[1] = std::min(objectMin[1], min[1]);
        min[2] = std::min(objectMin[2], min[2]);
    }

    return {min, max};
}


double Bvh::getSurfaceArea(const std::pair<Vec3, Vec3>& prism) {
    auto min = prism.first;
    auto max = prism.second;

    double xDiff = max[0] - min[0];
    double yDiff = max[1] - min[1];
    double zDiff = max[2] - min[2];

    return 2 * (xDiff * zDiff + yDiff * xDiff + zDiff * yDiff);
}

bool Bvh::isLeaf() const {
    return is_leaf;
}

void printBVHLevel(Bvh* bvh, int level) {

    for(int i = 0; i < level * 2; i++) {
        printf(" ");
    }
    if (bvh->isLeaf()) {
        printf("Leaf: %lu \n", bvh->numObjects());
    } else {
        printf("contains: \n");
        printBVHLevel(bvh->getA(), level + 1);
        printBVHLevel(bvh->getB(), level + 1);
    }
}

Bvh *Bvh::getA() const {
    return a;
}

Bvh *Bvh::getB() const {
    return b;
}

void Bvh::printBVH() {
    printBVHLevel(this, 0);
}

unsigned long Bvh::numObjects() {
    return objects.size();
}

int getConstAxis(int axis1, int axis2) {
    if (axis1 != X && axis2 != X) {
        return X;
    }
    if (axis1 != Y && axis2 != Y) {
        return Y;
    }
    return Z;
}


struct rectangle_hit {
    rectangle_hit(bool hitRect, double t) : hit_rect(hitRect), t(t) {}

    bool hit_rect;
    double t;
};

rectangle_hit get_plane_intersect(Ray* ray, int axis1, int axis2, bool is_low, Vec3 minCoords,
                                  Vec3 maxCoords) {
    assert(axis1 != axis2);

    //constant axis
    int constAxis = getConstAxis(axis1, axis2);
    double constCoord = (is_low) ? minCoords[constAxis] : maxCoords[constAxis];

    double t = (constCoord - ray->pos[constAxis]) / (ray->dir[constAxis]);
    if (!std::isfinite(t)) {
        return {false, 0};
    }
    Vec3 intersectPoint = ray->posAt(t);

    //verify in rectangle
    bool inRectangle = true;
    if (intersectPoint[axis1] < minCoords[axis1] && intersectPoint[axis1] > maxCoords[axis1]) {
        if (intersectPoint[axis2] < minCoords[axis2] && intersectPoint[axis2] > maxCoords[axis2]) {
            inRectangle = false;
        }
    }

    return {inRectangle, t};
}

bbox_isect_info Bvh::intersect(Ray *ray) {
    Vec3 pos = ray->pos;
    Vec3 dir = ray->dir;

    bool found_hit = false;
    //TODO fix
    double min_t = 100000;

    //find closet Ray plane intersection
    for (int i = X; i <= Z; i++) {
        for (int j = X; j <= Z; j++) {
            if (i != j) {
                bool is_low = (i < j);
                rectangle_hit rh = get_plane_intersect(ray, i, j, is_low, bbox.first, bbox.second);
                if (rh.hit_rect && rh.t >= 0 && rh.t < min_t) {
                    found_hit = true;
                    min_t = rh.t;
                }
            }
        }
    }

    return {found_hit, min_t};
}

std::vector<Object*> &Bvh::getObjects() {
    return objects;
};

bbox_isect_info::bbox_isect_info(bool hit, double t) : hit(hit), t(t) {}

//TODO constant
hit_info::hit_info() : object(nullptr), t(10000) {}
