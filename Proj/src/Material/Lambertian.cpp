//
// Created by wlxklyh on 2021/10/17.
//

#include "Lambertian.h"
#include "RPhysics.h"

bool Lambertian::Scatter(const RMath::Ray &rayIn, const RPhysics::HitRecord &rec,
                         RPhysics::ScatterRecord &scatterRecord) const {
    RMath::FPoint3D target = rec.p + rec.normal + RandomInUnitSphere();
    scatterRecord.scatterRay = RMath::Ray(rec.p, target - rec.p);
    scatterRecord.f_r = Albedo->Value(rec.u,rec.v,rec.p);
    return true;
}