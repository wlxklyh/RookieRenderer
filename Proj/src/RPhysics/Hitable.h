//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_HITABLE_H
#define ROOKIERENDERER_HITABLE_H

#include "RMath.h"
#include "AABB.h"

class MaterialBase;

namespace RPhysics {
    struct HitRecord {
        float t;
        RMath::FVec3 p;
        RMath::FVec3 normal;
        MaterialBase *mat;
    };

    class Hitable {
    public:
        virtual bool Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const = 0;

        virtual bool BoundindBox(float t0, float t1, AABB &box) const = 0;
    };
}


#endif //ROOKIERENDERER_HITABLE_H
