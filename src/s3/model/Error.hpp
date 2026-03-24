#pragma once
#include <string>
#include <vector>

#include "DeletedObject.hpp"
#include "RequestCharged.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct Error
        {
            std::string key;
            std::string versionId;
            std::string code;
            std::string message;
        };

    } // namespace model
} // namespace s3