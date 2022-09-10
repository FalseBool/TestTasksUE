#pragma once

#include <string>

class Converter
{
public:
    void Convert(std::string& strToConvert, const char& duplicatsRplacer = ')', const char& singleRplacer = '(') const;
};
