//
// Created by linyanhou on 2021/11/11.
//

#ifndef ROOKIERENDERER_PERLIN_H
#define ROOKIERENDERER_PERLIN_H

#include "RMath.h"

using namespace RMath;

namespace RMath {

    float perlin_interp(FVec3 c[2][2][2], float u, float v, float w) ;
    class Perlin {
    public:
        float noise(const FVec3& p) const {
            float u = p.X() - floor(p.X());
            float v = p.Y() - floor(p.Y());
            float w = p.Z() - floor(p.Z());
            int i = floor(p.X());
            int j = floor(p.Y());
            int k = floor(p.Z());
            FVec3 c[2][2][2];
            for (int di=0; di < 2; di++)
                for (int dj=0; dj < 2; dj++)
                    for (int dk=0; dk < 2; dk++)
                        c[di][dj][dk] = ranvec[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];
            return perlin_interp(c, u, v, w);
        }
        float turb(const FVec3& p, int depth=7) const {
            float accum = 0;
            FVec3 temp_p = p;
            float weight = 1.0;
            for (int i = 0; i < depth; i++) {
                accum += weight*noise(temp_p);
                weight *= 0.5;
                temp_p *= 2;
            }
            return fabs(accum);
        }
        static FVec3 *ranvec;
        static int *perm_x;
        static int *perm_y;
        static int *perm_z;
    };

    void permute(int *p, int n);

    static FVec3* perlin_generate();

    static int* perlin_generate_perm() ;



}
#endif //ROOKIERENDERER_PERLIN_H
