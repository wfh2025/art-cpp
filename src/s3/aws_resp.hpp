#ifndef ART_AWS_RESP_HPP_INCLUDED
#define ART_AWS_RESP_HPP_INCLUDED
#include <map>
#include <string>

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
} // namespace s3
#endif