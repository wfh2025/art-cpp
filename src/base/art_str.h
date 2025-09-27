#ifndef _ART_STR_H_
#define _ART_STR_H_
#include <string>
#include <vector>

namespace art
{
    namespace str
    {
        std::string toLower(const std::string& str);
        std::string toUpper(const std::string& str);
        bool startsWith(const std::string& str, const std::string& prefix);
        bool endsWith(const std::string& str, const std::string& suffix);
        std::vector<std::string> strsplit(const std::string& s, const std::string& delimiter);
        std::string strtrim(const std::string& str, const std::string& trimChars);
    } // namespace str
} // namespace art
#endif