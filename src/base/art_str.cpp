#include "art_str.h"
namespace art
{
    namespace str
    {
        std::string toLower(const std::string& str)
        {
            std::string result = str;
            for (auto& c : result)
            {
                c = std::tolower(c);
            }
            return result;
        }
        std::string toUpper(const std::string& str)
        {
            std::string result = str;
            for (auto& c : result)
            {
                c = std::toupper(c);
            }
            return result;
        }

        bool startsWith(const std::string& str, const std::string& prefix)
        {
            return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
        }
        bool endsWith(const std::string& str, const std::string& suffix)
        {
            return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
        }

        std::string strtrim(const std::string& str, const std::string& trimChars)
        {
            if (trimChars.empty())
            {
                return str;
            }
            size_t start = str.find_first_not_of(trimChars);
            if (start == std::string::npos)
            {
                return "";
            }
            size_t end = str.find_last_not_of(trimChars);
            return str.substr(start, end - start + 1);
        }

        std::vector<std::string> strsplit(const std::string& s, const std::string& delimiter)
        {
            std::vector<std::string> tokens;
            if (s.empty() || delimiter.empty())
            {
                tokens.push_back(s);
                return tokens;
            }

            size_t start = 0;
            size_t end = s.find(delimiter);

            while (end != std::string::npos)
            {
                tokens.push_back(s.substr(start, end - start));
                start = end + delimiter.length();
                end = s.find(delimiter, start);
            }
            tokens.push_back(s.substr(start));
            return tokens;
        }
    } // namespace str
} // namespace art