//
// Created by wlxklyh on 2021/10/17.
//

#ifndef ROOKIERENDERER_LAMBERTIAN_H
#define ROOKIERENDERER_LAMBERTIAN_H

#include "RMath.h"
#include "MaterialBase.h"

#include "ConstantTex.h"
#include "Texture.h"
class Lambertian : public MaterialBase {
public:
    Texture* Albedo;

    Lambertian(Texture *texture) : Albedo(texture) {};

    bool Scatter(const RMath::Ray &rayIn, const RPhysics::HitRecord &rec, RMath::FVec3 &attenuation,
                 RMath::Ray &scattered) const override;
};


#endif //ROOKIERENDERER_LAMBERTIAN_H
