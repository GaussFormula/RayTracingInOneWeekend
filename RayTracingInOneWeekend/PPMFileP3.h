#pragma once
#include "PPMFile.h"
#include "vec3.h"
#include <string>

class PPMFileP3 :public PPMFile
{
public:
    PPMFileP3(const int&width,const int& height)
        :PPMFile(width,height)
    {
        myBuffer += std::string("P3")
            + LF
            + std::to_string(width)
            + std::string(" ")
            + std::to_string(height)
            + LF
            + std::to_string(255)
            + LF;
    }

    virtual ~PPMFileP3(){}

    void AddOnePixelToBuffer(const vec3& color)
    {
        std::string colorStr;
        for (int i = 0; i < 3; ++i)
        {
            colorStr += std::to_string((int)color[i]) + std::string(" ");
        }
        myBuffer += colorStr;
    }

    void AddPixelsToBuffer(const std::string& pixels)
    {
        myBuffer += pixels;
    }

    void AddLFToBuffer()
    {
        myBuffer += LF;
    }

    void OutputAsFile(const std::string& filename);

public:
    static const std::string LF;

private:
    std::string myBuffer;
};