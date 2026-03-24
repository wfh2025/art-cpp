#pragma once
#include <string>

#include "ChecksumAlgorithm.hpp"
#include "Delete.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        enum class ChecksumMode
        {
            NotSet,
            Enabled
        };

    } // namespace model
} // namespace s3