//
// Created by wlxklyh on 2021/10/17.
//

#ifndef ROOKIERENDERER_DIELECTRIC_H
#define ROOKIERENDERER_DIELECTRIC_H

#include "RMath.h"
#include "MaterialBase.h"

class Dielectric : public MaterialBase {
public:
    float RefIdx;

    Dielectric(float ri) : RefIdx(ri) {}

    virtual bool Scatter(const RMath::Ray &ray, const RPhysics::HitRecord &rec,
                         RPhysics::ScatterRecord &scatterRecord) const;

};


#endif //ROOKIERENDERER_DIELECTRIC_H
