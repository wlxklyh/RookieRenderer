//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_SPHERE_H
#define ROOKIERENDERER_SPHERE_H

#include "Hitable.h"
#include "Material.h"

namespace RPhysics {
    class Sphere : public Hitable {
    public:
        RMath::FPoint3D Center;
        float Radius;
        MaterialBase *MatPtr;

        Sphere() {};

        Sphere(RMath::FVec3 center, float radius, MaterialBase *matPtr) : Center(center), Radius(radius), MatPtr(matPtr) {};

        virtual bool Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const override;

        virtual bool BoundindBox(float t0, float t1, AABB& box) const override;
    };
}


#endif //ROOKIERENDERER_SPHERE_H
