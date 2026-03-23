#pragma once
#include <string>

#include "ChecksumType.hpp"
#include "CompletedMultipartUpload.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct CompleteMultipartUploadRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptStr uploadId;                // Query String: uploadId
            s3::base::OptStr checksumCrc32;           // Header: x-amz-checksum-crc32
            s3::base::OptStr checksumCrc32c;          // Header: x-amz-checksum-crc32c
            s3::base::OptStr checksumCrc64nvme;       // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr checksumSha1;            // Header: x-amz-checksum-sha1
            s3::base::OptStr checksumSha256;          // Header: x-amz-checksum-sha256
            s3::model::ChecksumType checksumType;     // Header: x-amz-checksum-type
            s3::base::OptStr mpObjectSize;            // Header: x-amz-mp-object-size
            s3::model::RequestPayer requestPayer;     // Header: x-amz-request-payer
            s3::base::OptStr expectedBucketOwner;     // Header: x-amz-expected-bucket-owner
            s3::base::OptStr ifMatch;                 // Header: If-Match
            s3::base::OptStr ifNoneMatch;             // Header: If-None-Match
            s3::base::OptStr sSECustomerAlgorithm;    // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr sSECustomerKey;          // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr sSECustomerKeyMD5;       // Header: x-amz-server-side-encryption-customer-key-MD5
            CompletedMultipartUpload multipartUpload; // Body
        };

    } // namespace model
} // namespace s3