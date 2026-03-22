#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct ListPartsResult
        {
            s3::base::OptStr amzAbortDate;      // Header: x-amz-abort-date
            s3::base::OptStr amzAbortRuleId;    // Header: x-amz-abort-rule-id
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            std::string body;                   // Body: ListPartsResult XML
        };
    } // namespace model
} // namespace s3