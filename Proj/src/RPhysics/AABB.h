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

        AABB(RMath::FVec3 &min, RMath::FVec3 &max) {
            MaxV = max;
            MinV = min;
        }


        bool Hit(const RMath::Ray &ray, float &tMin, float &tMax) {
            for (int i = 0; i < 3; i++) {
                //避免除以0
                if (abs(ray.B[i]) < FLOAT_SMALL) {
                    if (ray.A[i] < MinV[i] || ray.A[i] > MaxV[i]) {
                        return false;
                    } else {
                        continue;
                    }
                }
                float t0 = RMath::Min((MinV[i] - ray.A[i]) / ray.B[i],
                                      (MaxV[i] - ray.A[i] / ray.B[i]));
                float t1 = RMath::Max((MinV[i] - ray.A[i]) / ray.B[i],
                                      (MaxV[i] - ray.A[i] / ray.B[i]));

                tMin = RMath::Min(tMin, t0);
                tMax = RMath::Max(tMax, t1);
                if (tMax <= tMin) {
                    return false;
                }
            }
            return true;
        }
    };

    static AABB MergeTwoBox(AABB &box1, AABB &box2);
}

#endif //ROOKIERENDERER_AABB_H
