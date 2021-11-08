//
// Created by linyanhou on 2021/11/9.
//

#ifndef ROOKIERENDERER_CHECKERTEX_H
#define ROOKIERENDERER_CHECKERTEX_H

#include "Texture.h"
class CheckerTex:  public Texture {
public:
    Texture *odd;
    Texture *even;

    CheckerTex() { }
    CheckerTex(Texture *t0, Texture *t1): even(t0), odd(t1) { }
    virtual FVec3 Value(float u, float v, const FVec3& p) const {
        float sines = sin(10*p.X())*sin(10*p.Y())*sin(10*p.Z());
        if (sines < 0)
            return odd->Value(u, v, p);
        else
            return even->Value(u, v, p);
    }
};


#endif //ROOKIERENDERER_CHECKERTEX_H
