#include <iostream>
#include <fstream>
#include "Ray.h"
#include "Vec3.h"

using namespace RMath;

float HitSphere(const FPoint3D &center, float radius, const Ray &ray) {
    FVec3 Origin2Center = ray.Origin() - center;
    float a = dot(ray.Direction(), ray.Direction());
    float b = 2.0 * dot(Origin2Center, ray.Direction());
    float c = dot(Origin2Center, Origin2Center) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    //选择t小的那个值 是首先hit到的
    return (-sqrt(discriminant) - b) / (2.0 * a);
}

FColorRGB Color(const Ray &ray) {
    float t = HitSphere(FPoint3D(0, 0, -1), 0.5, ray);
    if (t > 0) {
        FVec3 normal = unit_vector(ray.PointAtParameter(t) - FVec3(0, 0, -1));
        return 0.5f * normal + 0.5f;
    }
    FVec3 dir = ray.Direction();
    FVec3 unitDir = unit_vector(dir);
    float lerpValue = 0.5 * (unitDir.Y() + 1.0);
    return (1 - lerpValue) * FColorRGB(1.0, 1.0, 1.0) + lerpValue * FColorRGB(0.5, 0.7, 1.0);
}


int main() {
    std::ofstream out;
    out.open("OutputPic.ppm");

    //（1）宽高
    int PicW = 200;
    int PicH = 100;

    // （2）这个是ppm图片格式 后面渲染的结果用这个来显示
    out << "P3\n" << PicW << " " << PicH << "\n255\n";

    FPoint3D leftbottomCorner(-2.0, -1.0, -1.0);
    FVec3 horizontal(4, 0, 0);
    FVec3 vertical(0, 2, 0);
    FPoint3D origin(0, 0, 0);
    Ray ray(origin, leftbottomCorner);
    for (int y = PicH - 1; y >= 0; y--) {
        for (int x = 0; x < PicW; x++) {
            float u = float(x) / float(PicW);
            float v = float(y) / float(PicH);
            ray.B = leftbottomCorner + u * horizontal + v * vertical;
            FColorRGB color = Color(ray);
            int ir = int(255.99 * color[0]);
            int ig = int(255.99 * color[1]);
            int ib = int(255.99 * color[2]);
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    out.close();

    // (3)打开结果图片
#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
      //define something for Windows (64-bit only)
#else
      //define something for Windows (32-bit only)
#endif
#elif __APPLE__

#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
#elif TARGET_OS_IPHONE
    // iOS device
#elif TARGET_OS_MAC
    // Other kinds of Mac OS
    FILE *pp = popen("open OutputPic.ppm", "r");
#else
#   error "Unknown Apple platform"
#endif
#elif __ANDROID__
    // android
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif

    return 0;
}