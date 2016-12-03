//
// Created by manatee on 24.04.16.
//

#ifndef GRAPHIC3D_BEAMTRACER_H
#define GRAPHIC3D_BEAMTRACER_H

#include "utils/numeric.h"
#include "scene.h"

class BeamTracer {
public:
    BeamTracer();
    Light operator () (const Beam& beam, const Scene& scene) const;
private:
    Light trace(const Beam& beam, const Scene& scene, signed_small depth) const;
};

extern BeamTracer defaultTracer;


#endif //GRAPHIC3D_BEAMTRACER_H
