#include "Converter.h"
#include <algorithm>
#include <unordered_map>

void Converter::Convert(std::string& strToConvert, const char& duplicateReplacer, const char& singleReplacer) const
{
    if (strToConvert.empty())
        return;

    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), tolower);
    std::unordered_map<char, unsigned int> repeats;

    for (const char& letter : strToConvert) {
        if (repeats.contains(letter))
        {
            repeats[letter]++;
        }
        else
        {
            repeats.insert({ letter, 1 });
        }
    }

    for (char& letter : strToConvert) {
        const auto it = repeats.find(letter);
        if (it != repeats.end() && repeats[letter] > 1)
        {
            letter = duplicateReplacer;
        }
        else
        {
            letter = singleReplacer;
        }
    }
}
