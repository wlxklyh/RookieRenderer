//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_MATERIAL_H
#define ROOKIERENDERER_MATERIAL_H

#include "Ray.h"
#include "Hitable.h"

class Material {
public:
    virtual bool Scatter(const RMath::Ray &rayIn, const RMath::HitRecord &rec,
                         RMath::FVec3 &attenuation, RMath::Ray &scattered) const = 0;
};


#endif //ROOKIERENDERER_MATERIAL_H
