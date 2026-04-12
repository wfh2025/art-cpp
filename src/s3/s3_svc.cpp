#include "s3_svc.hpp"

#include <CivetServer.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace s3
{
    namespace svc
    {
        namespace
        {
            /// 占位处理器：确认 HTTP 栈可用；后续替换为桶/对象路由。
            class StubObjectStoreHandler final : public CivetHandler
            {
              public:
                bool handleGet(CivetServer *, struct mg_connection *conn) override
                {
                    static constexpr char kBody[] = "s3 object store stub\n";
                    const auto n = static_cast<long long>(std::strlen(kBody));
                    if (mg_send_http_ok(conn, "text/plain", n) < 0)
                    {
                        return false;
                    }
                    mg_write(conn, kBody, static_cast<size_t>(n));
                    return true;
                }
            };
        } // namespace

        struct ObjectStoreSvc::Impl
        {
            StubObjectStoreHandler handler_{};
            std::unique_ptr<CivetServer> server_{};

            explicit Impl(const ObjectStoreSvcConfig &cfg)
            {
                std::vector<std::string> options = {"listening_ports", cfg.listening_ports,
                                                    "num_threads", cfg.num_threads};
                server_ = std::make_unique<CivetServer>(options);
                server_->addHandler("/", handler_);
            }
        };

        ObjectStoreSvc::ObjectStoreSvc(const ObjectStoreSvcConfig &cfg)
            : impl_(std::make_unique<Impl>(cfg))
        {
        }

        ObjectStoreSvc::~ObjectStoreSvc() = default;

        bool ObjectStoreSvc::running() const
        {
            return impl_ && impl_->server_ && impl_->server_->getContext() != nullptr;
        }
    } // namespace svc
} // namespace s3
