#pragma once
#include "PPMFile.h"
#include "vec3.h"
#include <string>
#include <vector>

class PPMFileP6 :public PPMFile
{
public:
    PPMFileP6(const int& width, const int& height)
        :PPMFile(width, height)
    {
        myHeadBuffer += std::string("P6")
            + LF
            + std::to_string(width)
            + std::string(" ")
            + std::to_string(height)
            + LF
            + std::to_string(255)
            + LF;
    }

    virtual ~PPMFileP6() {}

    void AddOnePixelToBuffer(const vec3& color)
    {
        for (int i = 0; i < 3; ++i)
        {
            myDataBuffer.push_back((unsigned char)color[i]);
        }
    }

    void AddPixelsToBuffer(const std::vector<char>& pixels)
    {
        myDataBuffer.insert(myDataBuffer.end(), pixels.begin(), pixels.end());
    }


    void OutputAsFile(const std::string& filename)const;
public:
    static const std::string LF;

private:
    std::string myHeadBuffer;
    std::vector<char> myDataBuffer;
};