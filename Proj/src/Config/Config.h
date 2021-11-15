//
// Created by linyanhou on 2021/11/15.
//

#ifndef ROOKIERENDERER_CONFIG_H
#define ROOKIERENDERER_CONFIG_H

#include <string>
#include <sstream>

class Config {
public:
    std::string Dec;
    int PicH;
    int PicW;
    int SamplesPerPixel;

    Config(std::string _Dec, int _PicH, int _PicW, int _SamplesPerPixel) :
            Dec(_Dec), PicH(_PicH), PicW(_PicW), SamplesPerPixel(_SamplesPerPixel) {};

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
