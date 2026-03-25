#pragma once
#include <string>

#include "AbortMultipartUploadRequest.hpp"
#include "AbortMultipartUploadResult.hpp"
#include "ArchiveStatus.hpp"
#include "ChecksumAlgorithm.hpp"
#include "ChecksumMode.hpp"
#include "ChecksumType.hpp"
#include "CommonPrefix.hpp"
#include "CompleteMultipartUploadRequest.hpp"
#include "CompleteMultipartUploadResult.hpp"
#include "CompletedMultipartUpload.hpp"
#include "CompletedPart.hpp"
#include "CreateMultipartUploadRequest.hpp"
#include "CreateMultipartUploadResult.hpp"
#include "Delete.hpp"
#include "DeleteMarkerEntry.hpp"
#include "DeleteObjectRequest.hpp"
#include "DeleteObjectResult.hpp"
#include "DeleteObjectTaggingRequest.hpp"
#include "DeleteObjectTaggingResult.hpp"
#include "DeleteObjectsRequest.hpp"
#include "DeleteObjectsResult.hpp"
#include "DeletedObject.hpp"
#include "EncodingType.hpp"
#include "Error.hpp"
#include "GetObjectRequest.hpp"
#include "GetObjectResult.hpp"
#include "GetObjectTaggingRequest.hpp"
#include "GetObjectTaggingResult.hpp"
#include "HeadObjectRequest.hpp"
#include "HeadObjectResult.hpp"
#include "Initiator.hpp"
#include "ListMultipartUploadsRequest.hpp"
#include "ListMultipartUploadsResult.hpp"
#include "ListObjectVersionsRequest.hpp"
#include "ListObjectVersionsResult.hpp"
#include "ListObjectsRequest.hpp"
#include "ListObjectsResult.hpp"
#include "ListObjectsV2Request.hpp"
#include "ListObjectsV2Result.hpp"
#include "ListPartsRequest.hpp"
#include "ListPartsResult.hpp"
#include "MultipartUpload.hpp"
#include "Object.hpp"
#include "ObjectCannedACL.hpp"
#include "ObjectIdentifier.hpp"
#include "ObjectLockLegalHoldStatus.hpp"
#include "ObjectLockMode.hpp"
#include "ObjectVersion.hpp"
#include "OptionalObjectAttributes.hpp"
#include "Owner.hpp"
#include "Part.hpp"
#include "PutObjectRequest.hpp"
#include "PutObjectResult.hpp"
#include "PutObjectTaggingRequest.hpp"
#include "PutObjectTaggingResult.hpp"
#include "ReplicationStatus.hpp"
#include "RequestCharged.hpp"
#include "RequestPayer.hpp"
#include "ServerSideEncryption.hpp"
#include "StorageClass.hpp"
#include "Tag.hpp"
#include "Tagging.hpp"
#include "UploadPartRequest.hpp"
#include "UploadPartResult.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ListObjectsResult
        {
            RequestCharged requestCharged; // Header: x-amz-request-charged
            s3::base::OptBool isTruncated; // Body: isTruncated
            s3::base::OptStr marker;       // Body: isTruncated
            s3::base::OptStr nextMarker;   // Body: nextMarker
            std::vector<Object> contents;  // Body: contents
            s3::base::OptStr name;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptI64 maxKeys;
            std::vector<CommonPrefix> commonPrefixes;
            EncodingType encodingType;
            std::string requestId;
        };
    } // namespace model
} // namespace s3