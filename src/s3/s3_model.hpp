#pragma once

#include <map>
#include <string>
#include <vector>

#include "model/AbortMultipartUploadRequest.hpp"
#include "model/AbortMultipartUploadResult.hpp"
#include "model/CompleteMultipartUploadRequest.hpp"
#include "model/CompleteMultipartUploadResult.hpp"
#include "model/CreateMultipartUploadRequest.hpp"
#include "model/CreateMultipartUploadResult.hpp"
#include "model/DeleteObjectRequest.hpp"
#include "model/DeleteObjectResult.hpp"
#include "model/DeleteObjectTaggingRequest.hpp"
#include "model/DeleteObjectTaggingResult.hpp"
#include "model/DeleteObjectsRequest.hpp"
#include "model/DeleteObjectsResult.hpp"
#include "model/GetObjectRequest.hpp"
#include "model/GetObjectResult.hpp"
#include "model/GetObjectTaggingRequest.hpp"
#include "model/GetObjectTaggingResult.hpp"
#include "model/HeadObjectRequest.hpp"
#include "model/HeadObjectResult.hpp"
#include "model/ListObjectVersionsRequest.hpp"
#include "model/ListObjectVersionsResult.hpp"
#include "model/ListObjectsRequest.hpp"
#include "model/ListObjectsResult.hpp"
#include "model/ListObjectsV2Request.hpp"
#include "model/ListObjectsV2Result.hpp"
#include "model/ListPartsRequest.hpp"
#include "model/ListPartsResult.hpp"
#include "model/ObjectVersion.hpp"
#include "model/PutObjectRequest.hpp"
#include "model/PutObjectResult.hpp"
#include "model/PutObjectTaggingRequest.hpp"
#include "model/PutObjectTaggingResult.hpp"
#include "model/StorageClass.hpp"
#include "model/UploadPartRequest.hpp"
#include "model/UploadPartResult.hpp"
#include "s3_base.hpp"

namespace s3
{
    namespace model
    {
        const char* storageClassToString(const StorageClass storageClass);
        StorageClass stringToStorageClass(const std::string& str);
        const char* checksumTypeToString(const ChecksumType checksumType);
        ChecksumType stringToChecksumType(const std::string& str);
        const char* requestPayerToString(const RequestPayer requestPayer);
        RequestPayer stringToRequestPayer(const std::string& str);
    } // namespace model
} // namespace s3