//
// Created by wlxklyh on 2021/10/17.
//

#include "Metal.h"
#include "RPhysics.h"

bool Metal::Scatter(const RMath::Ray &rayIn, const RPhysics::HitRecord &rec,
                    RPhysics::ScatterRecord &scatterRecord) const {
    RMath::FVec3 reflected = Reflect(RMath::unit_vector(rayIn.Direction()), rec.normal);
    scatterRecord.scatterRay = RMath::Ray(rec.p, reflected + Fuzz * RandomInUnitSphere());
    scatterRecord.f_r = Albedo;
    return dot(scatterRecord.scatterRay.Direction(), rec.normal) > 0;
}