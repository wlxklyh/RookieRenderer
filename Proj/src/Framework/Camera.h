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
    FVec3 u, v, w;

    Camera(FPoint3D lookFrom, FVec3 lookAt, FVec3 vUp, float vfov, float aspect) {
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        Origin = lookFrom;
        w = unit_vector(lookFrom - lookAt);
        u = unit_vector(cross(vUp, w));
        v = cross(w, u);
        LeftBottomCorner = Origin - half_width * u - half_height * v - w;
        Horizontal = 2 * half_width * u;
        Vertical = 2 * half_height * v;

    }

    Ray GetRay(float u, float v) {
        return Ray(Origin, LeftBottomCorner + u * Horizontal + v * Vertical - Origin);
    }

};


#endif //ROOKIERENDERER_CAMERA_H
