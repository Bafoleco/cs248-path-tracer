//
// Created by Bay Foley-Cox on 3/9/22.
//

#ifndef PATH_TRACER_LIGHTSOURCE_H
#define PATH_TRACER_LIGHTSOURCE_H


#include "../types.h"

struct LightSampleInfo {
    Vec3 dir;
    Vec3 sourcePos;
    Color color;
    double intensity;
    double density;
    bool isDelta;
};

class LightSource {

public:
    virtual bool isDeltaLight() = 0;
    virtual void sampleLight(LightSampleInfo *lightSampleInfo, Vec3 pos) = 0;
};


#endif //PATH_TRACER_LIGHTSOURCE_H
