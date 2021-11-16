//
// Created by linyanhou on 2021/11/15.
//

#ifndef ROOKIERENDERER_CONFIG_H
#define ROOKIERENDERER_CONFIG_H

#include <string>
#include <sstream>
#include "RMath.h"

class Config {
public:
    std::string Dec;
    int PicH;
    int PicW;
    int SamplesPerPixel;
    RMath::FVec3 LookFrom;
    RMath::FVec3 LookAt;
    float DistToFocus = 10.0;
    float Aperture = 0.0;
    float VFov = 40.0;

    Config(std::string _Dec, int _PicH, int _PicW, int _SamplesPerPixel, const FVec3& lookfrom, const FVec3& lookat,
           float dist_to_focus = 10.0, float aperture = 0.0, float vfov = 40.0) :
            Dec(_Dec), PicH(_PicH), PicW(_PicW), SamplesPerPixel(_SamplesPerPixel), LookFrom(lookfrom),
            LookAt(lookat),DistToFocus(dist_to_focus),Aperture(aperture),VFov(vfov){};

    std::string GetProgressTips() const {
        std::stringstream ss;
        ss << "[" << Dec << PicH << "x" << PicW << "x" << SamplesPerPixel << "spp]";
        return ss.str();
    }

    std::string GetPPmFileName() const {
        std::stringstream ss;
        ss << Dec << PicH << "x" << PicW << "x" << SamplesPerPixel << "sppResultPic.ppm";
        return ss.str();
    }

    std::string GetLogFileName() const {
        std::stringstream ss;
        ss << Dec << PicH << "x" << PicW << "x" << SamplesPerPixel << "sppLog.txt";
        return ss.str();
    }

    std::string GetWinOpenCmd() const {
        std::stringstream ss;
        ss << " start .\\" << Dec << PicH << "x" << PicW << "x" << SamplesPerPixel << "sppResultPic.ppm";
        return ss.str();
    }

    std::string GetMacOpenCmd() const {
        std::stringstream ss;
        ss << "open " << Dec << PicH << "x" << PicW << "x" << SamplesPerPixel << "sppResultPic.ppm";
        return ss.str();
    }
};


#endif //ROOKIERENDERER_CONFIG_H
