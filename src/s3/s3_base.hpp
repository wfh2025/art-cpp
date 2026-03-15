#pragma once

#include <cstdint>
#include <string>
namespace s3
{
    namespace base
    {
        class OptInt32
        {
        public:
            OptInt32() noexcept;
            OptInt32(int32_t val) noexcept;
            ~OptInt32() noexcept;

            OptInt32& operator=(int32_t val) noexcept;
            bool has() const noexcept;
            int32_t value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;    // 是否有值
            int32_t _val; // 实际值
        };

        class OptInt64
        {
        public:
            OptInt64() noexcept;
            OptInt64(int64_t val) noexcept;
            ~OptInt64() noexcept;

            OptInt64& operator=(int64_t val) noexcept;
            bool has() const noexcept;
            int64_t value() const noexcept; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;    // 是否有值
            int64_t _val; // 实际值
        };

        class OptStr
        {
        public:
            OptStr();
            OptStr(const char* s);
            OptStr(const std::string& val);
            OptStr(std::string&& val);
            OptStr& operator=(const std::string& val);
            OptStr& operator=(const char* s);
            OptStr& operator=(std::string&& val);
            ~OptStr() noexcept;
            bool has() const noexcept;
            const std::string& value() const; // caution: 调用value()前提: has() == true
            void reset() noexcept;

        private:
            bool _has;        // 是否有值
            std::string _val; // 实际值
        };
    } // namespace base
} // namespace s3