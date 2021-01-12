#include "PPMFileP3.h"
#include <fstream>
const std::string PPMFileP3::LF = "\n";

void PPMFileP3::OutputAsFile()
{
    std::ofstream outFile;
    outFile.open("1.ppm", std::ios::out | std::ios::trunc);
    outFile << myBuffer;
    outFile.close();
}