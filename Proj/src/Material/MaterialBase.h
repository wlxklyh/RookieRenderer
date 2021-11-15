//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_MATERIALBASE_H
#define ROOKIERENDERER_MATERIALBASE_H

#include "RMath.h"
#include "RPhysicsFwd.h"


RMath::FVec3 Reflect(const RMath::FVec3 &v, const RMath::FVec3 &n);

double RandomDouble();

//看这个：https://blog.csdn.net/yinhun2012/article/details/79472364
bool Refract(const RMath::FVec3 &v, const RMath::FVec3 &n, float ni_over_nt, RMath::FVec3 &refracted);

float Schlick(float cosine, float refIdx);

RMath::FVec3 RandomInUnitSphere();


class MaterialBase {
public:
    virtual bool Scatter(const RMath::Ray &rayIn, const RPhysics::HitRecord &rec,
                         RMath::FVec3 &attenuation, RMath::Ray &scattered) const {
        return false;
    };


    virtual FVec3 Emitted(const Ray& r_in, const RPhysics::HitRecord& rec, float u, float v, const FVec3& p) const { return FVec3(0,0,0); }
};


#endif //ROOKIERENDERER_MATERIALBASE_H
