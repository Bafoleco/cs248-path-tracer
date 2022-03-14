//
// Created by Bay Foley-Cox on 3/9/22.
//

#include "LightSource.h"

LightSourceType LightSource::getLightSourceType() const {
    return lightSourceType;
}

LightSource::LightSource(LightSourceType lightSourceType) : lightSourceType(lightSourceType) {}
