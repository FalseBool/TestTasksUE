// NOTE. C++ 20 standard is used.

#include <iostream>
#include "Converter.h"
#include <string>

int main()
{
    Converter* converter = new Converter();

    std::string str;

    std::cout << "Press Ctrl+C to exit \n";

    while (true)
    {
        std::cout << "Enter string: \n";
        std::getline(std::cin, str);

        if (str.empty()) 
        {
            std::cout << "String is empty!\n\n";
            continue;
        }

        std::cout << str << " => ";
        converter->Convert(str);
        std::cout << str << " \n\n";
    }
}
