//
// Created by linyanhou on 2021/11/9.
//

#ifndef ROOKIERENDERER_TEXTURE_H
#define ROOKIERENDERER_TEXTURE_H

#include "RMath.h"

using namespace RMath;

class Texture {
public:
    virtual FVec3 Value(float u,float v, const FVec3& p) const = 0;
};

#endif //ROOKIERENDERER_TEXTURE_H
