#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

namespace s3
{
    namespace base
    {
        class OptBool
        {
        public:
            OptBool() noexcept;
            OptBool(bool val) noexcept;
            ~OptBool() noexcept;
            OptBool& operator=(bool val) noexcept;
            bool has() const noexcept;
            bool value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has; // 是否有值
            bool _val; // 实际值
        };

        class OptI32
        {
        public:
            OptI32() noexcept;
            OptI32(int32_t val) noexcept;
            ~OptI32() noexcept;
            OptI32& operator=(int32_t val) noexcept;
            bool has() const noexcept;
            int32_t value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;    // 是否有值
            int32_t _val; // 实际值
        };

        class OptI64
        {
        public:
            OptI64() noexcept;
            OptI64(int64_t val) noexcept;
            ~OptI64() noexcept;
            OptI64& operator=(int64_t val) noexcept;
            bool has() const noexcept;
            int64_t value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;    // 是否有值
            int64_t _val; // 实际值
        };

        class OptF32
        {
        public:
            OptF32() noexcept;
            OptF32(float val) noexcept;
            ~OptF32() noexcept;
            OptF32& operator=(float val) noexcept;
            bool has() const noexcept;
            float value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;  // 是否有值
            float _val; // 实际值
        };

        class OptF64
        {
        public:
            OptF64() noexcept;
            OptF64(double val) noexcept;
            ~OptF64() noexcept;
            OptF64& operator=(double val) noexcept;
            bool has() const noexcept;
            double value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;   // 是否有值
            double _val; // 实际值
        };

        class OptStr
        {
        public:
            OptStr() noexcept;
            OptStr(const char* s);
            OptStr(const std::string& val);
            OptStr(std::string&& val);
            OptStr& operator=(const std::string& val);
            OptStr& operator=(const char* s); // caution: 禁止s指向_val所持有的内存区间 [data(), data()+size())
            OptStr& operator=(std::string&& val);
            ~OptStr() noexcept;
            bool has() const noexcept;
            const std::string& value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;        // 是否有值
            std::string _val; // 实际值
        };

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

    } // namespace base
} // namespace s3