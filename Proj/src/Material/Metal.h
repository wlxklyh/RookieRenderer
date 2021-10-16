//
// Created by wlxklyh on 2021/10/17.
//

#ifndef ROOKIERENDERER_METAL_H
#define ROOKIERENDERER_METAL_H

#include "Vec3.h"
#include "Material.h"

class Metal : public Material {
public:
    RMath::FColorRGB Albedo;

    Metal(const RMath::FColorRGB &a) : Albedo(a) {};

    virtual bool Scatter(const RMath::Ray &rayIn, const RMath::HitRecord &rec,
                         RMath::FVec3 &attenuation, RMath::Ray &scattered) const override{
        RMath::FVec3 reflected = Reflect(RMath::unit_vector(rayIn.Direction()), rec.normal);
        scattered = RMath::Ray(rec.p, reflected);
        attenuation = Albedo;
        return dot(scattered.Direction(), rec.normal) > 0;
    }

    RMath::FVec3 Reflect(const RMath::FVec3 &v, const RMath::FVec3 &n)const {
        return v - 2 * dot(v, n) * n;
    }
};

#endif //ROOKIERENDERER_METAL_H
