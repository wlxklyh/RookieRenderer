//
// Created by linyanhou on 2021/11/9.
//

#ifndef ROOKIERENDERER_CONSTANTTEX_H
#define ROOKIERENDERER_CONSTANTTEX_H

#include "Texture.h"

class ConstantTex :public Texture{
public:
    FColorRGB Color;
    ConstantTex(){};
    ConstantTex(FVec3 c):Color(c){};
    FVec3 Value(float u,float v, const FVec3& p)const override{
        return  Color;
    }
};


#endif //ROOKIERENDERER_CONSTANTTEX_H
