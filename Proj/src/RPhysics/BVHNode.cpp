//
// Created by wlxklyh on 2021/10/29.
//

#include "BVHNode.h"
#include "AABB.h"

namespace RPhysics {
    template<int index>
    int BoxCompareX(const void *a, const void *b) {
        AABB leftBox;
        AABB rightBox;
        Hitable *ah = *(Hitable **) a;
        Hitable *bh = *(Hitable **) b;

        if (leftBox.MinV[index] - rightBox.MinV[index] < 0) {
            return -1;
        } else {
            return 1;
        }
    }

    BVHNode::BVHNode(Hitable **list, int n, float time0, float time1) {
        int axis = int(3 * drand48());
        if (axis == 0) {
            qsort(list, n, sizeof(Hitable *), BoxCompareX<0>);
        } else if (axis == 1) {
            qsort(list, n, sizeof(Hitable *), BoxCompareX<1>);
        } else if (axis == 2) {
            qsort(list, n, sizeof(Hitable *), BoxCompareX<2>);
        }

        if (n == 1) {
            Left = Right = list[0];
        } else if (n == 2) {
            Left = list[0];
            Right = list[1];
        } else {
            Left = new BVHNode(list, n / 2, time0, time1);
            Right = new BVHNode(list + n / 2, n - n / 2, time0, time1);
        }
        AABB leftBox;
        AABB rightBox;
        if(!Left->BoundindBox(time0,time1,leftBox) || !Right->BoundindBox(time0,time1,rightBox)){
            //error
        }
        BoundingAABB = MergeTwoBox(leftBox, rightBox);
    }

    bool BVHNode::Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const {
        if (BoundingAABB.Hit(ray, t_min, t_max))
        {
            HitRecord leftRec;
            HitRecord rightRec;
            bool hitLeft = Left->Hit(ray, t_min, t_max, leftRec);
            bool hitRight = Right->Hit(ray, t_min, t_max, rightRec);
            if (hitLeft && hitRight) {
                if (leftRec.t < rightRec.t) {
                    rec = leftRec;
                } else {
                    rec = rightRec;
                }
                return true;
            } else if (hitLeft) {
                rec = leftRec;
                return true;
            } else if (hitRight) {
                rec = rightRec;
                return true;
            }else{
                return false;
            }

        } else {
            return false;
        }
    }

    bool BVHNode::BoundindBox(float t0, float t1, AABB &box) const {
        box.MaxV = BoundingAABB.MaxV;
        box.MinV = BoundingAABB.MinV;
        return true;
    }


}