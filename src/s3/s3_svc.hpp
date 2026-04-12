#pragma once

#include <memory>
#include <string>

namespace s3
{
    namespace svc
    {
        /// 占位配置，后续可扩展为端口、线程数、文档根路径等。
        struct ObjectStoreSvcConfig
        {
            std::string listening_ports = "127.0.0.1:19080";
            std::string num_threads = "4";
        };

        /// 基于 CivetWeb 的 S3 兼容 HTTP 服务骨架；具体路由与存储逻辑后续填充。
        class ObjectStoreSvc
        {
          public:
            explicit ObjectStoreSvc(const ObjectStoreSvcConfig &cfg = {});
            ~ObjectStoreSvc();

            ObjectStoreSvc(const ObjectStoreSvc &) = delete;
            ObjectStoreSvc &operator=(const ObjectStoreSvc &) = delete;

            bool running() const;

          private:
            struct Impl;
            std::unique_ptr<Impl> impl_;
        };
    } // namespace svc
} // namespace s3
