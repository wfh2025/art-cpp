#pragma once

#include <memory>
#include <string>

namespace s3
{
    namespace svc
    {
        struct ObjectStoreSvcConfig
        {
            std::string listening_ports = "127.0.0.1:19080";
            std::string num_threads = "4";
        };

        class ObjectStoreSvc
        {
        public:
            explicit ObjectStoreSvc(const ObjectStoreSvcConfig& cfg = {});
            ~ObjectStoreSvc();

            ObjectStoreSvc(const ObjectStoreSvc&) = delete;
            ObjectStoreSvc& operator=(const ObjectStoreSvc&) = delete;

            bool running() const;

        private:
            struct Impl;
            std::unique_ptr<Impl> impl_;
        };
    } // namespace svc
} // namespace s3
