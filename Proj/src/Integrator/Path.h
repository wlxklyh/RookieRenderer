//
// Created by linyanhou on 2021/12/6.
//

#ifndef ROOKIERENDERER_PATH_H
#define ROOKIERENDERER_PATH_H

#include "Integrator.h"

class PathIntegrator : public SamplerIntegrator {
public:
    virtual FColorRGB Li(const Ray &ray, RPhysics::Hitable &world, int depth) const;
};


#endif //ROOKIERENDERER_PATH_H
