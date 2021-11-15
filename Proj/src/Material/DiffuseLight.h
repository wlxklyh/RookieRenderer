//
// Created by linyanhou on 2021/11/15.
//

#ifndef ROOKIERENDERER_DIFFUSELIGHT_H
#define ROOKIERENDERER_DIFFUSELIGHT_H

#include "MaterialBase.h"
#include "Texture.h"

class DiffuseLight :public MaterialBase {
public:
    DiffuseLight(Texture *t) : emit(t) {}
    virtual FVec3 Emitted(const Ray& r_in, const RPhysics::HitRecord& rec, float u, float v, const FVec3& p) const;
    Texture *emit;
};


#endif //ROOKIERENDERER_DIFFUSELIGHT_H
