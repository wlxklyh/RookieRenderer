//
// Created by wlxklyh on 2021/10/17.
//

#include "Lambertian.h"
#include "RPhysics.h"

bool Lambertian::Scatter(const RMath::Ray &rayIn, const RPhysics::HitRecord &rec, RMath::FVec3 &attenuation,
                         RMath::Ray &scattered) const {
    RMath::FPoint3D target = rec.p + rec.normal + RandomInUnitSphere();
    scattered = RMath::Ray(rec.p, target - rec.p);
    attenuation = Albedo;
    return true;
}