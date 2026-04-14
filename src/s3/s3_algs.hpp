#pragma once

#include <cstdint>
#include <memory>

#include "openssl/evp.h"
#include "openssl/opensslv.h"
#include "s3_base.hpp"

#ifndef LIBRESSL_VERSION_NUMBER
#error "art-s3 requires LibreSSL headers and libraries"
#endif

namespace s3
{
    namespace algs
    {
        class DigestCtx
        {
        public:
            explicit DigestCtx(const EVP_MD* md);
            ~DigestCtx();
            DigestCtx(const DigestCtx&) = delete;
            DigestCtx& operator=(const DigestCtx&) = delete;
            DigestCtx(DigestCtx&& other) noexcept;
            DigestCtx& operator=(DigestCtx&& other) noexcept;

            void update(const char* data, int64_t dataLen);
            s3::base::OptStr finalRaw();
            void reset();

        private:
            const EVP_MD* _md;
            std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> _ctx;
        };

        s3::base::OptStr md5(const char* data, int64_t dataLen);
        s3::base::OptStr crc32(const char* data, int64_t dataLen);
        s3::base::OptStr crc32c(const char* data, int64_t dataLen);
        s3::base::OptStr sha1(const char* data, int64_t dataLen);
        s3::base::OptStr sha256(const char* data, int64_t dataLen);
        s3::base::OptStr hmacSha256(const char* key, int64_t keyLen, const char* data, int64_t dataLen);
        s3::base::OptStr base64Encode(const char* data, int64_t dataLen);
        s3::base::OptStr base64Decode(const char* data, int64_t dataLen);
    } // namespace algs
} // namespace s3