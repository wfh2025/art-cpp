#include "s3_utils.hpp"

#include <iomanip>
#include <sstream>

namespace
{
    bool looksLikeIpv4Format(const std::string& s)
    {
        int parts = 0;
        size_t i = 0;
        while (i < s.size())
        {
            if (!(s[i] >= '0' && s[i] <= '9'))
            {
                return false;
            }
            size_t j = i;
            while (j < s.size() && s[j] >= '0' && s[j] <= '9')
            {
                ++j;
            }
            ++parts;
            if (parts > 4)
            {
                return false;
            }
            if (j == s.size())
            {
                i = j;
                break;
            }
            if (s[j] != '.')
            {
                return false;
            }
            i = j + 1;
            if (i == s.size())
            {
                return false;
            }
        }
        return parts == 4;
    }

    bool isValidUtf8(const std::string& s)
    {
        for (size_t i = 0; i < s.size();)
        {
            unsigned char c = static_cast<unsigned char>(s[i]);
            if (c <= 0x7F)
            {
                ++i;
                continue;
            }

            if (c >= 0xC2 && c <= 0xDF)
            {
                if (i + 1 >= s.size())
                {
                    return false;
                }
                unsigned char c1 = static_cast<unsigned char>(s[i + 1]);
                if ((c1 & 0xC0) != 0x80)
                {
                    return false;
                }
                i += 2;
                continue;
            }

            if (c >= 0xE0 && c <= 0xEF)
            {
                if (i + 2 >= s.size())
                {
                    return false;
                }
                unsigned char c1 = static_cast<unsigned char>(s[i + 1]);
                unsigned char c2 = static_cast<unsigned char>(s[i + 2]);
                if ((c1 & 0xC0) != 0x80 || (c2 & 0xC0) != 0x80)
                {
                    return false;
                }
                // Reject overlong and UTF-16 surrogate range.
                if ((c == 0xE0 && c1 < 0xA0) || (c == 0xED && c1 >= 0xA0))
                {
                    return false;
                }
                i += 3;
                continue;
            }

            if (c >= 0xF0 && c <= 0xF4)
            {
                if (i + 3 >= s.size())
                {
                    return false;
                }
                unsigned char c1 = static_cast<unsigned char>(s[i + 1]);
                unsigned char c2 = static_cast<unsigned char>(s[i + 2]);
                unsigned char c3 = static_cast<unsigned char>(s[i + 3]);
                if ((c1 & 0xC0) != 0x80 || (c2 & 0xC0) != 0x80 || (c3 & 0xC0) != 0x80)
                {
                    return false;
                }
                // Reject overlong and > U+10FFFF.
                if ((c == 0xF0 && c1 < 0x90) || (c == 0xF4 && c1 > 0x8F))
                {
                    return false;
                }
                i += 4;
                continue;
            }

            return false;
        }
        return true;
    }

    bool hasValidRelativePathSegments(const std::string& objectKey)
    {
        // AWS rule: while parsing left-to-right, cumulative ".." count must
        // never exceed number of non-relative segments.
        int depth = 0;
        size_t start = 0;
        while (start <= objectKey.size())
        {
            size_t slash = objectKey.find('/', start);
            size_t end = (slash == std::string::npos) ? objectKey.size() : slash;
            std::string segment = objectKey.substr(start, end - start);

            if (segment == "..")
            {
                --depth;
                if (depth < 0)
                {
                    return false;
                }
            }
            else if (!segment.empty() && segment != ".")
            {
                ++depth;
            }

            if (slash == std::string::npos)
            {
                break;
            }
            start = slash + 1;
        }
        return true;
    }
} // namespace

namespace s3
{
    namespace utils
    {
        bool isNullOrEmpty(const char* s)
        {
            return s == nullptr || s[0] == '\0';
        }

        s3::base::OptI64 parseInt64(const std::string& str)
        {
            s3::base::OptI64 optVal;
            int64_t tmp = 0;
            std::size_t pos = 0;
            try
            {
                tmp = std::stoll(str, &pos, 10);
            }
            catch (...)
            {
                return optVal;
            }

            if (pos != str.size())
            {
                return optVal;
            }
            optVal = tmp;
            return optVal;
        }

        s3::err::S3ErrorCode validateBucketName(const std::string& bucketName)
        {
            // Length: 3..63
            if (bucketName.size() < 3 || bucketName.size() > 63)
            {
                return s3::err::S3ErrorCode::InvalidBucketName;
            }

            // Allowed chars: lowercase letters, digits, '.', '-'
            for (size_t i = 0; i < bucketName.size(); ++i)
            {
                char c = bucketName[i];
                if (!(StringUtils::IsAlnum(c) || c == '.' || c == '-'))
                {
                    return s3::err::S3ErrorCode::InvalidBucketName;
                }
            }

            // Must begin and end with letter or number
            if (!StringUtils::IsAlnum(bucketName.front()) || !StringUtils::IsAlnum(bucketName.back()))
            {
                return s3::err::S3ErrorCode::InvalidBucketName;
            }

            // No adjacent dots
            if (bucketName.find("..") != std::string::npos)
            {
                return s3::err::S3ErrorCode::InvalidBucketName;
            }

            // Must not be formatted as IP address
            if (looksLikeIpv4Format(bucketName))
            {
                return s3::err::S3ErrorCode::InvalidBucketName;
            }

            static const std::vector<std::string> kReservedPrefixes = {
                "xn--",
                "sthree-",
                "amzn-s3-demo-",
            };
            for (size_t i = 0; i < kReservedPrefixes.size(); ++i)
            {
                const std::string& prefix = kReservedPrefixes[i];
                if (StringUtils::StartsWith(bucketName, prefix))
                {
                    return s3::err::S3ErrorCode::InvalidBucketName;
                }
            }

            static const std::vector<std::string> kReservedSuffixes = {
                "-s3alias", "--ol-s3", ".mrap", "--x-s3", "--table-s3",
            };
            for (size_t i = 0; i < kReservedSuffixes.size(); ++i)
            {
                const std::string& suffix = kReservedSuffixes[i];
                if (StringUtils::EndsWith(bucketName, suffix))
                {
                    return s3::err::S3ErrorCode::InvalidBucketName;
                }
            }

            // "-an" suffix is not allowed for general-purpose validation.
            if (StringUtils::EndsWith(bucketName, "-an"))
            {
                return s3::err::S3ErrorCode::InvalidBucketName;
            }

            return s3::err::S3ErrorCode::Ok;
        }

        s3::err::S3ErrorCode validateObjectKey(const std::string& objectKey)
        {
            // Object key is UTF-8, max 1024 bytes.
            if (objectKey.size() > 1024)
            {
                return s3::err::S3ErrorCode::KeyTooLongError;
            }
            if (!isValidUtf8(objectKey))
            {
                return s3::err::S3ErrorCode::InvalidKey;
            }
            if (!hasValidRelativePathSegments(objectKey))
            {
                return s3::err::S3ErrorCode::InvalidKey;
            }
            return s3::err::S3ErrorCode::Ok;
        }

        void StringUtils::Replace(std::string& s, const char* search, const char* replace)
        {
            if (!search || !replace)
            {
                return;
            }

            size_t replaceLength = strlen(replace);
            size_t searchLength = strlen(search);

            for (std::size_t pos = 0;; pos += replaceLength)
            {
                pos = s.find(search, pos);
                if (pos == std::string::npos)
                    break;

                s.erase(pos, searchLength);
                s.insert(pos, replace);
            }
        }

        std::string StringUtils::ToLower(const char* source)
        {
            std::string copy;
            size_t sourceLength = strlen(source);
            copy.resize(sourceLength);
            // appease the latest whims of the VC++ 2017 gods
            std::transform(source, source + sourceLength, copy.begin(), [](unsigned char c) { return (char)::tolower(c); });

            return copy;
        }

        std::string StringUtils::ToUpper(const char* source)
        {
            std::string copy;
            size_t sourceLength = strlen(source);
            copy.resize(sourceLength);
            // appease the latest whims of the VC++ 2017 gods
            std::transform(source, source + sourceLength, copy.begin(), [](unsigned char c) { return (char)::toupper(c); });

            return copy;
        }

        bool StringUtils::CaselessCompare(const char* value1, const char* value2)
        {
            std::string value1Lower = ToLower(value1);
            std::string value2Lower = ToLower(value2);

            return value1Lower == value2Lower;
        }

        bool StringUtils::StartsWith(const std::string& text, const std::string& prefix)
        {
            if (prefix.empty())
            {
                return true;
            }
            if (text.size() < prefix.size())
            {
                return false;
            }
            return text.compare(0, prefix.size(), prefix) == 0;
        }

        bool StringUtils::EndsWith(const std::string& text, const std::string& suffix)
        {
            if (suffix.empty())
            {
                return true;
            }
            if (text.size() < suffix.size())
            {
                return false;
            }
            return text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
        }

        std::vector<std::string> StringUtils::Split(const std::string& toSplit, char splitOn)
        {
            return Split(toSplit, splitOn, SIZE_MAX, SplitOptions::NOT_SET);
        }

        std::vector<std::string> StringUtils::Split(const std::string& toSplit, char splitOn, SplitOptions option)
        {
            return Split(toSplit, splitOn, SIZE_MAX, option);
        }

        std::vector<std::string> StringUtils::Split(const std::string& toSplit, char splitOn, size_t numOfTargetParts)
        {
            return Split(toSplit, splitOn, numOfTargetParts, SplitOptions::NOT_SET);
        }

        std::vector<std::string> StringUtils::Split(const std::string& toSplit, char splitOn, size_t numOfTargetParts, SplitOptions option)
        {
            if (option == SplitOptions::INCLUDE_EMPTY_SEGMENTS)
            {
                return StringUtils::SplitWithSpaces(toSplit, splitOn);
            }

            std::vector<std::string> returnValues;
            std::stringstream input(toSplit);
            std::string item;

            while (returnValues.size() < numOfTargetParts - 1 && std::getline(input, item, splitOn))
            {
                if (!item.empty() || option == SplitOptions::INCLUDE_EMPTY_ENTRIES)
                {
                    returnValues.emplace_back(std::move(item));
                }
            }

            if (std::getline(input, item, static_cast<char>(EOF)))
            {
                if (option != SplitOptions::INCLUDE_EMPTY_ENTRIES)
                {
                    // Trim all leading delimiters.
                    item.erase(item.begin(), std::find_if(item.begin(), item.end(), [splitOn](int ch) { return ch != splitOn; }));
                    if (!item.empty())
                    {
                        returnValues.emplace_back(std::move(item));
                    }
                }
                else
                {
                    returnValues.emplace_back(std::move(item));
                }
            }
            // To handle the case when there are trailing delimiters.
            else if (!toSplit.empty() && toSplit.back() == splitOn && option == SplitOptions::INCLUDE_EMPTY_ENTRIES)
            {
                returnValues.emplace_back();
            }

            return returnValues;
        }

        std::vector<std::string> StringUtils::SplitWithSpaces(const std::string& toSplit, char splitOn)
        {
            size_t pos = 0;
            std::string split{toSplit};
            std::vector<std::string> returnValues;
            while ((pos = split.find(splitOn)) != std::string::npos)
            {
                returnValues.emplace_back(split.substr(0, pos));
                split.erase(0, pos + 1);
            }
            if (!split.empty())
            {
                returnValues.emplace_back(split);
            }
            return returnValues;
        }

        std::vector<std::string> StringUtils::SplitOnLine(const std::string& toSplit)
        {
            std::stringstream input(toSplit);
            std::vector<std::string> returnValues;
            std::string item;

            while (std::getline(input, item))
            {
                if (item.size() > 0)
                {
                    returnValues.push_back(item);
                }
            }

            return returnValues;
        }

        std::string StringUtils::URLEncode(const char* unsafe)
        {
            std::stringstream escaped;
            escaped.fill('0');
            escaped << std::hex << std::uppercase;

            size_t unsafeLength = strlen(unsafe);
            for (auto i = unsafe, n = unsafe + unsafeLength; i != n; ++i)
            {
                char c = *i;
                if (IsAlnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
                {
                    escaped << (char)c;
                }
                else
                {
                    // this unsigned char cast allows us to handle unicode characters.
                    escaped << '%' << std::setw(2) << int((unsigned char)c) << std::setw(0);
                }
            }

            return escaped.str();
        }

        std::string StringUtils::UTF8Escape(const char* unicodeString, const char* delimiter)
        {
            std::stringstream escaped;
            escaped.fill('0');
            escaped << std::hex << std::uppercase;

            size_t unsafeLength = strlen(unicodeString);
            for (auto i = unicodeString, n = unicodeString + unsafeLength; i != n; ++i)
            {
                int c = *i;
                if (c >= ' ' && c < 127)
                {
                    escaped << (char)c;
                }
                else
                {
                    // this unsigned char cast allows us to handle unicode characters.
                    escaped << delimiter << std::setw(2) << int((unsigned char)c) << std::setw(0);
                }
            }

            return escaped.str();
        }

        std::string StringUtils::URLEncode(double unsafe)
        {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%g", unsafe);

            return StringUtils::URLEncode(buffer);
        }

        std::string StringUtils::URLDecode(const char* safe)
        {
            std::string unescaped;

            for (; *safe; safe++)
            {
                switch (*safe)
                {
                case '%': {
                    int hex = 0;
                    auto ch = *++safe;
                    if (ch >= '0' && ch <= '9')
                    {
                        hex = (ch - '0') * 16;
                    }
                    else if (ch >= 'A' && ch <= 'F')
                    {
                        hex = (ch - 'A' + 10) * 16;
                    }
                    else if (ch >= 'a' && ch <= 'f')
                    {
                        hex = (ch - 'a' + 10) * 16;
                    }
                    else
                    {
                        unescaped.push_back('%');
                        if (ch == 0)
                        {
                            return unescaped;
                        }
                        unescaped.push_back(ch);
                        break;
                    }

                    ch = *++safe;
                    if (ch >= '0' && ch <= '9')
                    {
                        hex += (ch - '0');
                    }
                    else if (ch >= 'A' && ch <= 'F')
                    {
                        hex += (ch - 'A' + 10);
                    }
                    else if (ch >= 'a' && ch <= 'f')
                    {
                        hex += (ch - 'a' + 10);
                    }
                    else
                    {
                        unescaped.push_back('%');
                        unescaped.push_back(*(safe - 1));
                        if (ch == 0)
                        {
                            return unescaped;
                        }
                        unescaped.push_back(ch);
                        break;
                    }

                    unescaped.push_back(char(hex));
                    break;
                }
                case '+':
                    unescaped.push_back(' ');
                    break;
                default:
                    unescaped.push_back(*safe);
                    break;
                }
            }

            return unescaped;
        }

        static bool IsSpace(int ch)
        {
            if (ch < -1 || ch > 255)
            {
                return false;
            }

            return ::isspace(ch) != 0;
        }

        std::string StringUtils::LTrim(const char* source)
        {
            std::string copy(source);
            copy.erase(copy.begin(), std::find_if(copy.begin(), copy.end(), [](int ch) { return !IsSpace(ch); }));
            return copy;
        }

        // trim from end
        std::string StringUtils::RTrim(const char* source)
        {
            std::string copy(source);
            copy.erase(std::find_if(copy.rbegin(), copy.rend(), [](int ch) { return !IsSpace(ch); }).base(), copy.end());
            return copy;
        }

        // trim from both ends
        std::string StringUtils::Trim(const char* source)
        {
            return LTrim(RTrim(source).c_str());
        }

        long long StringUtils::ConvertToInt64(const char* source)
        {
            if (!source)
            {
                return 0;
            }

            return std::atoll(source);
        }

        long StringUtils::ConvertToInt32(const char* source)
        {
            if (!source)
            {
                return 0;
            }

            return std::atol(source);
        }

        bool StringUtils::ConvertToBool(const char* source)
        {
            if (!source)
            {
                return false;
            }

            std::string strValue = ToLower(source);
            if (strValue == "true" || strValue == "1")
            {
                return true;
            }

            return false;
        }

        double StringUtils::ConvertToDouble(const char* source)
        {
            if (!source)
            {
                return 0.0;
            }

            return std::strtod(source, NULL);
        }
    } // namespace utils
} // namespace s3