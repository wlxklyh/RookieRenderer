//
// Created by linyanhou on 2021/11/15.
//

#ifndef ROOKIERENDERER_DIFFUSELIGHT_H
#define ROOKIERENDERER_DIFFUSELIGHT_H

#include "MaterialBase.h"
//class DiffuseLight :public MaterialBase {
//public:
//    DiffuseLight(texture *a) : emit(a) {}
//    virtual vec3 emitted(const ray& r_in, const hit_record& rec, float u, float v, const vec3& p) const {
//        if (dot(rec.normal, r_in.direction()) < 0.0)
//            return emit->value(u, v, p);
//        else
//            return vec3(0,0,0);
//    }
//    texture *emit;
//};


#endif //ROOKIERENDERER_DIFFUSELIGHT_H
