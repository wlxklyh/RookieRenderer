//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_HITTABLELIST_H
#define ROOKIERENDERER_HITTABLELIST_H

#include "HitTable.h"

namespace RMath {
    class HitTableList : public HitTable {
    public:
        int Size;
        HitTable **List;

        HitTableList() {};

        HitTableList(HitTable **l, int size) : List(l), Size(size) {};

        virtual bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
    };
}


#endif //ROOKIERENDERER_HITTABLELIST_H
