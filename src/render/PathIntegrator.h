//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_PATHINTEGRATOR_H
#define PATH_TRACER_PATHINTEGRATOR_H

#include "../types.h"
#include "../scene/Bvh.h"
#include "../scene/Scene.h"

class PathIntegrator {

public:
    static Color sample(Scene *scene, const Ray ray) ;
};


#endif //PATH_TRACER_PATHINTEGRATOR_H
