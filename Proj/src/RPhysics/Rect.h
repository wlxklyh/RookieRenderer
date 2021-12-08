//
// Created by linyanhou on 2021/11/15.
//

#ifndef ROOKIERENDERER_RECT_H
#define ROOKIERENDERER_RECT_H

#include "Hitable.h"
#include "AABB.h"

namespace RPhysics {
    template<int axisI0, int axisI1, int axisI2>
    class Rect2D : public Hitable {
    public:
        float axis0_0, axis0_1, axis1_0, axis1_1, axis2;
        MaterialBase *mat;

        Rect2D() { mat = nullptr; }

        Rect2D(float _axis0_0, float _axis0_1, float _axis1_0, float _axis1_1, float _axis2, MaterialBase *_mat)
                : axis0_0(_axis0_0), axis0_1(_axis0_1), axis1_0(_axis1_0), axis1_1(_axis1_1), axis2(_axis2), mat(_mat) {
        }

        virtual bool Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const {
            //平行一律看着没碰撞
            if (RMath::NearZero(ray.Direction()[axisI2])) {
                return false;
            }
            //看下跟Z平面是否有交点
            float t = (axis2 - ray.Origin()[axisI2]) / ray.Direction()[axisI2];
            if (t < t_min || t > t_max) {
                return false;
            }
            float axis0 = ray.Origin()[axisI0] + t * ray.Direction()[axisI0];
            float axis1 = ray.Origin()[axisI1] + t * ray.Direction()[axisI1];
            if (axis0 < axis0_0 || axis0 > axis0_1 || axis1 < axis1_0 || axis1 > axis1_1)
                return false;
            rec.u = (axis0 - axis0_0) / (axis0_1 - axis0_0);
            rec.v = (axis1 - axis1_0) / (axis1_1 - axis1_0);
            rec.t = t;
            rec.mat = mat;
            rec.p = ray.PointAtParameter(t);
            rec.normal = FVec3(0, 0, 0);
            rec.normal[axisI2] = 1;
            return true;
        }

        virtual bool BoundindBox(float t0, float t1, AABB &box) const {
            box = AABB(FVec3(axis0_0, axis1_0, axis2 - 0.0001), FVec3(axis0_1, axis1_1, axis2 + 0.0001));
            return true;
        }
    };

    typedef Rect2D<0, 1, 2> XYRect;
    typedef Rect2D<0, 2, 1> XZRect;
    typedef Rect2D<1, 2, 0> YZRect;

}


#endif //ROOKIERENDERER_RECT_H
