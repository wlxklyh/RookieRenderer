//
// Created by linyanhou on 2021/11/16.
//

#include "Pdf.h"
namespace RMath {
    FVec3 RandomInUnitSphere() {
        RMath::FVec3 p;
        do {
            p = 2.0 * RMath::FVec3(drand48(), drand48(), drand48()) - RMath::FVec3(1, 1, 1);
        } while (p.squared_length() >= 1.0);
        return p;
    }
}