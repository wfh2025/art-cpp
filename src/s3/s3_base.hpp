#pragma once

#include <cstdint>
#include <string>
namespace s3
{
    namespace base
    {
        class OptInt64
        {
        public:
            OptInt64();
            OptInt64(int64_t val);
            ~OptInt64();

            OptInt64& operator=(int64_t val);
            bool has() const;
            int64_t value() const;
            void reset();

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
            const std::string& value() const;
            void reset() noexcept;

        private:
            bool _has;        // 是否有值
            std::string _val; // 实际值
        };
    } // namespace base
} // namespace s3