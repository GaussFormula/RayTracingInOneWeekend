#pragma once
#include <vector>
void BoxFilterDenoising(const std::vector<unsigned char>& src, std::vector<unsigned char>& dst,
    int startRows, int endRows,
    int startColumns, int endColumns,
    const int& totalWidth, const int& totalHeight);