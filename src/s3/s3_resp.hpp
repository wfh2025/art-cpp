#ifndef ART_S3_S3_RESP_HPP_INCLUDED
#define ART_S3_S3_RESP_HPP_INCLUDED
#include <map>
#include <string>

#include "s3_def.hpp"
namespace s3
{
    class RestfulErrorResponseBodyBuilder
    {
    public:
        RestfulErrorResponseBodyBuilder() = default;
        void kv(const std::string& key, const std::string& value);
        void kvMap(const std::map<std::string, std::string>& m);
        std::string toXml();

    public:
        static RestfulErrorResponseBodyBuilder create();

    private:
        std::map<std::string, std::string> m_errMap;
    };

    class HttpMsgBuilder
    {
    public:
        HttpMsgBuilder() = default;
        std::string str()
        {
            return "";
        }

    private:
        HttpCode m_httpCode;
    };
    std::string buildListObjectsResultToXml(const ListObjectsResult& output);
} // namespace s3
#endif