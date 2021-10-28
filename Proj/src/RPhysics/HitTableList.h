//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_HITTABLELIST_H
#define ROOKIERENDERER_HITTABLELIST_H

#include "Hitable.h"

namespace RPhysics {
    class HitTableList : public Hitable {
    public:
        int Size;
        Hitable **HitableList;

        HitTableList() {};

        HitTableList(Hitable **l, int size) : HitableList(l), Size(size) {};

        virtual bool Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const override;

        virtual bool BoundindBox(float t0, float t1, AABB &box) const override;
    };
}


#endif //ROOKIERENDERER_HITTABLELIST_H
