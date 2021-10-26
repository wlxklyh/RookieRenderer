//
// Created by wlxklyh on 2021/10/14.
//

#ifndef ROOKIERENDERER_MATHUTIL_H
#define ROOKIERENDERER_MATHUTIL_H

#include "Macro.h"

namespace RMath {
#define FLOAT_SMALL 0.0000000001

    template<class T>
    FORCEINLINE T Min(T value1, T value2) {
        return value1 < value2?value1:value2;
    }

    template<class T>
    FORCEINLINE T Max(T value1, T value2) {
        return value1 > value2?value1:value2;
    }


}
#endif //ROOKIERENDERER_MATHUTIL_H
