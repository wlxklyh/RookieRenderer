//
// Created by wlxklyh on 2021/10/26.
//

#ifndef ROOKIERENDERER_AABB_H
#define ROOKIERENDERER_AABB_H

#include "MathUtil.h"
#include "Vec3.h"
#include "Ray.h"
namespace RMath{
    class AABB {
    public:
        FVec3 MinV;
        FVec3 MaxV;

        AABB(){};
        AABB(RMath::FVec3& min,RMath::FVec3& max){
            MaxV = max;
            MinV = min;
        }


        bool Hit(const Ray& ray, float &tMin,float &tMax){
            for(int i = 0; i < 3; i++){
                //避免除以0
                if(abs(ray.B[i]) < FLOAT_SMALL){
                    if(ray.A[i] < MinV[i] || ray.A[i] > MaxV[i]){
                        return false;
                    }else {
                        continue;
                    }
                }
                float t0 = RMath::Min((MinV[i] - ray.A[i]) / ray.B[i],
                                      (MaxV[i] - ray.A[i] / ray.B[i]));
                float t1 = RMath::Max((MinV[i] - ray.A[i]) / ray.B[i],
                                      (MaxV[i] - ray.A[i] / ray.B[i]));

                tMin = RMath::Min(tMin,t0);
                tMax = RMath::Max(tMax,t1);
                if(tMax <= tMin){
                    return false;
                }
            }
            return true;
        }

        static AABB MergeTwoBox(AABB& box1,AABB& box2){
            FVec3 min(RMath::Min(box1.MinV.X(),box2.MinV.X()),
                      RMath::Min(box1.MinV.Y(),box2.MinV.Y()),
                      RMath::Min(box1.MinV.Z(),box2.MinV.Z()));

            FVec3 max(RMath::Max(box1.MaxV.X(),box2.MaxV.X()),
                      RMath::Max(box1.MaxV.Y(),box2.MaxV.Y()),
                      RMath::Max(box1.MaxV.Z(),box2.MaxV.Z()));

            return AABB(min,max);

        }
    };

}

#endif //ROOKIERENDERER_AABB_H
