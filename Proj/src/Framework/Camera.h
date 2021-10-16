//
// Created by wlxklyh on 2021/10/16.
//

#ifndef ROOKIERENDERER_CAMERA_H
#define ROOKIERENDERER_CAMERA_H

#include "../RMath/Vec3.h"
#include "../RMath/Ray.h"

using namespace RMath;

class Camera {
public:
    FPoint3D Origin;
    FPoint3D LeftBottomCorner;
    FVec3 Horizontal;
    FVec3 Vertical;

    Camera() {
        LeftBottomCorner = FPoint3D(-2.0, -1.0, -1.0);
        Horizontal = FVec3(4, 0, 0);
        Vertical = FVec3(0, 2, 0);
        Origin = FPoint3D(0, 0, 0);
    }

    Ray GetRay(float u, float v) {
        return Ray(Origin, LeftBottomCorner + u * Horizontal + v * Vertical - Origin);
    }

};


#endif //ROOKIERENDERER_CAMERA_H
