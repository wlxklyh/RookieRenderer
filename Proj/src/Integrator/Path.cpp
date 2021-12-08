//
// Created by linyanhou on 2021/12/6.
//

#include "Path.h"
#include "RPhysics.h"

FColorRGB PathIntegrator::Li(const Ray &ray, RPhysics::Hitable &world, int depth) const{
    RPhysics::HitRecord hitRecord;
    if (world.Hit(ray, 0.0001, MAXFLOAT, hitRecord)) {
        Ray scattered;
        FColorRGB attenuation;
        FColorRGB emitted = hitRecord.mat->Emitted(ray, hitRecord, hitRecord.u, hitRecord.v, hitRecord.p);
        if (depth < 50 && hitRecord.mat->Scatter(ray, hitRecord, attenuation, scattered)) {
            double p_RR = 0.6;
            double rValue = drand48();
            if(rValue < p_RR){
                FColorRGB retColor = Li(scattered, world, depth + 1);
                return retColor * attenuation  / p_RR;
            }
            else
            {
                return FColorRGB(0,0,0);
            }
        } else {
            return emitted;
        }
    } else {
//        FVec3 dir = ray.Direction();
//        FVec3 unitDir = unit_vector(dir);
//        float lerpValue = 0.5 * (unitDir.Y() + 1.0);
//        return (1 - lerpValue) * FColorRGB(1.0, 1.0, 1.0) + lerpValue * FColorRGB(0.5, 0.7, 1.0);
        //天空盒为黑色
        return FColorRGB(0,0,0);
    }
}