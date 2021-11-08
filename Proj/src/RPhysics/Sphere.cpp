//
// Created by wlxklyh on 2021/10/16.
//

#include "Sphere.h"


namespace RPhysics {
    void get_sphere_uv(const FVec3 & p, float& u, float& v) {
        float phi = atan2(p.Z(), p.X());
        float theta = asin(p.Y());
        u = 1-(phi + M_PI) / (2*M_PI);
        v = (theta + M_PI/2) / M_PI;
    }


    bool Sphere::Hit(const RMath::Ray &ray, float t_min, float t_max, HitRecord &rec) const {
        RMath::FVec3 Origin2Center = ray.Origin() - Center;
        float a = dot(ray.Direction(), ray.Direction());
        float b = 2.0 * dot(Origin2Center, ray.Direction());
        float c = dot(Origin2Center, Origin2Center) - Radius * Radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        }
        float t[2];
        t[0] = (-sqrt(discriminant) - b) / (2.0 * a);
        t[1] = (+sqrt(discriminant) - b) / (2.0 * a);
        for (int i = 0; i < 2; i++) {
            if (t[i] < t_max && t[i] > t_min) {
                rec.t = t[i];
                rec.p = ray.PointAtParameter(t[i]);
                get_sphere_uv((rec.p- Center)/Radius,rec.u,rec.v);
                rec.normal = (rec.p - Center) / Radius;
                rec.mat = MatPtr;
                return true;
            }
        }
        return false;
    }

    bool Sphere::BoundindBox(float t0, float t1, AABB &box) const {
        box.MinV = Center - RMath::FVec3(Radius, Radius, Radius);
        box.MaxV = Center + RMath::FVec3(Radius, Radius, Radius);
        return true;
    }

}