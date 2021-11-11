//
// Created by linyanhou on 2021/11/11.
//

#include "Perlin.h"

namespace RMath {
    FVec3 *Perlin::ranvec = perlin_generate();
    int *Perlin::perm_x = perlin_generate_perm();
    int *Perlin::perm_y = perlin_generate_perm();
    int *Perlin::perm_z = perlin_generate_perm();


    float perlin_interp(FVec3 c[2][2][2], float u, float v, float w) {
        float uu = u * u * (3 - 2 * u);
        float vv = v * v * (3 - 2 * v);
        float ww = w * w * (3 - 2 * w);
        float accum = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) {
                    FVec3 weight_v(u - i, v - j, w - k);
                    accum += (i * uu + (1 - i) * (1 - uu)) *
                             (j * vv + (1 - j) * (1 - vv)) *
                             (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight_v);
                }
        return accum;
    }

    void permute(int *p, int n) {
        for (int i = n - 1; i > 0; i--) {
            int target = int(drand48() * (i + 1));
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
        return;
    }

    FVec3* perlin_generate() {
        FVec3 * p = new FVec3[256];
        for ( int i = 0; i < 256; ++i )
            p[i] = unit_vector(FVec3(-1 + 2*drand48(), -1 + 2*drand48(), -1 + 2*drand48()));
        return p;
    }



    int* perlin_generate_perm() {
        int * p = new int[256];
        for (int i = 0; i < 256; i++)
            p[i] = i;
        permute(p, 256);
        return p;
    }
}