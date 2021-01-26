#include "PPMFileP6.h"
#include <fstream>
const std::string PPMFileP6::LF = "\n";

void PPMFileP6::OutputAsFile(const std::string& filename)const
{
    std::ofstream outFile;
    outFile.open(filename, std::ios::out | std::ios::binary);
    outFile.write(myHeadBuffer.c_str(), myHeadBuffer.size());
    outFile.write(&myDataBuffer[0], myDataBuffer.size());
    outFile.close();
}