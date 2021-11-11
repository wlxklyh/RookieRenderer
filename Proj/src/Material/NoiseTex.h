//
// Created by linyanhou on 2021/11/11.
//

#ifndef ROOKIERENDERER_NOISETEX_H
#define ROOKIERENDERER_NOISETEX_H


#include "RMath.h"
#include "Texture.h"

class NoiseTex : public Texture {
public:
    NoiseTex() {}
    NoiseTex(float sc) : scale(sc) {}
    virtual FVec3 Value(float u, float v, const FVec3& p) const {
//            return FVec3(1,1,1)*0.5*(1 + noise.turb(scale * p));
//            return FVec3(1,1,1)*noise.turb(scale * p);
        return FVec3(1,1,1)*0.5*(1 + sin(scale*p.X() + 5*noise.turb(scale*p))) ;
    }
    Perlin noise;
    float scale;
};



#endif //ROOKIERENDERER_NOISETEX_H
