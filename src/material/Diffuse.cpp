//
// Created by Bay Foley-Cox on 3/6/22.
//

#include "Diffuse.h"

Vec3 Diffuse::sampleOutgoingGivenIncoming(Vec3 incoming) const {
//    return BSDF::sampleOutgoingGivenIncoming(incoming);
    return Vec3(0, 0, 0);
}

Vec3 Diffuse::sampleIncomingGivenOutgoing(Vec3 outgoing) const {
//    return BSDF::sampleIncomingGivenOutgoing(outgoing);

    return Vec3(0, 0, 0);
}
