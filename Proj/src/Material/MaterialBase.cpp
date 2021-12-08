//
// Created by wlxklyh on 2021/10/16.
//

#include "MaterialBase.h"

RMath::FVec3 Reflect(const RMath::FVec3 &v, const RMath::FVec3 &n) {
    return v - 2 * dot(v, n) * n;
}

double RandomDouble() {
    return rand() / (RAND_MAX + 1.0);
}

//看这个：https://blog.csdn.net/yinhun2012/article/details/79472364
bool Refract(const RMath::FVec3 &v, const RMath::FVec3 &n, float ni_over_nt, RMath::FVec3 &refracted) {
    RMath::FVec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    } else
        return false;
}

float Schlick(float cosine, float refIdx) {
    float r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

