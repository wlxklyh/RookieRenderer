//
// Created by wlxklyh on 2021/10/16.
//

#include "Hitable.h"

namespace RPhysics{

     bool FlipNormals::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
        if (ptr->Hit(r, t_min, t_max, rec)) {
            rec.normal = -rec.normal;
            return true;
        }
        else
            return false;
    }
     bool FlipNormals::BoundindBox(float t0, float t1, AABB& box) const {
        return ptr->BoundindBox(t0, t1, box);
    }
}