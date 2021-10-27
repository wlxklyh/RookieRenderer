//
// Created by wlxklyh on 2021/10/17.
//

#ifndef ROOKIERENDERER_METAL_H
#define ROOKIERENDERER_METAL_H

#include "RMath.h"
#include "MaterialBase.h"

class Metal : public MaterialBase {
public:
    RMath::FColorRGB Albedo;
    float Fuzz;

    Metal(const RMath::FColorRGB &a, float fuzz) : Albedo(a), Fuzz(fuzz) {};

    virtual bool Scatter(const RMath::Ray &rayIn, const RPhysics::HitRecord &rec,
                         RMath::FVec3 &attenuation, RMath::Ray &scattered) const override;

};

#endif //ROOKIERENDERER_METAL_H
