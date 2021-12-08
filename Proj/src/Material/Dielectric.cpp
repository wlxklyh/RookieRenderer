//
// Created by wlxklyh on 2021/10/17.
//

#include "Dielectric.h"
#include "RPhysics.h"

bool Dielectric::Scatter(const RMath::Ray &ray, const RPhysics::HitRecord &rec,
                         RPhysics::ScatterRecord &scatterRecord) const {
    RMath::FVec3 outwardNormal;
    RMath::FVec3 reflected = Reflect(ray.Direction(), rec.normal);
    float ni_over_nt;
    scatterRecord.f_r = RMath::FVec3(1.0, 1.0, 1.0);
    RMath::FVec3 refracted;
    float reflect_prob;
    float cosine;
    //如果大雨90入射
    if (dot(ray.Direction(), rec.normal) > 0) {
        outwardNormal = -rec.normal;
        ni_over_nt = RefIdx;
        // cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        cosine = dot(ray.Direction(), rec.normal) / ray.Direction().length();
        cosine = sqrt(1 - RefIdx * RefIdx * (1 - cosine * cosine));
    } else {
        outwardNormal = rec.normal;
        ni_over_nt = 1.0 / RefIdx;
        cosine = -dot(ray.Direction(), rec.normal) / ray.Direction().length();
    }

    if (Refract(ray.Direction(), outwardNormal, ni_over_nt, refracted))
        reflect_prob = Schlick(cosine, RefIdx);
    else
        reflect_prob = 1.0;
    if (RandomDouble() < reflect_prob)
        scatterRecord.scatterRay = RMath::Ray(rec.p, reflected);
    else
        scatterRecord.scatterRay = RMath::Ray(rec.p, refracted);
    return true;
}
