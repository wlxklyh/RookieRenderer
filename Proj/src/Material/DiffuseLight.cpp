//
// Created by linyanhou on 2021/11/15.
//

#include "DiffuseLight.h"
#include "Hitable.h"

FVec3 DiffuseLight::Emitted(const Ray& r_in, const RPhysics::HitRecord& rec, float u, float v, const FVec3& p) const {
    if (dot(rec.normal, r_in.Direction()) < 0.0)
        return emit->Value(u, v, p);
    else
        return FVec3(0,0,0);
}