#include <iostream>
#include <fstream>

#include "RMath.h"
#include "RPhysics.h"
#include "Framework.h"
#include "Material.h"
#include "Camera.h"

using namespace RMath;
using namespace RPhysics;

Hitable *RandomScene() {
    Texture *checker = new CheckerTex( new ConstantTex(FColorRGB (0.2,0.3, 0.1)),
                                       new ConstantTex(FColorRGB(0.9, 0.9, 0.9)));
    int num = 500;
    Hitable **list = new Hitable *[num + 10];
    list[0] = new Sphere(FVec3(0, -1000, 0), 1000, new Lambertian(checker));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        if (i >= num) {
            break;
        }
        for (int b = -11; b < 11; b++) {
            if (i >= num) {
                break;
            }
            float choose_mat = RandomDouble();
            FVec3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());
            if ((center - FVec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new Sphere(
                            center, 0.2,
                            new Lambertian(new ConstantTex(FVec3(RandomDouble() * RandomDouble(),
                                                 RandomDouble() * RandomDouble(),
                                                 RandomDouble() * RandomDouble())))
                    );
                } else if (choose_mat < 0.95) { // metal
                    list[i++] = new Sphere(
                            center, 0.2,
                            new Metal(FVec3(0.5 * (1 + RandomDouble()),
                                            0.5 * (1 + RandomDouble()),
                                            0.5 * (1 + RandomDouble())),
                                      0.5 * RandomDouble())
                    );
                } else {  // glass
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    //list[i++] = new Sphere(FVec3(0, 1, 0), 1.0, new Dielectric(1.5));
//    list[i++] = new Sphere(FVec3(-4, 1, 0), 1.0, new Lambertian(FVec3(0.4, 0.2, 0.1)));
//    list[i++] = new Sphere(FVec3(4, 1, 0), 1.0, new Metal(FVec3(0.7, 0.6, 0.5), 0.0));

    list[i++] = new Sphere(FVec3(-4, 1, 5), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(FVec3(0, 1, 5), 1.0, new Lambertian(new ConstantTex(FVec3(237.0 / 255.0, 107.0 / 255.0, 126.0 / 255.0))));
    list[i++] = new Sphere(FVec3(4, 1, 5), 1.0, new Metal(FVec3(0.7, 0.6, 0.5), 0.0));

    return new BVHNode(list, i,0.0,1.0);
    //return new HitTableList(list, i);
}

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
    int startTime = clock();
    std::ofstream out;
    out.open("OutputPic.ppm");


    //（1）宽高
    int PicW = 200;
    int PicH = 100;
    int SamplesPerPixel = 1;

    PicW = 200;
    PicH = 100;
    SamplesPerPixel = 1;

    // （2）这个是ppm图片格式 后面渲染的结果用这个来显示
    out << "P3\n" << PicW << " " << PicH << "\n255\n";

    // (3)场景里面有两个球
    const int listSize = 5;
    Hitable *list[listSize];
    list[0] = new Sphere(FVec3(0, 0, -1), 0.5, new Lambertian(new ConstantTex(FColorRGB(0.8, 0.3, 0.3))));
    list[1] = new Sphere(FVec3(0, -100.5, -1), 100, new Lambertian(new ConstantTex(FColorRGB(0.8, 0.8, 0.0))));
    list[2] = new Sphere(FVec3(1, 0, -1), 0.5, new Metal(FColorRGB(0.8, 0.6, 0.2), 0.3));
    list[3] = new Sphere(FVec3(-1, 0, -1), 0.5, new Dielectric(1.5));
    list[4] = new Sphere(FVec3(-1, 0, -1), -0.45, new Dielectric(1.5));

    //Hitable *world = new HitTableList(list, listSize);
    Hitable *world = RandomScene();
    //（4）相机
    FVec3 lookFrom(0, 1.5, 8.5), lookAt(0, 1, 5);
    float distFocus = (lookFrom - lookAt).length();
    Camera camera(lookFrom, lookAt, FVec3(0, 1, 0),
                  90, float(PicW) / float(PicH), 0.0001, distFocus);
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
        float costTime = (float)(clock() - startTime)/ (float) CLOCKS_PER_SEC / 60.0f;
        float nowProgress = ((PicH - y) * 1.0f) / (PicH * 1.0f);
        std::cout<<"Progress:"<< nowProgress * 100 << "% "
        << "Already cost:" << costTime << " minutes"
        << " Still need:" << costTime / nowProgress * (1-nowProgress)<< " minutes\n";
    }
    std::ofstream outTime;
    outTime.open("OutputTime.txt");

    outTime << "Width:" << PicW << " Height:" << PicH << " Samples:" << SamplesPerPixel << "\n";
    outTime << float(clock() - startTime) / (float) CLOCKS_PER_SEC / 60.0f << " minutes\n";
    out.close();

    // 打开结果图片
#ifdef _WIN32
    system(" start .\\OutputPic.ppm");
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