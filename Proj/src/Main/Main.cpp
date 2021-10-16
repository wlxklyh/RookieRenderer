#include <iostream>
#include <fstream>
#include "Ray.h"
#include "Sphere.h"
#include "Vec3.h"
#include "Hitable.h"
#include "HitTableList.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

using namespace RMath;


FColorRGB Color(const Ray &ray, Hitable &world, int depth) {
    HitRecord hitRecord;
    if (world.Hit(ray, 0.0001, MAXFLOAT, hitRecord)) {
        Ray scattered;
        FColorRGB attenuation;
        if (depth < 50 && hitRecord.mat->Scatter(ray, hitRecord, attenuation, scattered)) {
            FColorRGB retColor = Color(scattered, world, depth + 1);
            return retColor * attenuation;
        } else {
            return FColorRGB(0, 0, 0);
        }
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
    const int listSize = 5;
    Hitable *list[listSize];
    list[0] = new Sphere(FVec3(0, 0, -1), 0.5, new Lambertian(FColorRGB(0.8, 0.3, 0.3)));
    list[1] = new Sphere(FVec3(0, -100.5, -1), 100, new Lambertian(FColorRGB(0.8, 0.8, 0.0)));
    list[2] = new Sphere(FVec3(1, 0, -1), 0.5, new Metal(FColorRGB(0.8, 0.6, 0.2), 0.3));
    list[3] = new Sphere(FVec3(-1, 0, -1), 0.5, new Dielectric( 1.5));
    list[4] = new Sphere(FVec3(-1, 0, -1), -0.45, new Dielectric( 1.5));

    Hitable *world = new HitTableList(list, listSize);

    //（4）相机
    Camera camera;
    for (int y = PicH - 1; y >= 0; y--) {
        for (int x = 0; x < PicW; x++) {

            FColorRGB color(0, 0, 0);
            for (int samplesIndex = 0; samplesIndex < SamplesPerPixel; ++samplesIndex) {
                float u = float(x + drand48()) / float(PicW);
                float v = float(y + drand48()) / float(PicH);
                Ray ray = camera.GetRay(u, v);
                FColorRGB col = Color(ray, *world, 0);
                color += col;
            }
            color = color / SamplesPerPixel;
            //gamma矫正
            color = FColorRGB(sqrt(color.R()), sqrt(color.G()), sqrt(color.B()));
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