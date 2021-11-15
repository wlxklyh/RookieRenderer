//
// Created by linyanhou on 2021/11/15.
//

#ifndef ROOKIERENDERER_BOX_H
#define ROOKIERENDERER_BOX_H

#include "Hitable.h"
#include "HitTableList.h"
#include "Rect.h"
namespace RPhysics{
    class Box: public Hitable  {
    public:
        FVec3 Min, Max;
        Box() {}
        Box(const FVec3& p0, const FVec3& p1, MaterialBase *ptr)
        {
            Min = p0;
            Max = p1;
            Hitable **list = new Hitable*[6];
            list[0] = new XYRect(p0.X(), p1.X(), p0.Y(), p1.Y(), p1.Z(), ptr);
            list[1] = new FlipNormals(new XYRect (p0.X(), p1.X(), p0.Y(), p1.Y(), p0.Z(), ptr));
            list[2] = new XZRect(p0.X(), p1.X(), p0.Z(), p1.Z(), p1.Y(), ptr);
            list[3] = new FlipNormals(new XZRect(p0.X(), p1.X(), p0.Z(), p1.Z(), p0.Y(), ptr));
            list[4] = new YZRect(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p1.X(), ptr);
            list[5] = new FlipNormals(new YZRect(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p0.X(), ptr));
            list_ptr = new HitTableList(list,6);
        }
        virtual bool Hit(const Ray& r, float t0, float t1, HitRecord& rec) const;
        virtual bool BoudingBox(float t0, float t1, AABB& box) const {
            box =  AABB(Min, Max);
            return true;
        }
        Hitable *list_ptr;
    };
}

#endif //ROOKIERENDERER_BOX_H
