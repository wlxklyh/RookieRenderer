#include <iostream>
#include <fstream>
#include "MathUtil.h"
int main()
{
    std::ofstream out;
    out.open("OutputPic.ppm");

    //（1）宽高
    int PicW = 200;
    int PicH = 200;

    // （2）这个是ppm图片格式 后面渲染的结果用这个来显示
    out << "P3\n" << PicW << " " << PicH << "\n255\n";
    for (int i = 0; i < PicW; i++)
    {
        for (int j =0; j < PicH; j++)
        {
            float r = float(i) / float(PicW);
            float g = float(j) / float(PicH);
            float b = 0.1;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}