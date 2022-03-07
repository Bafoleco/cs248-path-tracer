//
// Created by Bay Foley-Cox on 3/6/22.
//

#ifndef PATH_TRACER_DIFFUSE_H
#define PATH_TRACER_DIFFUSE_H


#include "BSDF.h"
#include "Eigen/Core"
#include "Eigen/Geometry"

class Diffuse : public BSDF {
public:
    Vec3 sampleOutgoingGivenIncoming(Vec3 incoming) const override;
    Vec3 sampleIncomingGivenOutgoing(Vec3 outgoing) const override;
};


#endif //PATH_TRACER_DIFFUSE_H
