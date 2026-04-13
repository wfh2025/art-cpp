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
            class StubObjectStoreHandler final : public CivetHandler
            {
            public:
                bool handleGet(CivetServer*, struct mg_connection* conn) override
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

            explicit Impl(const ObjectStoreSvcConfig& cfg)
            {
                std::vector<std::string> options = {
                    "listening_ports",
                    cfg.listening_ports,
                    "num_threads",
                    cfg.num_threads,
                    "run_as_user",
                    "",
                    "tcp_nodelay",
                    "0",
                    "max_request_size",
                    "16384",
                    "linger_timeout_ms",
                    "",
                    "connection_queue",
                    "20",
                    "listen_backlog",
                    "200",
#if defined(__linux__)
                    "allow_sendfile_call",
                    "yes",
#endif
                    "throttle",
                    "",
                    "enable_keep_alive",
                    "no",
                    "request_timeout_ms",
                    "30000",
                    "keep_alive_timeout_ms",
                    "500",
                    "decode_url",
                    "yes",
                    "decode_query_string",
                    "no",
                    "document_root",
                    "",
                    "access_log_file",
                    "",
                    "error_log_file",
                    "",
                    "cgi_pattern",
                    "**.cgi$|**.pl$|**.php$",
                    "cgi_environment",
                    "",
                    "cgi_interpreter",
                    "",
                    "cgi_interpreter_args",
                    "",
                    "cgi2_buffering",
                    "yes",
                    "put_delete_auth_file",
                    "",
                    "protect_uri",
                    "",
                    "authentication_domain",
                    "mydomain.com",
                    "enable_auth_domain_check",
                    "yes",
                    "ssi_pattern",
                    "**.shtml$|**.shtm$",
                    "enable_directory_listing",
                    "yes",
                    "enable_webdav",
                    "no",
                    "global_auth_file",
                    "",
                    "index_files",
                    "index.xhtml,index.html,index.htm,index.cgi,index.shtml,index.php",
                    "access_control_list",
                    "",
                    "extra_mime_types",
                    "",
                    "ssl_certificate",
                    "",
                    "ssl_certificate_chain",
                    "",
                    "url_rewrite_patterns",
                    "",
                    "hide_files_patterns",
                    "",
                    "ssl_verify_peer",
                    "no",
                    "ssl_cache_timeout",
                    "-1",
                    "ssl_ca_path",
                    "",
                    "ssl_ca_file",
                    "",
                    "ssl_verify_depth",
                    "9",
                    "ssl_default_verify_paths",
                    "yes",
                    "ssl_cipher_list",
                    "",
                    "ssl_protocol_version",
                    "4",
                    "ssl_short_trust",
                    "no",
                    "access_control_allow_origin",
                    "*",
                    "access_control_allow_methods",
                    "*",
                    "access_control_allow_headers",
                    "*",
                    "error_pages",
                    "*",
                    "additional_header",
                    "*",
                    "allow_index_script_resource",
                    "no",
                };
                server_ = std::make_unique<CivetServer>(options);
                server_->addHandler("/", handler_);
            }
        };

        ObjectStoreSvc::ObjectStoreSvc(const ObjectStoreSvcConfig& cfg) : impl_(std::make_unique<Impl>(cfg)) {}

        ObjectStoreSvc::~ObjectStoreSvc() = default;

        bool ObjectStoreSvc::running() const
        {
            return impl_ && impl_->server_ && impl_->server_->getContext() != nullptr;
        }
    } // namespace svc
} // namespace s3
