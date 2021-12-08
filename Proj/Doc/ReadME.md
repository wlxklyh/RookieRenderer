# RookieRenderer 

![windows](https://github.com/wlxklyh/RookieRenderer/actions/workflows/cmake-win.yml/badge.svg) ![macOS](https://github.com/wlxklyh/RookieRenderer/actions/workflows/macos-ci.yml/badge.svg)

## Final Result

----
![](Img/BasicPpathTracing/CornelBox500x500x25000sppResultPic.jpg)
![](Img/BasicPathTracing-blueredResult/CornelBox500x500x25000sppResultPic.jpg)

----
![](Img/OutputPic.jpg)
![](Img/OutputPic1000x2000x100SppNextWeekChapter3.jpg)

## 1. Ray Tracing in a weekend Practice Proj


This project is a practice program for [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). Petershirley YYDS.
### Build

- You can use Clion to open proj dir on windows platform or mac platform
- Also you can use cmake and cmake build the proj.
- Also, you can use vs on windows platform.Run generate_sln.bat to generate vs solution.

### Step Pic

You can checkout the version you want:

![](Img/commitlog.png)

|Chapter|Pic|Descript|
|-|-|-|
|Chapter1 Output an image|![Chapter1](Img/Chapter1.png)||
|Chapter2 The vec3 class|![Chapter2](Img/Chapter1.png)||
|Chapter3 Rays, camera, backgroud|![Chapter3](Img/Chapter3.png)||
|Chapter4 Adding a sphere|![Chapter4](Img/Chapter4.png)||
|Chapter5-1 Surface normals|![](Img/Chapter5.png)||
|Chapter5-2 multiple objects|![](Img/Chapter5-2.png)||
|Chapter6 Antialiasing| ![](Img/Chapter6.png)||
|Chapter7-Diffuse material|![](Img/Chapter7-diffuse.png)||
|Chapter7-Diffuse & Gamma|![](Img/Chapter7-diffuse&gamma.png)||
|Chapter8 Metal|![](Img/Chapter8.png)||
|Chapter8 Metal Fuzz|![](Img/Chapter8-Fuzz.png)||
|Chapter9 Dielectrics|![](Img/Chapter9.png)||
|Chapter10 Positionable camera|![](Img/Chapter10.png)||
|Chapter11 Defocus Blur|![](Img/Chapter11.png)||
|Chapter12 RandomScene|![](Img/Chapter12.png)||
|Chapter12 RandomScene|![](Img/OutputPic.jpg)||


## 2. Ray Tracing The Next Week Practice Proj


### Step Pic

|Chapter|Pic|Descript|
|-|-|-|
|Chapter1 Motion Blur|||
|Chapter2 BVH|![](Img/NextWeekChapter3TimeData.png) ![](Img/costtimecompare.png)||
|Chapter3 Solid Texture|![](Img/OutputPic1000x2000x100SppNextWeekChapter3.jpg)||
|Chapter4 PerlinNoise|![](Img/OutputPic1000x2000x100SppNextWeekChapter4.jpg)||

## 3. Ray Tracing The Rest Of Your Life

### Step Pic

|Title|Pic|Time|
|-|-|-|
|Basic path tracing 1spp|![](Img/BasicPpathTracing/CornelBox500x500x1sppResultPic.jpg)|0.089 minutes Width:500 Height:500 Samples:1|
|Basic path tracing 8spp|![](Img/BasicPpathTracing/CornelBox500x500x8sppResultPic.jpg)|0.13385 minutes Width:500 Height:500 Samples:8|
|Basic path tracing 12spp|![](Img/BasicPpathTracing/CornelBox500x500x12sppResultPic.jpg)|0.15685 minutes Width:500 Height:500 Samples:12|
|Basic path tracing 40spp|![](Img/BasicPpathTracing/CornelBox500x500x40sppResultPic.jpg)|0.46475 minutes Width:500 Height:500 Samples:40|
|Basic path tracing 200spp|![](Img/BasicPpathTracing/CornelBox500x500x200sppResultPic.jpg)|1.44405 minutes Width:500 Height:500 Samples:200|
|Basic path tracing 1000spp|![](Img/BasicPpathTracing/CornelBox500x500x1000sppResultPic.jpg)|6.68965 minutes Width:500 Height:500 Samples:1000|
|Basic path tracing 5000spp|![](Img/BasicPpathTracing/CornelBox500x500x5000sppResultPic.jpg)|32.4512 minutes Width:500 Height:500 Samples:5000|
|Basic path tracing 25000spp|![](Img/BasicPpathTracing/CornelBox500x500x25000sppResultPic.jpg)|161.271 minutes Width:500 Height:500 Samples:25000|