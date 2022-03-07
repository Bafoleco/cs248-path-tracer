//
// Created by Bay Foley-Cox on 3/5/22.
//

#ifndef PATH_TRACER_BSDF_H
#define PATH_TRACER_BSDF_H

#include "../types.h"

class BSDF {

public:
    /*
     * We will operate in the frame of reference of the surface, where z is the surface normal
     *
     */
    virtual Vec3 sampleOutgoingGivenIncoming(Vec3 incoming) const = 0;
    virtual Vec3 sampleIncomingGivenOutgoing(Vec3 outgoing) const = 0;
    virtual ~BSDF();

private:


};


#endif //PATH_TRACER_BSDF_H
