//
// Created by wlxklyh on 2021/10/16.
//

#include "AABB.h"
#include "HitTableList.h"

namespace RPhysics {

    bool HitTableList::Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const {
        bool hitAnything = false;
        HitRecord recTmp;
        double closestTime = t_max;
        for (int i = 0; i < Size; ++i) {
            if (HitableList[i]->Hit(ray, t_min, closestTime, recTmp)) {
                hitAnything = true;
                closestTime = recTmp.t;
                rec = recTmp;
            }
        }
        return hitAnything;
    }

    bool HitTableList::BoundindBox(float t0, float t1, AABB &box) const {
        if (Size < 1) {
            return false;
        }
        AABB nowMergeAABB;
        bool firstHasBox = HitableList[0]->BoundindBox(t0, t1, nowMergeAABB);
        if (!firstHasBox) {
            return false;
        } else {
            box.MinV = nowMergeAABB.MinV;
            box.MaxV = nowMergeAABB.MaxV;
        }
        for (int i = 1; i < Size; ++i) {
            box = MergeTwoBox(box, nowMergeAABB);
        }
        return true;
    }
}