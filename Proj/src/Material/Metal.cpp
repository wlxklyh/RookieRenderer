//
// Created by wlxklyh on 2021/10/17.
//

#include "Metal.h"
#include "RPhysics.h"

bool Metal::Scatter(const RMath::Ray &rayIn, const RPhysics::HitRecord &rec, RMath::FVec3 &attenuation,
                    RPhysics::ScatterRecord &scatterRecord) const {
    RMath::FVec3 reflected = Reflect(RMath::unit_vector(rayIn.Direction()), rec.normal);
    scatterRecord.scattered = RMath::Ray(rec.p, reflected + Fuzz * RandomInUnitSphere());
    attenuation = Albedo;
    return dot(scatterRecord.scattered.Direction(), rec.normal) > 0;
}