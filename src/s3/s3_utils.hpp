#pragma once
#include <chrono>
#include <cstdint>
#include <string>

#include "s3_base.hpp"

namespace s3
{
    namespace utils
    {
        bool isNullOrEmpty(const char* s);
        s3::base::OptI64 parseInt64(const std::string& str);
        std::string timeToISO8601(const std::chrono::system_clock::time_point& time);

        enum class DateFormat
        {
            RFC822,         // for http headers
            ISO_8601,       // for query and xml payloads
            ISO_8601_BASIC, // for retry headers and signers
            AutoDetect
        };

        enum class Month
        {
            January = 0,
            February,
            March,
            April,
            May,
            June,
            July,
            August,
            September,
            October,
            November,
            December
        };

        enum class DayOfWeek
        {
            Sunday = 0,
            Monday,
            Tuesday,
            Wednesday,
            Thursday,
            Friday,
            Saturday
        };

        /**
         * Wrapper for timestamp functionality.
         */
        class DateTime
        {
        public:
            /**
             *  Initializes time point to epoch
             */
            DateTime();

            /**
             *  Initializes time point to any other arbitrary timepoint
             */
            DateTime(const std::chrono::system_clock::time_point& timepointToAssign);

            /**
             * Initializes time point to millis Since epoch
             */
            DateTime(int64_t millisSinceEpoch);

            /**
             * Initializes time point to epoch time in seconds with a millis mantissa,
             *
             * i.e. 1.1 would be 1100 milliseconds
             */
            DateTime(double secondsSinceEpoch);

            /**
             * Initializes time point to epoch time in seconds
             */
            DateTime(uint64_t secondsSinceEpoch);

            /**
             * Initializes time point to value represented by timestamp and format.
             */
            DateTime(const std::string& timestamp, DateFormat format);

            /**
             * Initializes time point to value represented by timestamp and format.
             */
            DateTime(const char* timestamp, DateFormat format);

            bool operator==(const DateTime& other) const;
            bool operator<(const DateTime& other) const;
            bool operator>(const DateTime& other) const;
            bool operator!=(const DateTime& other) const;
            bool operator<=(const DateTime& other) const;
            bool operator>=(const DateTime& other) const;

            DateTime operator+(const std::chrono::milliseconds& a) const;
            DateTime operator-(const std::chrono::milliseconds& a) const;

            /**
             * Initializes time point to epoch time in seconds with a millis mantissa,
             *
             * i.e. 1.1 would be 1100 milliseconds
             */
            DateTime& operator=(double secondsSinceEpoch);

            /**
             * Assign from millis since epoch.
             */
            DateTime& operator=(int64_t millisSinceEpoch);

            /**
             * Assign from another time_point
             */
            DateTime& operator=(const std::chrono::system_clock::time_point& timepointToAssign);

            /**
             * Assign from an ISO8601 or RFC822 formatted string
             */
            DateTime& operator=(const std::string& timestamp);

            /**
             * Whether or not parsing the timestamp from string was successful.
             */
            inline bool WasParseSuccessful() const
            {
                return m_valid;
            }

            /**
             * Convert dateTime to local time string using predefined format.
             */
            std::string ToLocalTimeString(DateFormat format) const;

            /**
             * Convert dateTime to local time string using arbitrary format.
             */
            std::string ToLocalTimeString(const char* formatStr) const;

            /**
             * Convert dateTime to GMT time string using predefined format.
             */
            std::string ToGmtString(DateFormat format) const;

            /**
             * Convert dateTime to GMT time string using arbitrary format.
             */
            std::string ToGmtString(const char* formatStr) const;

            /**
             * Convert dateTime to GMT time string using predefined format.
             */
            std::string ToGmtStringWithMs() const;

            /**
             * Get the representation of this datetime as seconds with a millis mantissa since epoch
             *
             * i.e. 1.1 would be 1100 milliseconds
             */
            double SecondsWithMSPrecision() const;

            /**
             * Get the seconds without millisecond precision.
             */
            int64_t Seconds() const;

            /**
             * Milliseconds since epoch of this datetime.
             */
            int64_t Millis() const;

            /**
             *  In the likely case this class doesn't do everything you need to do, here's a copy of the time_point structure. Have fun.
             */
            std::chrono::system_clock::time_point UnderlyingTimestamp() const;

            /**
             * Get the Year portion of this dateTime. localTime if true, return local time, otherwise return UTC
             */
            int GetYear(bool localTime = false) const;

            /**
             * Get the Month portion of this dateTime. localTime if true, return local time, otherwise return UTC
             */
            Month GetMonth(bool localTime = false) const;

            /**
             * Get the Day of the Month portion of this dateTime. localTime if true, return local time, otherwise return UTC
             */
            int GetDay(bool localTime = false) const;

            /**
             * Get the Day of the Week portion of this dateTime. localTime if true, return local time, otherwise return UTC
             */
            DayOfWeek GetDayOfWeek(bool localTime = false) const;

            /**
             * Get the Hour portion of this dateTime. localTime if true, return local time, otherwise return UTC
             */
            int GetHour(bool localTime = false) const;

            /**
             * Get the Minute portion of this dateTime. localTime if true, return local time, otherwise return UTC
             */
            int GetMinute(bool localTime = false) const;

            /**
             * Get the Second portion of this dateTime. localTime if true, return local time, otherwise return UTC
             */
            int GetSecond(bool localTime = false) const;

            /**
             * Get whether or not this dateTime is in Daylight savings time. localTime if true, return local time, otherwise return UTC
             */
            bool IsDST(bool localTime = false) const;

            /**
             * Get an instance of DateTime representing this very instant.
             */
            static DateTime Now();

            /**
             * Get the millis since epoch representing this very instant.
             */
            static int64_t CurrentTimeMillis();

            /**
             * Calculates the current local timestamp, formats it and returns it as a string
             */
            static std::string CalculateLocalTimestampAsString(const char* formatStr);

            /**
             * Calculates the current gmt timestamp, formats it, and returns it as a string
             */
            static std::string CalculateGmtTimestampAsString(const char* formatStr);

            /**
             * Calculates the current hour of the day in localtime.
             */
            static int CalculateCurrentHour();

            /**
             * The amazon timestamp format is a double with seconds.milliseconds
             */
            static double ComputeCurrentTimestampInAmazonFormat();

            /**
             * Calculates the current time in GMT with millisecond precision using the format
             * "Year-month-day hours:minutes:seconds.milliseconds"
             */
            static std::string CalculateGmtTimeWithMsPrecision();

            /**
             * Compute the difference between two timestamps.
             */
            static std::chrono::milliseconds Diff(const DateTime& a, const DateTime& b);

            std::chrono::milliseconds operator-(const DateTime& other) const;

        private:
            std::chrono::system_clock::time_point m_time;
            bool m_valid;

            void ConvertTimestampStringToTimePoint(const char* timestamp, DateFormat format);
            tm GetTimeStruct(bool localTime) const;
            tm ConvertTimestampToLocalTimeStruct() const;
            tm ConvertTimestampToGmtStruct() const;
        };

        /**
         * All the things the c++ stdlib is missing for string operations that I needed.
         */
        class StringUtils
        {
        public:
            static void Replace(std::string& s, const char* search, const char* replace);

            /**
             * Converts a string to lower case.
             */
            static std::string ToLower(const char* source);

            /**
             * Converts a string to upper case.
             */
            static std::string ToUpper(const char* source);

            /**
             * Does a caseless comparison of two strings.
             */
            static bool CaselessCompare(const char* value1, const char* value2);

            /**
             * URL encodes a string (uses %20 not + for spaces).
             */
            static std::string URLEncode(const char* unsafe);

            static inline std::string URLEncode(const std::string& unsafe)
            {
                return URLEncode(unsafe.c_str());
            }

            /**
             * Http Clients tend to escape some characters but not all. Escaping all of them causes problems, because the client
             * will also try to escape them.
             * So this only escapes non-ascii characters and the + character
             */
            static std::string UTF8Escape(const char* unicodeString, const char* delimiter);

            /**
             * URL encodes a double (if it ends up going to scientific notation) otherwise it just returns it as a string.
             */
            static std::string URLEncode(double unsafe);

            /**
             * Decodes a URL encoded string (will handle both encoding schemes for spaces).
             */
            static std::string URLDecode(const char* safe);

            enum class SplitOptions
            {
                /**
                 * By default, removes all the empty entries in the vector returned by Split()
                 */
                NOT_SET,
                /**
                 * Deprecated use INCLUDE_EMPTY_SEGMENTS instead.
                 */
                INCLUDE_EMPTY_ENTRIES,
                /**
                 * Include delimiters as empty segments in the split string
                 */
                INCLUDE_EMPTY_SEGMENTS,
            };

            /**
             * @brief Splits a string on a delimiter (empty items are excluded).
             * @param toSplit, the original string to split
             * @param splitOn, the delimiter you want to use.
             */
            static std::vector<std::string> Split(const std::string& toSplit, char splitOn);

            /**
             * @brief Splits a string on a delimiter.
             * @param toSplit, the original string to split
             * @param splitOn, the delimiter you want to use.
             * @param option, if INCLUDE_EMPTY_ENTRIES, includes empty entries in the result, otherwise removes empty entries.
             */
            static std::vector<std::string> Split(const std::string& toSplit, char splitOn, SplitOptions option);

            /**
             * @brief Splits a string on a delimiter (empty items are excluded).
             * @param toSplit, the original string to split
             * @param splitOn, the delimiter you want to use.
             * @param numOfTargetParts, how many target parts you want to get, if it is 0, as many as possible.
             */
            static std::vector<std::string> Split(const std::string& toSplit, char splitOn, size_t numOfTargetParts);

            /**
             * @brief Splits a string on a delimiter.
             * @param toSplit, the original string to split
             * @param splitOn, the delimiter you want to use.
             * @param numOfTargetParts, how many target parts you want to get, if it is 0, as many as possible.
             * @param option, if INCLUDE_EMPTY_ENTRIES, includes empty entries in the result, otherwise removes empty entries.
             */
            static std::vector<std::string> Split(const std::string& toSplit, char splitOn, size_t numOfTargetParts, SplitOptions option);

            /**
             * Splits a string on delimeter, keeping the delimiter in the string as a empty space.
             * @param toSplit, the original string to split
             * @param splitOn, the delimiter you want to use.
             */
            static std::vector<std::string> SplitWithSpaces(const std::string& toSplit, char splitOn);

            /**
             * Splits a string on new line characters.
             */
            static std::vector<std::string> SplitOnLine(const std::string& toSplit);

            /** static std::vector<std::string> SplitOnRegex(std::string regex);
             *  trim from start
             */
            static std::string LTrim(const char* source);

            /**
             * trim from end
             */
            static std::string RTrim(const char* source);

            /**
             * trim from both ends
             */
            static std::string Trim(const char* source);

            /**
             * convert to int 64
             */
            static long long ConvertToInt64(const char* source);

            /**
             * convert to int 32
             */
            static long ConvertToInt32(const char* source);

            /**
             * convert to bool
             */
            static bool ConvertToBool(const char* source);

            /**
             * convert to double
             */
            static double ConvertToDouble(const char* source);

            /**
             * not all platforms (Android) have std::to_string
             */
            template <typename T> static std::string to_string(T value)
            {
                std::ostringstream os;
                os << value;
                return os.str();
            }

            /**
             * locale agnostic implementation of std::isalnum
             */
            static bool IsAlnum(char c)
            {
                return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
            }

            /**
             * Convert an unsigned integer to its hex string in upper case.
             */
            template <typename T, class = typename std::enable_if<std::is_unsigned<T>::value>::type> static std::string ToHexString(T value)
            {
                if (value == 0)
                {
                    return "0";
                }

                std::string s;
                s.reserve(sizeof(value) * 2);
                T r = value;
                while (r > 0)
                {
                    s += "0123456789ABCDEF"[r & 0xf];
                    r >>= 4;
                }

                std::reverse(s.begin(), s.end());
                return s;
            }
        };

    } // namespace utils

} // namespace s3
