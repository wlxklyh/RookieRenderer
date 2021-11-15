//
// Created by wlxklyh on 2021/10/26.
//

#ifndef ROOKIERENDERER_AABB_H
#define ROOKIERENDERER_AABB_H

#include "RMath.h"

namespace RPhysics {

    class AABB {
    public:
        RMath::FVec3 MinV;
        RMath::FVec3 MaxV;

        AABB() {};

        AABB(const RMath::FVec3 &min,const  RMath::FVec3 &max) {
            MaxV = max;
            MinV = min;
        }

        bool Hit(const RMath::Ray &ray, float tMin, float tMax) const;
    };

    AABB MergeTwoBox(AABB &box1, AABB &box2);
}

#endif //ROOKIERENDERER_AABB_H
