//
// Created by linyanhou on 2021/12/6.
//

#ifndef ROOKIERENDERER_INTEGRATOR_H
#define ROOKIERENDERER_INTEGRATOR_H
#include "RMath.h"

namespace RPhysics {
    class Hitable;
}

class Integrator {
public:
//    virtual ~Integrator();
};

class SamplerIntegrator : public Integrator {
public:
    SamplerIntegrator(){}
    virtual FColorRGB Li(const Ray &ray, RPhysics::Hitable &world, int depth) const = 0;
};

#endif //ROOKIERENDERER_INTEGRATOR_H
