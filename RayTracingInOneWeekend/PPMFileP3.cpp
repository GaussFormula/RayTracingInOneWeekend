#include "PPMFileP3.h"
#include <fstream>
const std::string PPMFileP3::LF = "\n";

void PPMFileP3::OutputAsFile(const std::string& filename)
{
    std::ofstream outFile;
    outFile.open(filename, std::ios::out);
    outFile << myBuffer;
    outFile.close();
}