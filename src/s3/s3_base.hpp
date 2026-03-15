#pragma once

#include <cstdint>
#include <string>

namespace s3
{
    namespace base
    {
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
            bool _has;   // 是否有值
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
            bool _has;    // 是否有值
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
    } // namespace base
} // namespace s3