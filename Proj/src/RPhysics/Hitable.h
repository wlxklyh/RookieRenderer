//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_HITABLE_H
#define ROOKIERENDERER_HITABLE_H

#include "RMath.h"
#include "AABB.h"

class MaterialBase;

namespace RPhysics {
    struct HitRecord {
        HitRecord(){mat = nullptr;}
        float u;
        float v;
        float t;
        RMath::FVec3 p;
        RMath::FVec3 normal;
        MaterialBase *mat;
    };

    struct ScatterRecord {
        ScatterRecord(){
            f_r = 1.0;
            pdf = 1.0;
        }
        float f_r;
        float pdf;
        Ray scatterRay;
    };

    class Hitable {
    public:
        //这个碰撞体的碰撞函数
        virtual bool Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const = 0;
        //这个碰撞体的包围盒：获取当前碰撞体的包围盒 这样就可以计算BVH的merge
        virtual bool BoundindBox(float t0, float t1, AABB &box) const = 0;
    };

    class FlipNormals : public Hitable {
    public:
        Hitable *ptr;
        FlipNormals(Hitable *p) : ptr(p) {}
        virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
        virtual bool BoundindBox(float t0, float t1, AABB& box) const;
    };
}


#endif //ROOKIERENDERER_HITABLE_H
