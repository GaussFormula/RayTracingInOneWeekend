#pragma once
#include <string>
#include <iostream>

class PPMFile
{
public:
    PPMFile(const int&width,const int&height)
        :myWidth(width)
        ,myHeight(height)
    {}

    PPMFile(const PPMFile& rhs);

    PPMFile& operator=(const PPMFile& rhs);


    virtual ~PPMFile() = 0
    {

    }
    
private:
    int myWidth = 0;
    int myHeight = 0;
};