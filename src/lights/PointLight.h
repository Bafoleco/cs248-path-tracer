//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_POINTLIGHT_H
#define PATH_TRACER_POINTLIGHT_H


#include "../types.h"
#include "LightSource.h"

class PointLight : public LightSource {
public:
    PointLight(const Vec3 &pos, const Color &color, double intensity);

    bool isDeltaLight() override;

    void sampleLight(LightSampleInfo *lightSampleInfo, Vec3 pos) override;

    Vec3 pos;
    Color color;
    double intensity;
};


#endif //PATH_TRACER_POINTLIGHT_H
