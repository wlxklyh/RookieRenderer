//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_HITTABLE_H
#define ROOKIERENDERER_HITTABLE_H

#include "Ray.h"


namespace RMath {
    struct HitRecord {
        float t;
        FVec3 p;
        FVec3 normal;
    };

    class HitTable {
    public:
        virtual bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const = 0;
    };
}


#endif //ROOKIERENDERER_HITTABLE_H
