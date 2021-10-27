//
// Created by wlxklyh on 2021/10/26.
//

#include "AABB.h"

namespace RPhysics{
    static AABB MergeTwoBox(AABB &box1, AABB &box2) {
        RMath::FVec3 min(RMath::Min(box1.MinV.X(), box2.MinV.X()),
                  RMath::Min(box1.MinV.Y(), box2.MinV.Y()),
                  RMath::Min(box1.MinV.Z(), box2.MinV.Z()));

        RMath::FVec3 max(RMath::Max(box1.MaxV.X(), box2.MaxV.X()),
                  RMath::Max(box1.MaxV.Y(), box2.MaxV.Y()),
                  RMath::Max(box1.MaxV.Z(), box2.MaxV.Z()));

        return AABB(min, max);
    }
}
