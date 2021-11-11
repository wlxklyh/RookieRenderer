//
// Created by wlxklyh on 2021/10/14.
//

#include "MathUtil.h"

namespace RMath {

    int RandInt(int MIN,int MAX){
        std::uniform_int_distribution<int> distr(MIN, MAX);
        return distr(eng);
    }
}