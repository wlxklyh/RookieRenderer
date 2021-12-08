//
// Created by linyanhou on 2021/12/6.
//

#include "Path.h"
#include "RPhysics.h"

FColorRGB PathIntegrator::Li(const Ray &ray, RPhysics::Hitable &world, int depth) const{
    RPhysics::HitRecord hitRecord;
    //(1)什么都没击中那么返回天空盒 没有天空和则黑色
    if (world.Hit(ray, 0.0001, MAXFLOAT, hitRecord) == false) {
        //天空盒为黑色
        return FColorRGB(0,0,0);
    }

    //(2)递归深度太深了 返回黑色 无效光线
    if(depth > 50){
        return FColorRGB(0,0,0);
    }

    RPhysics::ScatterRecord scatterRecord;
    FColorRGB attenuation;
    //(3)光源没有散射 Scatter会返回false 所以直接去返回emitted了
    if (hitRecord.mat->Scatter(ray, hitRecord, attenuation, scatterRecord) == false) {
        FColorRGB emitted = hitRecord.mat->Emitted(ray, hitRecord, hitRecord.u, hitRecord.v, hitRecord.p);
        return emitted;
    }

    //(4)RR的PDF和蒙特卡洛积分的pdf
    double p_RR = 0.6;
    double rValue = drand48();
    if(rValue < p_RR){
        return Li(scatterRecord.scattered, world, depth + 1) * scatterRecord.f_r * attenuation / scatterRecord.pdf / p_RR;
    }
    else
    {
        return FColorRGB(0,0,0);
    }

}

//天空盒备份
//        FVec3 dir = ray.Direction();
//        FVec3 unitDir = unit_vector(dir);
//        float lerpValue = 0.5 * (unitDir.Y() + 1.0);
//        return (1 - lerpValue) * FColorRGB(1.0, 1.0, 1.0) + lerpValue * FColorRGB(0.5, 0.7, 1.0);