//
// Created by Bay Foley-Cox on 3/9/22.
//

#ifndef PATH_TRACER_AREALIGHT_H
#define PATH_TRACER_AREALIGHT_H

#include "../geometry/Plane.h"
#include "LightSource.h"

class AreaLight : public LightSource {

public:
    bool isDeltaLight() override;
    void sampleLight(LightSampleInfo *lightSampleInfo, Vec3 pos) override;
    AreaLight(const Color &color, double intensity, Plane plane);

    Plane* getPlane();

private:
    Color color;
    double intensity;
    Plane plane;
    double area;
};


#endif //PATH_TRACER_AREALIGHT_H
