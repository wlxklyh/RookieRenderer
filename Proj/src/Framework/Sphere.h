//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_SPHERE_H
#define ROOKIERENDERER_SPHERE_H

#include "HitTable.h"

namespace RMath {
    class Sphere : public HitTable {
    public:
        FPoint3D Center;
        float Radius;

        Sphere() {};

        Sphere(FVec3 center, float radius) : Center(center), Radius(radius) {};

        virtual bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const;
    };
}


#endif //ROOKIERENDERER_SPHERE_H
