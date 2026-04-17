#include "s3_algs.hpp"

#include <memory>
#include <string>

#include "openssl/evp.h"
#include "openssl/hmac.h"
#include "openssl/md5.h"
#include "spdlog/spdlog.h"

namespace
{
    const EVP_MD* kCrc32Digest = EVP_get_digestbyname("CRC32");
    const EVP_MD* kCrc32cDigest = EVP_get_digestbyname("CRC32C");

    s3::base::OptStr digestOneShot(const EVP_MD* md, const char* data, int64_t dataLen)
    {
        s3::algs::DigestCtx ctx(md);
        ctx.update(data, dataLen);
        return ctx.finalRaw();
    }
} // namespace

namespace s3
{
    namespace algs
    {
        DigestCtx::DigestCtx(const EVP_MD* md) : _md(md), _ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free)
        {
            EVP_DigestInit_ex(_ctx.get(), _md, nullptr);
        }

        DigestCtx::~DigestCtx() = default;

        DigestCtx::DigestCtx(DigestCtx&& other) noexcept : _md(other._md), _ctx(std::move(other._ctx)) {}

        DigestCtx& DigestCtx::operator=(DigestCtx&& other) noexcept
        {
            _md = other._md;
            _ctx = std::move(other._ctx);
            return *this;
        }

        void DigestCtx::update(const char* data, int64_t dataLen)
        {
            EVP_DigestUpdate(_ctx.get(), data, static_cast<size_t>(dataLen));
        }

        s3::base::OptStr DigestCtx::finalRaw()
        {
            unsigned char digest[EVP_MAX_MD_SIZE] = {0};
            unsigned int digestLen = 0;
            EVP_DigestFinal_ex(_ctx.get(), digest, &digestLen);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(digest), digestLen));
        }

        void DigestCtx::reset()
        {
            EVP_MD_CTX_reset(_ctx.get());
            EVP_DigestInit_ex(_ctx.get(), _md, nullptr);
        }

        s3::base::OptStr md5(const char* data, int64_t dataLen)
        {
#ifdef S3_OPENSSL_USE_C_API
            unsigned char digest[MD5_DIGEST_LENGTH] = {0};
            MD5_CTX ctx;
            (void)MD5_Init(&ctx);
            (void)MD5_Update(&ctx, data, static_cast<size_t>(dataLen));
            (void)MD5_Final(digest, &ctx);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(digest), MD5_DIGEST_LENGTH));
#else
            unsigned int digestLen = 0;
            unsigned char digest[EVP_MAX_MD_SIZE] = {0};
            std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
            (void)EVP_DigestInit_ex(ctx.get(), EVP_md5(), nullptr);
            (void)EVP_DigestUpdate(ctx.get(), data, static_cast<size_t>(dataLen));
            (void)EVP_DigestFinal_ex(ctx.get(), digest, &digestLen);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(digest), digestLen));
#endif
        }

        s3::base::OptStr crc32(const char* data, int64_t dataLen)
        {
            unsigned int digestLen = 0;
            unsigned char digest[EVP_MAX_MD_SIZE] = {0};
            std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
            (void)EVP_DigestInit_ex(ctx.get(), kCrc32Digest, nullptr);
            (void)EVP_DigestUpdate(ctx.get(), data, static_cast<size_t>(dataLen));
            (void)EVP_DigestFinal_ex(ctx.get(), digest, &digestLen);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(digest), digestLen));
        }

        s3::base::OptStr crc32c(const char* data, int64_t dataLen)
        {
            unsigned int digestLen = 0;
            unsigned char digest[EVP_MAX_MD_SIZE] = {0};
            std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
            (void)EVP_DigestInit_ex(ctx.get(), kCrc32cDigest, nullptr);
            (void)EVP_DigestUpdate(ctx.get(), data, static_cast<size_t>(dataLen));
            (void)EVP_DigestFinal_ex(ctx.get(), digest, &digestLen);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(digest), digestLen));
        }

        s3::base::OptStr sha1(const char* data, int64_t dataLen)
        {
            unsigned int digestLen = 0;
            unsigned char digest[EVP_MAX_MD_SIZE] = {0};
            std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
            (void)EVP_DigestInit_ex(ctx.get(), EVP_sha1(), nullptr);
            (void)EVP_DigestUpdate(ctx.get(), data, static_cast<size_t>(dataLen));
            (void)EVP_DigestFinal_ex(ctx.get(), digest, &digestLen);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(digest), digestLen));
        }

        s3::base::OptStr sha256(const char* data, int64_t dataLen)
        {
            unsigned int digestLen = 0;
            unsigned char digest[EVP_MAX_MD_SIZE] = {0};
            std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
            (void)EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr);
            (void)EVP_DigestUpdate(ctx.get(), data, static_cast<size_t>(dataLen));
            (void)EVP_DigestFinal_ex(ctx.get(), digest, &digestLen);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(digest), digestLen));
        }

        s3::base::OptStr hmacSha256(const char* key, int64_t keyLen, const char* data, int64_t dataLen)
        {
            unsigned char mac[EVP_MAX_MD_SIZE] = {0};
            unsigned int macLen = 0;
            HMAC(EVP_sha256(), key, static_cast<int>(keyLen), reinterpret_cast<const unsigned char*>(data), static_cast<size_t>(dataLen), mac,
                 &macLen);
            return s3::base::OptStr(std::string(reinterpret_cast<const char*>(mac), macLen));
        }

        s3::base::OptStr base64Encode(const char* data, int64_t dataLen)
        {
            std::string out(static_cast<size_t>(4 * ((dataLen + 2) / 3) + 1), '\0');
            const int outLen =
                EVP_EncodeBlock(reinterpret_cast<unsigned char*>(&out[0]), reinterpret_cast<const unsigned char*>(data), static_cast<int>(dataLen));
            out.resize(static_cast<size_t>(outLen));
            return s3::base::OptStr(std::move(out));
        }

        s3::base::OptStr base64Decode(const char* data, int64_t dataLen)
        {
            std::string out(static_cast<size_t>((dataLen / 4) * 3 + 1), '\0');
            const int outLen =
                EVP_DecodeBlock(reinterpret_cast<unsigned char*>(&out[0]), reinterpret_cast<const unsigned char*>(data), static_cast<int>(dataLen));
            out.resize(static_cast<size_t>(outLen));
            return s3::base::OptStr(std::move(out));
        }
    } // namespace algs
} // namespace s3