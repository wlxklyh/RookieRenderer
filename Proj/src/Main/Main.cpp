#include <iostream>
#include <fstream>
#include "Ray.h"
#include "Sphere.h"
#include "Vec3.h"
#include "HitTable.h"
#include "HitTableList.h"
#include "Camera.h"

using namespace RMath;


FColorRGB Color(const Ray &ray, HitTable &world) {
    HitRecord hitRecord;
    if (world.Hit(ray, 0.0, MAXFLOAT, hitRecord)) {
        return 0.5f * hitRecord.normal + 0.5f;
    } else {
        FVec3 dir = ray.Direction();
        FVec3 unitDir = unit_vector(dir);
        float lerpValue = 0.5 * (unitDir.Y() + 1.0);
        return (1 - lerpValue) * FColorRGB(1.0, 1.0, 1.0) + lerpValue * FColorRGB(0.5, 0.7, 1.0);
    }
}


int main() {
    std::ofstream out;
    out.open("OutputPic.ppm");

    //（1）宽高
    int PicW = 200;
    int PicH = 100;
    int SamplesPerPixel = 100;
    // （2）这个是ppm图片格式 后面渲染的结果用这个来显示
    out << "P3\n" << PicW << " " << PicH << "\n255\n";

    // (3)场景里面有两个球
    HitTable *list[2];
    list[0] = new Sphere(FVec3(0, 0, -1), 0.5);
    list[1] = new Sphere(FVec3(0, -100.5, -1), 100);
    HitTable *world = new HitTableList(list, 2);

    //（4）相机
    Camera camera;
    for (int y = PicH - 1; y >= 0; y--) {
        for (int x = 0; x < PicW; x++) {

            FColorRGB color(0, 0, 0);
            for (int samplesIndex = 0; samplesIndex < SamplesPerPixel; ++samplesIndex) {
                float u = float(x ) / float(PicW);
                float v = float(y ) / float(PicH);
                Ray ray = camera.GetRay(u, v);
                FColorRGB col = Color(ray, *world);
                color += col;
            }
            color = color / SamplesPerPixel;
            int ir = int(255.99 * color[0]);
            int ig = int(255.99 * color[1]);
            int ib = int(255.99 * color[2]);
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    out.close();

    // 打开结果图片
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