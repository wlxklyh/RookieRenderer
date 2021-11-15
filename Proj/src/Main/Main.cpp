#include <iostream>
#include <fstream>

#include "RMath.h"
#include "RPhysics.h"
#include "Framework.h"
#include "Material.h"
#include "Camera.h"
#include "Config.h"

using namespace RMath;
using namespace RPhysics;

Hitable *RandomScene() {
    Texture *checker = new CheckerTex( new ConstantTex(FColorRGB (0.2,0.3, 0.1)),
                                       new ConstantTex(FColorRGB(0.9, 0.9, 0.9)));
    int num = 1;
    Hitable **list = new Hitable *[num + 10];
    list[0] = new Sphere(FVec3(0, -1000, 0), 1000, new Lambertian(new NoiseTex(4)));
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

    list[i++] = new Sphere(FVec3(-4, 1, 5), 1.0, new Lambertian(new NoiseTex(4)));
    list[i++] = new Sphere(FVec3(0, 1, 5), 1.0, new Lambertian(new NoiseTex(0.1f)));
    list[i++] = new Sphere(FVec3(4, 1, 5), 1.0, new Lambertian(new NoiseTex(1)));

    return new BVHNode(list, i,0.0,1.0);
    //return new HitTableList(list, i);
}

Hitable *CornelBox() {
    int i = 0;
    Hitable **list = new Hitable*[8];
    MaterialBase *red = new Lambertian( new ConstantTex(FVec3(0.65, 0.05, 0.05)) );
    MaterialBase *white = new Lambertian( new ConstantTex(FVec3(0.73, 0.73, 0.73)) );
    MaterialBase *green = new Lambertian( new ConstantTex(FVec3(0.12, 0.45, 0.15)) );
    MaterialBase *light = new DiffuseLight( new ConstantTex(FVec3(15, 15, 15)) );

    list[i++] = new FlipNormals(new YZRect(0, 555, 0, 555, 555, green));
    list[i++] = new YZRect(0, 555, 0, 555, 0, red);
    list[i++] = new FlipNormals(new XZRect(213, 343, 227, 332, 554, light));
    list[i++] = new FlipNormals(new XZRect(0, 555, 0, 555, 555, white));
    list[i++] = new XZRect(0, 555, 0, 555, 0, white);
    list[i++] = new FlipNormals(new XYRect (0, 555, 0, 555, 555, white));

    MaterialBase *glass = new Dielectric(1.5);
    MaterialBase *mirr = new Metal(FVec3(0.7, 0.6, 0.5), 0.0);
    list[i++] = new Sphere(FVec3(130, 90, 130),90 , glass);
    list[i++] = new Sphere(FVec3(395,90,310),90 , mirr);

    return new BVHNode(list, i,0.0,1.0);
    //return new HitTableList(list, i);
}

FColorRGB Color(const Ray &ray, Hitable &world, int depth) {
    HitRecord hitRecord;
    if (world.Hit(ray, 0.0001, MAXFLOAT, hitRecord)) {
        Ray scattered;
        FColorRGB attenuation;
        FColorRGB emitted = hitRecord.mat->Emitted(ray, hitRecord, hitRecord.u, hitRecord.v, hitRecord.p);
        if (depth < 50 && hitRecord.mat->Scatter(ray, hitRecord, attenuation, scattered)) {
            FColorRGB retColor = Color(scattered, world, depth + 1);
            return retColor * attenuation;
        } else {
            return emitted;
        }
    } else {
//        FVec3 dir = ray.Direction();
//        FVec3 unitDir = unit_vector(dir);
//        float lerpValue = 0.5 * (unitDir.Y() + 1.0);
//        return (1 - lerpValue) * FColorRGB(1.0, 1.0, 1.0) + lerpValue * FColorRGB(0.5, 0.7, 1.0);
        //天空盒为黑色
        return FColorRGB(0,0,0);
    }
}

void RunConfig(const Config& config){
    int startTime = clock();
    std::ofstream out;
    out.open(config.GetPPmFileName());

    //（1）宽高
    int PicW = config.PicW;
    int PicH = config.PicH;
    int SamplesPerPixel = config.SamplesPerPixel;
    std::string dec = config.GetProgressTips();
    // （2）这个是ppm图片格式 后面渲染的结果用这个来显示
    out << "P3\n" << PicW << " " << PicH << "\n255\n";

    Hitable *world = CornelBox();
    //（4）相机
    FVec3 lookfrom(278, 278, -800);
    FVec3 lookat(278,278,0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 40.0;
    float aspect = float(PicH) / float(PicW);
    Camera *cam = new Camera(lookfrom, lookat, FVec3(0,1,0),
                             vfov, aspect, aperture, dist_to_focus);
    for (int y = PicH - 1; y >= 0; y--) {
        for (int x = 0; x < PicW; x++) {

            FColorRGB color(0, 0, 0);
            for (int samplesIndex = 0; samplesIndex < SamplesPerPixel; ++samplesIndex) {
                float u = float(x + drand48()) / float(PicW);
                float v = float(y + drand48()) / float(PicH);
                Ray ray = cam->GetRay(u, v);
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
        std::cout<< dec <<"Progress:"<< nowProgress * 100 << "% "
                 << "Already cost:" << costTime << " minutes"
                 << " Still need:" << costTime / nowProgress * (1-nowProgress)<< " minutes\n";
    }
    std::ofstream outTime;
    outTime.open(config.GetLogFileName());

    outTime << "Width:" << PicW << " Height:" << PicH << " Samples:" << SamplesPerPixel << "\n";
    outTime << float(clock() - startTime) / (float) CLOCKS_PER_SEC / 60.0f << " minutes\n";
    out.close();

    // 打开结果图片
#ifdef _WIN32
    system(config.GetWinOpenCmd().c_str());
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
    FILE *pp = popen(GetMacOpenCmd.c_str(), "r");
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

}

int main() {
    RunConfig(Config("CornelBox",500,500,1));
    RunConfig(Config("CornelBox",500,500,8));
    RunConfig(Config("CornelBox",500,500,12));
    RunConfig(Config("CornelBox",500,500,40));
    RunConfig(Config("CornelBox",500,500,200));
    RunConfig(Config("CornelBox",500,500,1000));
    RunConfig(Config("CornelBox",500,500,5000));
    RunConfig(Config("CornelBox",500,500,25000));
    return 0;
}