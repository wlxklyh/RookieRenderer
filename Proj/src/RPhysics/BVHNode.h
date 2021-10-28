//
// Created by wlxklyh on 2021/10/29.
//

#ifndef ROOKIERENDERER_BVHNODE_H
#define ROOKIERENDERER_BVHNODE_H

#include "Hitable.h"
#include "AABB.h"

namespace RPhysics {
    class BVHNode : public Hitable {
    public:
        Hitable *Left;
        Hitable *Right;
        AABB BoundingAABB;

        BVHNode() {};

        BVHNode(Hitable **list, int n, float time0, float time1);

        virtual bool Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const override;

        virtual bool BoundindBox(float t0, float t1, AABB &box) const override;
    };

}


#endif //ROOKIERENDERER_BVHNODE_H
