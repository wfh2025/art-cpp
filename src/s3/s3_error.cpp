#include "s3_error.hpp"

#include <unordered_map>

#include "spdlog/fmt/bundled/args.h"
#include "spdlog/spdlog.h"

namespace
{
    const std::unordered_map<s3::err::S3ErrorCode, s3::err::S3ErrorInfo> kS3ErrorInfoTable = {
        {
            s3::err::S3ErrorCode::Ok,
            {
                s3::err::S3ErrorCode::Ok,
                "",
                "",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::AccessControlListNotSupported,
            {
                s3::err::S3ErrorCode::AccessControlListNotSupported,
                "AccessControlListNotSupported",
                "The bucket does not allow ACLs.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::AccessDenied,
            {
                s3::err::S3ErrorCode::AccessDenied,
                "AccessDenied",
                "Access Denied",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::AccessPointAlreadyOwnedByYou,
            {
                s3::err::S3ErrorCode::AccessPointAlreadyOwnedByYou,
                "AccessPointAlreadyOwnedByYou",
                "An access point with an identical name already exists in your account.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::AccessDeniedStorageLens,
            {
                s3::err::S3ErrorCode::AccessDeniedStorageLens,
                "AccessDenied",
                "This Region is not supported as a home Region for S3 Storage Lens.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::AccessDeniedAccessGrants,
            {
                s3::err::S3ErrorCode::AccessDeniedAccessGrants,
                "AccessDenied",
                "You do not have {} permissions to the requested S3 Prefix: {}",
                2,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::AccountProblem,
            {
                s3::err::S3ErrorCode::AccountProblem,
                "AccountProblem",
                "There is a problem with your AWS account that prevents the operation from completing successfully. For further assistance, see "
                "[Contact Us](https://aws.amazon.com/contact-us/).",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::AllAccessDisabled,
            {
                s3::err::S3ErrorCode::AllAccessDisabled,
                "AllAccessDisabled",
                "All access to this Amazon S3 resource has been disabled. For further assistance, see https://aws.amazon.com/contact-us/",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::AmbiguousGrantByEmailAddress,
            {
                s3::err::S3ErrorCode::AmbiguousGrantByEmailAddress,
                "AmbiguousGrantByEmailAddress",
                "The email address that you provided is associated with more than one account.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::AuthorizationHeaderMalformed,
            {
                s3::err::S3ErrorCode::AuthorizationHeaderMalformed,
                "AuthorizationHeaderMalformed",
                "The authorization header that you provided is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::AuthorizationQueryParametersError,
            {
                s3::err::S3ErrorCode::AuthorizationQueryParametersError,
                "AuthorizationQueryParametersError",
                "The authorization query parameters that you provided are not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::BadDigest,
            {
                s3::err::S3ErrorCode::BadDigest,
                "BadDigest",
                "The Content-MD5 or checksum value that you specified did not match what the server received.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InternalError,
            {
                s3::err::S3ErrorCode::InternalError,
                "InternalError",
                "An internal error occurred. Try again.",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::InternalErrorSelect,
            {
                s3::err::S3ErrorCode::InternalErrorSelect,
                "InternalError",
                "An internal error occurred.",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsQuotaExceededError,
            {
                s3::err::S3ErrorCode::AccessGrantsQuotaExceededError,
                "AccessGrantsQuotaExceededError",
                "The access grants quota has been exceeded. Access Grants Quota: {}. Please reach out to S3 if an increase is required.",
                1,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::BucketAlreadyExists,
            {
                s3::err::S3ErrorCode::BucketAlreadyExists,
                "BucketAlreadyExists",
                "The requested bucket name is not available. The bucket namespace is shared by all users of the system. Specify a different name and "
                "try again.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::BucketAlreadyOwnedByYou,
            {
                s3::err::S3ErrorCode::BucketAlreadyOwnedByYou,
                "BucketAlreadyOwnedByYou",
                "The bucket that you tried to create already exists, and you own it.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::BucketHasAccessPointsAttached,
            {
                s3::err::S3ErrorCode::BucketHasAccessPointsAttached,
                "BucketHasAccessPointsAttached",
                "The bucket you tried to delete has access points attached. Delete your access points before deleting your bucket.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::BucketNotEmpty,
            {
                s3::err::S3ErrorCode::BucketNotEmpty,
                "BucketNotEmpty",
                "The bucket that you tried to delete is not empty.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::ClientTokenConflict,
            {
                s3::err::S3ErrorCode::ClientTokenConflict,
                "ClientTokenConflict",
                "Your Multi-Region Access Point idempotency token was already used for a different request.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::ConditionalRequestConflict,
            {
                s3::err::S3ErrorCode::ConditionalRequestConflict,
                "ConditionalRequestConflict",
                "A conflicting operation occurred. "
                "If using PutObject you can retry the request. "
                "If using multipart upload you should initiate "
                "another CreateMultipartUpload request and re-upload each part.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::ConnectionClosedByRequester,
            {
                s3::err::S3ErrorCode::ConnectionClosedByRequester,
                "ConnectionClosedByRequester",
                "Returned to the original caller when an error is encountered while reading the WriteGetObjectResponse body.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::CredentialsNotSupported,
            {
                s3::err::S3ErrorCode::CredentialsNotSupported,
                "CredentialsNotSupported",
                "This request does not support credentials.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::CrossLocationLoggingProhibited,
            {
                s3::err::S3ErrorCode::CrossLocationLoggingProhibited,
                "CrossLocationLoggingProhibited",
                "Cross-Region logging is not allowed. Buckets in one AWS Region cannot log information to a bucket in another Region.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::DeviceNotActiveError,
            {
                s3::err::S3ErrorCode::DeviceNotActiveError,
                "DeviceNotActiveError",
                "The device is not currently active.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EndpointNotFound,
            {
                s3::err::S3ErrorCode::EndpointNotFound,
                "EndpointNotFound",
                "Direct requests to the correct endpoint.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ExpiredToken,
            {
                s3::err::S3ErrorCode::ExpiredToken,
                "ExpiredToken",
                "The provided token has expired.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EntityTooSmall,
            {
                s3::err::S3ErrorCode::EntityTooSmall,
                "EntityTooSmall",
                "Your proposed upload is smaller than the minimum allowed object size.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EntityTooLarge,
            {
                s3::err::S3ErrorCode::EntityTooLarge,
                "EntityTooLarge",
                "Your proposed upload exceeds the maximum allowed object size. For more information, see [Amazon Simple Storage Service endpoints "
                "and quotas](https://docs.aws.amazon.com//general/latest/gr/s3.html) in the AWS General Reference.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IllegalLocationConstraintException,
            {
                s3::err::S3ErrorCode::IllegalLocationConstraintException,
                "IllegalLocationConstraintException",
                "This error might occur for the following reasons: You are trying to access a bucket from a different Region than where the bucket "
                "exists. You attempt to create a bucket with a location constraint that corresponds to a different region than the regional endpoint "
                "the request was sent to.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IllegalVersioningConfigurationException,
            {
                s3::err::S3ErrorCode::IllegalVersioningConfigurationException,
                "IllegalVersioningConfigurationException",
                "The versioning configuration specified in the request is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IncompleteBody,
            {
                s3::err::S3ErrorCode::IncompleteBody,
                "IncompleteBody",
                "You did not provide the number of bytes specified by the Content-Length HTTP header.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IncorrectEndpoint,
            {
                s3::err::S3ErrorCode::IncorrectEndpoint,
                "IncorrectEndpoint",
                "The specified bucket exists in another Region. Direct requests to the correct endpoint.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IncorrectNumberOfFilesInPostRequest,
            {
                s3::err::S3ErrorCode::IncorrectNumberOfFilesInPostRequest,
                "IncorrectNumberOfFilesInPostRequest",
                "POST requires exactly one file upload per request.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InlineDataTooLarge,
            {
                s3::err::S3ErrorCode::InlineDataTooLarge,
                "InlineDataTooLarge",
                "The inline data exceeds the maximum allowed size.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAccessKeyId,
            {
                s3::err::S3ErrorCode::InvalidAccessKeyId,
                "InvalidAccessKeyId",
                "The AWS access key ID that you provided does not exist in our records.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAccessPoint,
            {
                s3::err::S3ErrorCode::InvalidAccessPoint,
                "InvalidAccessPoint",
                "The specified access point name or account is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAccessPointAliasError,
            {
                s3::err::S3ErrorCode::InvalidAccessPointAliasError,
                "InvalidAccessPointAliasError",
                "The specified access point alias name is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAddressingHeader,
            {
                s3::err::S3ErrorCode::InvalidAddressingHeader,
                "InvalidAddressingHeader",
                "You must specify the Anonymous role.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidArgument,
            {
                s3::err::S3ErrorCode::InvalidArgument,
                "InvalidArgument",
                "This error might occur for the following reasons: A ListBuckets request is made to a Regional endpoint that is different from the "
                "Region specified in the bucket-region parameter. The specified argument was not valid. The request was missing a required header. "
                "The "
                "specified argument was incomplete or in the wrong format. The specified argument must have a length greater than or equal to 3.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidArgumentReplication,
            {
                s3::err::S3ErrorCode::InvalidArgumentReplication,
                "InvalidArgument",
                "Replication configuration is invalid. For example, required account/time values are missing or rule ID contains non-ASCII "
                "characters.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidBucketAclWithObjectOwnership,
            {
                s3::err::S3ErrorCode::InvalidBucketAclWithObjectOwnership,
                "InvalidBucketAclWithObjectOwnership",
                "Bucket cannot have ACLs set with ObjectOwnership's BucketOwnerEnforced setting.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidBucketName,
            {
                s3::err::S3ErrorCode::InvalidBucketName,
                "InvalidBucketName",
                "The specified bucket is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidBucketOwnerAWSAccountID,
            {
                s3::err::S3ErrorCode::InvalidBucketOwnerAWSAccountID,
                "InvalidBucketOwnerAWSAccountID",
                "The value of the expected bucket owner parameter must be an AWS account ID.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidBucketState,
            {
                s3::err::S3ErrorCode::InvalidBucketState,
                "InvalidBucketState",
                "The request is not valid for the current state of the bucket.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidDigest,
            {
                s3::err::S3ErrorCode::InvalidDigest,
                "InvalidDigest",
                "The Content-MD5 or checksum value that you specified is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidEncryptionAlgorithmError,
            {
                s3::err::S3ErrorCode::InvalidEncryptionAlgorithmError,
                "InvalidEncryptionAlgorithmError",
                "The encryption request that you specified is not valid. The valid value isAES256.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidHostHeader,
            {
                s3::err::S3ErrorCode::InvalidHostHeader,
                "InvalidHostHeader",
                "The host headers provided in the request used the incorrect style addressing.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidHttpMethod,
            {
                s3::err::S3ErrorCode::InvalidHttpMethod,
                "InvalidHttpMethod",
                "The request is made using an unexpected HTTP method.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidLocationConstraint,
            {
                s3::err::S3ErrorCode::InvalidLocationConstraint,
                "InvalidLocationConstraint",
                "The specified location (Region) constraint is not valid. For more information about selecting a Region for your buckets, see "
                "[Buckets overview](https://docs.aws.amazon.com/AmazonS3/latest/userguide/UsingBucket.html#access-bucket-intro).",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidObjectState,
            {
                s3::err::S3ErrorCode::InvalidObjectState,
                "InvalidObjectState",
                "The operation is not valid for the current state of the object.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidPayer,
            {
                s3::err::S3ErrorCode::InvalidPayer,
                "InvalidPayer",
                "All access to this object has been disabled. For further assistance, see [Contact Us](https://aws.amazon.com/contact-us/).",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidPart,
            {
                s3::err::S3ErrorCode::InvalidPart,
                "InvalidPart",
                "One or more of the specified parts could not be found. The part might not have been uploaded, or the specified entity tag might not "
                "have matched the part's entity tag.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidPartOrder,
            {
                s3::err::S3ErrorCode::InvalidPartOrder,
                "InvalidPartOrder",
                "The list of parts was not in ascending order. The parts list must be specified in order by part number.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidPolicyDocument,
            {
                s3::err::S3ErrorCode::InvalidPolicyDocument,
                "InvalidPolicyDocument",
                "The content of the form does not meet the conditions specified in the policy document.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRange,
            {
                s3::err::S3ErrorCode::InvalidRange,
                "InvalidRange",
                "The requested range cannot be satisfied.",
                0,
                s3::http::HttpStatusCode::RangeNotSatisfiable,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRegion,
            {
                s3::err::S3ErrorCode::InvalidRegion,
                "InvalidRegion",
                "You've attempted to create a Multi-Region Access Point in a Region that you haven't opted in to.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRequest,
            {
                s3::err::S3ErrorCode::InvalidRequest,
                "InvalidRequest",
                "This error might occur for the following reasons: An unpaginated ListBuckets request is made from an account that has an approved "
                "general "
                "purpose bucket quota higher than 10,000. You must make paginated requests to list the buckets in an account with more than 10,000 "
                "buckets. "
                "The request is using the wrong signature version. Use AWS4-HMAC-SHA256 (Signature Version 4). An access point can be created only "
                "for "
                "an "
                "existing bucket. The access point is not in a state where it can be deleted. An access point can be listed only for an existing "
                "bucket. The "
                "next token is not valid. At least one action must be specified in a lifecycle rule. At least one lifecycle rule must be specified. "
                "The "
                "number "
                "of lifecycle rules must not exceed the allowed limit of 1000 rules. The range for the MaxResults parameter is not valid. SOAP "
                "requests "
                "must be "
                "made over an HTTPS connection. Amazon S3 Transfer Acceleration is not supported for buckets with non-DNS compliant names. Amazon S3 "
                "Transfer "
                "Acceleration is not supported for buckets with periods (.) in their names. The Amazon S3 Transfer Acceleration endpoint supports "
                "only "
                "virtual "
                "style requests. Amazon S3 Transfer Acceleration is not configured on this bucket. Amazon S3 Transfer Acceleration is disabled on "
                "this "
                "bucket. "
                "Amazon S3 Transfer Acceleration is not supported on this bucket. Conflicting values provided in HTTP headers and query parameters. "
                "Conflicting "
                "values provided in HTTP headers and POST form fields. CopyObject request made on objects larger than 5GB in size.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRequestReplication,
            {
                s3::err::S3ErrorCode::InvalidRequestReplication,
                "InvalidRequest",
                "Replication request is invalid. For example, AccessControlTranslation owner/account requirements or RTC/Metrics consistency is "
                "violated.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRequestTagging,
            {
                s3::err::S3ErrorCode::InvalidRequestTagging,
                "InvalidRequest",
                "The AWS Region in the resource ARN doesn't match the Region in this request, or account/partition values are invalid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRequestOutposts,
            {
                s3::err::S3ErrorCode::InvalidRequestOutposts,
                "InvalidRequest",
                "The request is invalid for S3 on Outposts, such as missing VPC configuration or invalid access point state.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidSessionException,
            {
                s3::err::S3ErrorCode::InvalidSessionException,
                "InvalidSessionException",
                "Returned if the session doesn't exist anymore because it timed out or expired.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidSignature,
            {
                s3::err::S3ErrorCode::InvalidSignature,
                "InvalidSignature",
                "The request signature that the server calculated does not match the signature that you provided. Check your AWS secret access key "
                "and signing method. For more information, see [Signing and authenticating REST "
                "requests](https://docs.aws.amazon.com/AmazonS3/latest/userguide/RESTAuthentication.html).",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidSecurity,
            {
                s3::err::S3ErrorCode::InvalidSecurity,
                "InvalidSecurity",
                "The provided security credentials are not valid.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidSOAPRequest,
            {
                s3::err::S3ErrorCode::InvalidSOAPRequest,
                "InvalidSOAPRequest",
                "The SOAP request body is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidStorageClass,
            {
                s3::err::S3ErrorCode::InvalidStorageClass,
                "InvalidStorageClass",
                "The storage class that you specified is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTargetBucketForLogging,
            {
                s3::err::S3ErrorCode::InvalidTargetBucketForLogging,
                "InvalidTargetBucketForLogging",
                "The target bucket for logging either does not exist, is not owned by you, or does not have the appropriate grants for the "
                "log-delivery group.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidToken,
            {
                s3::err::S3ErrorCode::InvalidToken,
                "InvalidToken",
                "The provided token is malformed or otherwise not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidURI,
            {
                s3::err::S3ErrorCode::InvalidURI,
                "InvalidURI",
                "The specified URI couldn't be parsed.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTagTagging,
            {
                s3::err::S3ErrorCode::InvalidTagTagging,
                "InvalidTag",
                "Your request contains tag input that is not valid. For example, your request might contain duplicate keys, keys or values that are "
                "too long, or system tags.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTagAccessGrants,
            {
                s3::err::S3ErrorCode::InvalidTagAccessGrants,
                "InvalidTag",
                "There are duplicate tag keys in your request. Remove the duplicate tag keys and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTagStorageLensTagging,
            {
                s3::err::S3ErrorCode::InvalidTagStorageLensTagging,
                "InvalidTag",
                "This request contains a tag key or value that isn't valid. Valid characters include [a-zA-Z+-=._:/]. Tag keys can contain up to 128 "
                "characters. Tag values can contain up to 256 characters. There are duplicate tag keys in your request. User-defined tag keys can't "
                "start with aws:.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTagStorageLensGroup,
            {
                s3::err::S3ErrorCode::InvalidTagStorageLensGroup,
                "InvalidTag",
                "The object tag key or value is invalid for Storage Lens groups.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::KeyTooLongError,
            {
                s3::err::S3ErrorCode::KeyTooLongError,
                "KeyTooLongError",
                "Your key is too long.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MalformedACLError,
            {
                s3::err::S3ErrorCode::MalformedACLError,
                "MalformedACLError",
                "The ACL that you provided was not well formed or did not validate against our published schema.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MalformedPOSTRequest,
            {
                s3::err::S3ErrorCode::MalformedPOSTRequest,
                "MalformedPOSTRequest",
                "The body of your POST request is not well-formed multipart/form-data.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MalformedXML,
            {
                s3::err::S3ErrorCode::MalformedXML,
                "MalformedXML",
                "The XML that you provided was not well formed or did not validate against our published schema.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MaxMessageLengthExceeded,
            {
                s3::err::S3ErrorCode::MaxMessageLengthExceeded,
                "MaxMessageLengthExceeded",
                "Your request was too large.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MaxPostPreDataLengthExceededError,
            {
                s3::err::S3ErrorCode::MaxPostPreDataLengthExceededError,
                "MaxPostPreDataLengthExceededError",
                "Your POST request fields preceding the upload file were too large.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MetadataTooLarge,
            {
                s3::err::S3ErrorCode::MetadataTooLarge,
                "MetadataTooLarge",
                "Your metadata headers exceed the maximum allowed metadata size.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MethodNotAllowed,
            {s3::err::S3ErrorCode::MethodNotAllowed, "MethodNotAllowed", "The specified method is not allowed against this resource.", 0,
             s3::http::HttpStatusCode::MethodNotAllowed},
        },
        {
            s3::err::S3ErrorCode::MethodNotAllowedSelect,
            {s3::err::S3ErrorCode::MethodNotAllowedSelect, "MethodNotAllowed", "The specified method is not allowed against this resource.", 0,
             s3::http::HttpStatusCode::MethodNotAllowed},
        },
        {
            s3::err::S3ErrorCode::MissingAuthenticationToken,
            {
                s3::err::S3ErrorCode::MissingAuthenticationToken,
                "MissingAuthenticationToken",
                "The request was not signed.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::MissingAttachment,
            {
                s3::err::S3ErrorCode::MissingAttachment,
                "MissingAttachment",
                "A SOAP attachment was expected, but none was found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingContentLength,
            {s3::err::S3ErrorCode::MissingContentLength, "MissingContentLength", "You must provide the Content-Length HTTP header.", 0,
             s3::http::HttpStatusCode::LengthRequired},
        },
        {
            s3::err::S3ErrorCode::MissingRequestBodyError,
            {
                s3::err::S3ErrorCode::MissingRequestBodyError,
                "MissingRequestBodyError",
                "You sent an empty XML document as a request.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingSecurityElement,
            {
                s3::err::S3ErrorCode::MissingSecurityElement,
                "MissingSecurityElement",
                "The SOAP 1.1 request is missing a security element.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingSecurityHeader,
            {
                s3::err::S3ErrorCode::MissingSecurityHeader,
                "MissingSecurityHeader",
                "Your request is missing a required header.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::NoLoggingStatusForKey,
            {
                s3::err::S3ErrorCode::NoLoggingStatusForKey,
                "NoLoggingStatusForKey",
                "There is no such thing as a logging status subresource for a key.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchAsyncRequest,
            {
                s3::err::S3ErrorCode::NoSuchAsyncRequest,
                "NoSuchAsyncRequest",
                "The specified request was not found.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchAccessPoint,
            {
                s3::err::S3ErrorCode::NoSuchAccessPoint,
                "NoSuchAccessPoint",
                "The specified access point does not exist.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchBucket,
            {
                s3::err::S3ErrorCode::NoSuchBucket,
                "NoSuchBucket",
                "The specified bucket does not exist.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchBucketAsync,
            {s3::err::S3ErrorCode::NoSuchBucketAsync, "NoSuchBucket", "The specified bucket does not exist.", 0, s3::http::HttpStatusCode::OK},
        },
        {
            s3::err::S3ErrorCode::NoSuchBucketPolicy,
            {
                s3::err::S3ErrorCode::NoSuchBucketPolicy,
                "NoSuchBucketPolicy",
                "The specified bucket does not have a bucket policy.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchCORSConfiguration,
            {
                s3::err::S3ErrorCode::NoSuchCORSConfiguration,
                "NoSuchCORSConfiguration",
                "The specified bucket does not have a CORS configuration.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchKey,
            {
                s3::err::S3ErrorCode::NoSuchKey,
                "NoSuchKey",
                "The specified key does not exist.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchLifecycleConfiguration,
            {
                s3::err::S3ErrorCode::NoSuchLifecycleConfiguration,
                "NoSuchLifecycleConfiguration",
                "The specified lifecycle configuration does not exist.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchMultiRegionAccessPoint,
            {
                s3::err::S3ErrorCode::NoSuchMultiRegionAccessPoint,
                "NoSuchMultiRegionAccessPoint",
                "The specified Multi-Region Access Point does not exist.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchMultiRegionAccessPointAsync,
            {s3::err::S3ErrorCode::NoSuchMultiRegionAccessPointAsync, "NoSuchMultiRegionAccessPoint",
             "The specified Multi-Region Access Point does not exist.", 0, s3::http::HttpStatusCode::OK},
        },
        {
            s3::err::S3ErrorCode::NoSuchObjectLockConfiguration,
            {
                s3::err::S3ErrorCode::NoSuchObjectLockConfiguration,
                "NoSuchObjectLockConfiguration",
                "The specified object does not have an ObjectLock configuration.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchTagSet,
            {
                s3::err::S3ErrorCode::NoSuchTagSet,
                "NoSuchTagSet",
                "The specified tag does not exist.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchUpload,
            {
                s3::err::S3ErrorCode::NoSuchUpload,
                "NoSuchUpload",
                "The specified multipart upload does not exist. The upload ID might not be valid, or the multipart upload might have been aborted or "
                "completed.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchVersion,
            {
                s3::err::S3ErrorCode::NoSuchVersion,
                "NoSuchVersion",
                "The version ID specified in the request does not match an existing version.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchWebsiteConfiguration,
            {
                s3::err::S3ErrorCode::NoSuchWebsiteConfiguration,
                "NoSuchWebsiteConfiguration",
                "The specified bucket does not have a website configuration.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NotDeviceOwnerError,
            {
                s3::err::S3ErrorCode::NotDeviceOwnerError,
                "NotDeviceOwnerError",
                "The device that generated the token is not owned by the authenticated user.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::NotImplemented,
            {
                s3::err::S3ErrorCode::NotImplemented,
                "NotImplemented",
                "A header you provided implies functionality that is not implemented.",
                0,
                s3::http::HttpStatusCode::NotImplemented,
            },
        },
        {
            s3::err::S3ErrorCode::NotModified,
            {
                s3::err::S3ErrorCode::NotModified,
                "NotModified",
                "The resource was not changed.",
                0,
                s3::http::HttpStatusCode::NotModified,
            },
        },
        {
            s3::err::S3ErrorCode::NotSignedUp,
            {
                s3::err::S3ErrorCode::NotSignedUp,
                "NotSignedUp",
                "Your account is not signed up for the Amazon S3 service. You must sign up before you can use Amazon S3. You can sign up at the "
                "following URL: [https://aws.amazon.com/s3](https://aws.amazon.com/s3/)",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::NoTransformationDefined,
            {
                s3::err::S3ErrorCode::NoTransformationDefined,
                "NoTransformationDefined",
                "No transformation found for this Object Lambda Access Point.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::ObjectLockConfigurationNotFoundError,
            {
                s3::err::S3ErrorCode::ObjectLockConfigurationNotFoundError,
                "ObjectLockConfigurationNotFoundError",
                "The Object Lock configuration does not exist for this bucket.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::OwnershipControlsNotFoundError,
            {
                s3::err::S3ErrorCode::OwnershipControlsNotFoundError,
                "OwnershipControlsNotFoundError",
                "The bucket ownership controls were not found.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::OperationAborted,
            {
                s3::err::S3ErrorCode::OperationAborted,
                "OperationAborted",
                "A conflicting conditional operation is currently in progress against this resource. Try again.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::PermanentRedirect,
            {
                s3::err::S3ErrorCode::PermanentRedirect,
                "PermanentRedirect",
                "The bucket that you are attempting to access must be addressed using the specified endpoint. Send all future requests to this "
                "endpoint.",
                0,
                s3::http::HttpStatusCode::MovedPermanently,
            },
        },
        {
            s3::err::S3ErrorCode::PermanentRedirectControlError,
            {
                s3::err::S3ErrorCode::PermanentRedirectControlError,
                "PermanentRedirectControlError",
                "The API operation you are attempting to access must be addressed using the specified endpoint. Send all future requests to this "
                "endpoint.",
                0,
                s3::http::HttpStatusCode::MovedPermanently,
            },
        },
        {
            s3::err::S3ErrorCode::PreconditionFailed,
            {
                s3::err::S3ErrorCode::PreconditionFailed,
                "PreconditionFailed",
                "At least one of the preconditions that you specified did not hold.",
                0,
                s3::http::HttpStatusCode::PreconditionFailed,
            },
        },
        {
            s3::err::S3ErrorCode::Redirect,
            {
                s3::err::S3ErrorCode::Redirect,
                "Redirect",
                "Temporary redirect. You are being redirected to the bucket while the Domain Name System (DNS) server is being updated.",
                0,
                s3::http::HttpStatusCode::TemporaryRedirect,
            },
        },
        {
            s3::err::S3ErrorCode::RequestHeaderSectionTooLarge,
            {
                s3::err::S3ErrorCode::RequestHeaderSectionTooLarge,
                "RequestHeaderSectionTooLarge",
                "The request header and query parameters used to make the request exceed the maximum allowed size.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::RequestIsNotMultiPartContent,
            {
                s3::err::S3ErrorCode::RequestIsNotMultiPartContent,
                "RequestIsNotMultiPartContent",
                "A bucket POST request must be of the enclosure-type multipart/form-data.",
                0,
                s3::http::HttpStatusCode::PreconditionFailed,
            },
        },
        {
            s3::err::S3ErrorCode::RequestTimeout,
            {
                s3::err::S3ErrorCode::RequestTimeout,
                "RequestTimeout",
                "Your socket connection to the server was not read from or written to within the timeout period.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::RequestTimeTooSkewed,
            {
                s3::err::S3ErrorCode::RequestTimeTooSkewed,
                "RequestTimeTooSkewed",
                "The difference between the request time and the server's time is too large.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::RequestTorrentOfBucketError,
            {
                s3::err::S3ErrorCode::RequestTorrentOfBucketError,
                "RequestTorrentOfBucketError",
                "Requesting the torrent file of a bucket is not permitted.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ResponseInterrupted,
            {
                s3::err::S3ErrorCode::ResponseInterrupted,
                "ResponseInterrupted",
                "Returned to the original caller when an error is encountered while reading the WriteGetObjectResponse body.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::RestoreAlreadyInProgress,
            {
                s3::err::S3ErrorCode::RestoreAlreadyInProgress,
                "RestoreAlreadyInProgress",
                "The object restore is already in progress.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::ServerSideEncryptionConfigurationNotFoundError,
            {
                s3::err::S3ErrorCode::ServerSideEncryptionConfigurationNotFoundError,
                "ServerSideEncryptionConfigurationNotFoundError",
                "The server-side encryption configuration was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::SignatureDoesNotMatch,
            {
                s3::err::S3ErrorCode::SignatureDoesNotMatch,
                "SignatureDoesNotMatch",
                "The request signature that the server calculated does not match the signature that you provided. Check your AWS secret access key "
                "and signing method. For more information, see [REST "
                "Authentication](https://docs.aws.amazon.com/AmazonS3/latest/userguide/RESTAuthentication.html) and [SOAP "
                "Authentication](https://docs.aws.amazon.com/AmazonS3/latest/userguide/SOAPAuthentication.html).",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::TagPolicyException,
            {
                s3::err::S3ErrorCode::TagPolicyException,
                "TagPolicyException",
                "The tag policy does not allow the specified value for the following tag key.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TagPolicyExceptionTagging,
            {
                s3::err::S3ErrorCode::TagPolicyExceptionTagging,
                "TagPolicyException",
                "The tag policy does not allow the specified value for the following tag key.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TemporaryRedirect,
            {
                s3::err::S3ErrorCode::TemporaryRedirect,
                "TemporaryRedirect",
                "You are being redirected to the bucket while the Domain Name System (DNS) server is being updated.",
                0,
                s3::http::HttpStatusCode::TemporaryRedirect,
            },
        },
        {
            s3::err::S3ErrorCode::TokenCodeInvalidError,
            {
                s3::err::S3ErrorCode::TokenCodeInvalidError,
                "TokenCodeInvalidError",
                "The serial number and/or token code you provided is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TokenRefreshRequired,
            {
                s3::err::S3ErrorCode::TokenRefreshRequired,
                "TokenRefreshRequired",
                "The provided token must be refreshed.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyAccessPoints,
            {
                s3::err::S3ErrorCode::TooManyAccessPoints,
                "TooManyAccessPoints",
                "You have attempted to create more access points than are allowed for an account. For more information, see [Amazon Simple Storage "
                "Service endpoints and quotas](https://docs.aws.amazon.com//general/latest/gr/s3.html) in the AWS General Reference.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyBuckets,
            {
                s3::err::S3ErrorCode::TooManyBuckets,
                "TooManyBuckets",
                "You have attempted to create more buckets than are allowed for an account. For more information, see [Amazon Simple Storage Service "
                "endpoints and quotas](https://docs.aws.amazon.com//general/latest/gr/s3.html) in the AWS General Reference.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyBucketsStorageLens,
            {
                s3::err::S3ErrorCode::TooManyBucketsStorageLens,
                "TooManyBuckets",
                "The buckets container cannot have more than 50 buckets.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyMultiRegionAccessPointregionsError,
            {
                s3::err::S3ErrorCode::TooManyMultiRegionAccessPointregionsError,
                "TooManyMultiRegionAccessPointregionsError",
                "You have attempted to create a Multi-Region Access Point with more Regions than are allowed for an account. For more information, "
                "see [Amazon Simple Storage Service endpoints and quotas](https://docs.aws.amazon.com//general/latest/gr/s3.html) in the AWS General "
                "Reference.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyMultiRegionAccessPoints,
            {
                s3::err::S3ErrorCode::TooManyMultiRegionAccessPoints,
                "TooManyMultiRegionAccessPoints",
                "You have attempted to create more Multi-Region Access Points than are allowed for an account. For more information, see [Amazon "
                "Simple Storage Service endpoints and quotas](https://docs.aws.amazon.com//general/latest/gr/s3.html) in the AWS General Reference.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnauthorizedAccess,
            {s3::err::S3ErrorCode::UnauthorizedAccess, "UnauthorizedAccess", "You are not authorized to perform this operation.", 0,
             s3::http::HttpStatusCode::Unauthorized},
        },
        {
            s3::err::S3ErrorCode::UnauthorizedAccessError,
            {
                s3::err::S3ErrorCode::UnauthorizedAccessError,
                "UnauthorizedAccessError",
                "Applicable in China Regions only. Returned when a request is made to a bucket that doesn't have an ICP license. For more "
                "information, see [ICP Recordal](https://www.amazonaws.cn/en/support/icp/).",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::UnexpectedIPError,
            {
                s3::err::S3ErrorCode::UnexpectedIPError,
                "UnexpectedIPError",
                "Applicable in China Regions only. This request was rejected because the IP was unexpected.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::UnexpectedContent,
            {
                s3::err::S3ErrorCode::UnexpectedContent,
                "UnexpectedContent",
                "This request contains unsupported content.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedArgument,
            {
                s3::err::S3ErrorCode::UnsupportedArgument,
                "UnsupportedArgument",
                "The request contained an unsupported argument.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedOperation,
            {
                s3::err::S3ErrorCode::UnsupportedOperation,
                "UnsupportedOperation",
                "The specified action was not supported.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedSignature,
            {
                s3::err::S3ErrorCode::UnsupportedSignature,
                "UnsupportedSignature",
                "The provided request is signed with an unsupported STS Token version or the signature version is not supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::KMSDisabledException,
            {
                s3::err::S3ErrorCode::KMSDisabledException,
                "KMS.DisabledException",
                "The request was rejected because the specified KMS key is not enabled.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::KMSInvalidKeyUsageException,
            {
                s3::err::S3ErrorCode::KMSInvalidKeyUsageException,
                "KMS.InvalidKeyUsageException",
                "To find the encryption or signing algorithms supported for a particular KMS key, use the DescribeKey operation.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::KMSKMSInvalidStateException,
            {
                s3::err::S3ErrorCode::KMSKMSInvalidStateException,
                "KMS.KMSInvalidStateException",
                "The request was rejected because the state of the specified resource is not valid for this request.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::KMSNotFoundException,
            {
                s3::err::S3ErrorCode::KMSNotFoundException,
                "KMS.NotFoundException",
                "The request was rejected because the specified entity or resource could not be found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnresolvableGrantByEmailAddress,
            {
                s3::err::S3ErrorCode::UnresolvableGrantByEmailAddress,
                "UnresolvableGrantByEmailAddress",
                "The email address that you provided does not match any account on record.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UserKeyMustBeSpecified,
            {
                s3::err::S3ErrorCode::UserKeyMustBeSpecified,
                "UserKeyMustBeSpecified",
                "The bucket POST request must contain the specified field name. If it is specified, check the order of the fields.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MalformedPolicy,
            {
                s3::err::S3ErrorCode::MalformedPolicy,
                "MalformedPolicy",
                "Your policy contains a principal that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MalformedPolicyAsync,
            {
                s3::err::S3ErrorCode::MalformedPolicyAsync,
                "MalformedPolicy",
                "The specified policy syntax is not valid.",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyTags,
            {
                s3::err::S3ErrorCode::TooManyTags,
                "TooManyTags",
                "The number of tags exceeds the limit of 50 tags.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyTagsAccessGrants,
            {
                s3::err::S3ErrorCode::TooManyTagsAccessGrants,
                "TooManyTags",
                "The number of tags exceeds the limit of 50 tags. Remove some tags and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InsufficientCapacity,
            {s3::err::S3ErrorCode::InsufficientCapacity, "InsufficientCapacity", "Insufficient capacity.", 0,
             s3::http::HttpStatusCode::InsufficientStorage},
        },
        {
            s3::err::S3ErrorCode::ServiceUnavailable,
            {
                s3::err::S3ErrorCode::ServiceUnavailable,
                "ServiceUnavailable",
                "Service is unable to handle request.",
                0,
                s3::http::HttpStatusCode::ServiceUnavailable,
            },
        },
        {
            s3::err::S3ErrorCode::SlowDown,
            {
                s3::err::S3ErrorCode::SlowDown,
                "SlowDown",
                "Please reduce your request rate.",
                0,
                s3::http::HttpStatusCode::ServiceUnavailable,
            },
        },
        {
            s3::err::S3ErrorCode::SlowDownObjectLambda,
            {
                s3::err::S3ErrorCode::SlowDownObjectLambda,
                "SlowDown",
                "Reduce your request rate for operations involving AWS Lambda.",
                0,
                s3::http::HttpStatusCode::ServiceUnavailable,
            },
        },
        {
            s3::err::S3ErrorCode::SlowDownFSx,
            {
                s3::err::S3ErrorCode::SlowDownFSx,
                "SlowDown",
                "Please reduce your request rate.",
                0,
                s3::http::HttpStatusCode::ServiceUnavailable,
            },
        },
        {
            s3::err::S3ErrorCode::AmbiguousFieldName,
            {
                s3::err::S3ErrorCode::AmbiguousFieldName,
                "AmbiguousFieldName",
                "The field name matches to multiple fields in the file. Check the SQL expression and the file, and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::Busy,
            {
                s3::err::S3ErrorCode::Busy,
                "Busy",
                "The service is unavailable. Try again later.",
                0,
                s3::http::HttpStatusCode::ServiceUnavailable,
            },
        },
        {
            s3::err::S3ErrorCode::CastFailed,
            {
                s3::err::S3ErrorCode::CastFailed,
                "CastFailed",
                "An attempt to convert from one data type to another usingCAST failed in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ColumnTooLong,
            {
                s3::err::S3ErrorCode::ColumnTooLong,
                "ColumnTooLong",
                "The length of a column in the result is greater thanmaxCharsPerColumn of 1 MB.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::CSVEscapingRecordDelimiter,
            {
                s3::err::S3ErrorCode::CSVEscapingRecordDelimiter,
                "CSVEscapingRecordDelimiter",
                "A quoted record delimiter was found in the file. To allow quoted record delimiters, setAllowQuotedRecordDelimiter to'TRUE'.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::CSVParsingError,
            {
                s3::err::S3ErrorCode::CSVParsingError,
                "CSVParsingError",
                "An error occurred while parsing the CSV file. Check the file and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::CSVUnescapedQuote,
            {
                s3::err::S3ErrorCode::CSVUnescapedQuote,
                "CSVUnescapedQuote",
                "An unescaped quote was found while parsing the CSV file. To allow quoted record delimiters, setAllowQuotedRecordDelimiter to'TRUE'.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EmptyRequestBody,
            {
                s3::err::S3ErrorCode::EmptyRequestBody,
                "EmptyRequestBody",
                "The request body cannot be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorBindingDoesNotExist,
            {
                s3::err::S3ErrorCode::EvaluatorBindingDoesNotExist,
                "EvaluatorBindingDoesNotExist",
                "A column name or a path provided does not exist in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorInvalidArguments,
            {
                s3::err::S3ErrorCode::EvaluatorInvalidArguments,
                "EvaluatorInvalidArguments",
                "There is an incorrect number of arguments in the function call in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPattern,
            {
                s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPattern,
                "EvaluatorInvalidTimestampFormatPattern",
                "The timestamp format string in the SQL expression is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPatternSymbol,
            {
                s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPatternSymbol,
                "EvaluatorInvalidTimestampFormatPatternSymbol",
                "The timestamp format pattern contains a symbol in the SQL expression that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPatternSymbolForParsing,
            {
                s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPatternSymbolForParsing,
                "EvaluatorInvalidTimestampFormatPatternSymbolForParsing",
                "The timestamp format pattern contains a valid format symbol that cannot be applied to timestamp parsing in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPatternToken,
            {
                s3::err::S3ErrorCode::EvaluatorInvalidTimestampFormatPatternToken,
                "EvaluatorInvalidTimestampFormatPatternToken",
                "The timestamp format pattern contains a token in the SQL expression that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorLikePatternInvalidEscapeSequence,
            {
                s3::err::S3ErrorCode::EvaluatorLikePatternInvalidEscapeSequence,
                "EvaluatorLikePatternInvalidEscapeSequence",
                "An argument given to the LIKE expression was not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorNegativeLimit,
            {
                s3::err::S3ErrorCode::EvaluatorNegativeLimit,
                "EvaluatorNegativeLimit",
                "LIMIT must not be negative.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorTimestampFormatPatternDuplicateFields,
            {
                s3::err::S3ErrorCode::EvaluatorTimestampFormatPatternDuplicateFields,
                "EvaluatorTimestampFormatPatternDuplicateFields",
                "The timestamp format pattern contains multiple format specifiers representing the timestamp field in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorTimestampFormatPatternHourClockAmPmMismatch,
            {
                s3::err::S3ErrorCode::EvaluatorTimestampFormatPatternHourClockAmPmMismatch,
                "EvaluatorTimestampFormatPatternHourClockAmPmMismatch",
                "The timestamp format pattern contains a 12-hour hour of day format symbol but doesn't also contain an AM/PM field, or it contains a "
                "24-hour hour of day format specifier and contains an AM/PM field in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EvaluatorUnterminatedTimestampFormatPatternToken,
            {
                s3::err::S3ErrorCode::EvaluatorUnterminatedTimestampFormatPatternToken,
                "EvaluatorUnterminatedTimestampFormatPatternToken",
                "The timestamp format pattern contains an unterminated token in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ExpressionTooLong,
            {
                s3::err::S3ErrorCode::ExpressionTooLong,
                "ExpressionTooLong",
                "The SQL expression is too long. The maximum byte-length for an SQL expression is 256 KB.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ExternalEvalException,
            {
                s3::err::S3ErrorCode::ExternalEvalException,
                "ExternalEvalException",
                "The query cannot be evaluated. Check the file and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IllegalSqlFunctionArgument,
            {
                s3::err::S3ErrorCode::IllegalSqlFunctionArgument,
                "IllegalSqlFunctionArgument",
                "An illegal argument was used in the SQL function.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IncorrectSqlFunctionArgumentType,
            {
                s3::err::S3ErrorCode::IncorrectSqlFunctionArgumentType,
                "IncorrectSqlFunctionArgumentType",
                "An incorrect argument type was specified in a function call in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::IntegerOverflow,
            {
                s3::err::S3ErrorCode::IntegerOverflow,
                "IntegerOverflow",
                "An integer overflow or underflow occurred in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InternalErrorSelect2,
            {s3::err::S3ErrorCode::InternalErrorSelect2, "InternalError", "An internal error occurred.", 0,
             s3::http::HttpStatusCode::InternalServerError},
        },
        {
            s3::err::S3ErrorCode::InvalidCast,
            {
                s3::err::S3ErrorCode::InvalidCast,
                "InvalidCast",
                "An attempt to convert from one data type to another usingCAST failed in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidColumnIndex,
            {
                s3::err::S3ErrorCode::InvalidColumnIndex,
                "InvalidColumnIndex",
                "The column index in the SQL expression is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidCompressionFormat,
            {
                s3::err::S3ErrorCode::InvalidCompressionFormat,
                "InvalidCompressionFormat",
                "The file is not in a supported compression format. Only GZIP and BZIP2 are supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidDataSource,
            {
                s3::err::S3ErrorCode::InvalidDataSource,
                "InvalidDataSource",
                "The data source type is not valid. Only CSV, JSON, and Parquet are supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidDataType,
            {
                s3::err::S3ErrorCode::InvalidDataType,
                "InvalidDataType",
                "The SQL expression contains a data type that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidExpressionType,
            {
                s3::err::S3ErrorCode::InvalidExpressionType,
                "InvalidExpressionType",
                "TheExpressionType value is not valid. Only SQL expressions are supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidFileHeaderInfo,
            {
                s3::err::S3ErrorCode::InvalidFileHeaderInfo,
                "InvalidFileHeaderInfo",
                "TheFileHeaderInfo value is not valid. OnlyNONE,USE, andIGNORE are supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidJsonType,
            {
                s3::err::S3ErrorCode::InvalidJsonType,
                "InvalidJsonType",
                "The JsonType value is not valid. Only DOCUMENT and LINES are supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidKeyPath,
            {
                s3::err::S3ErrorCode::InvalidKeyPath,
                "InvalidKeyPath",
                "The key path in the SQL expression is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidQuoteFields,
            {
                s3::err::S3ErrorCode::InvalidQuoteFields,
                "InvalidQuoteFields",
                "The QuoteFields value is not valid. Only ALWAYS and ASNEEDED are supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRequestParameter,
            {
                s3::err::S3ErrorCode::InvalidRequestParameter,
                "InvalidRequestParameter",
                "The value of a parameter in theSelectRequest element is not valid. Check the service API documentation and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidScanRange,
            {
                s3::err::S3ErrorCode::InvalidScanRange,
                "InvalidScanRange",
                "The provided scan range is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTableAlias,
            {
                s3::err::S3ErrorCode::InvalidTableAlias,
                "InvalidTableAlias",
                "The SQL expression contains a table alias that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTextEncoding,
            {
                s3::err::S3ErrorCode::InvalidTextEncoding,
                "InvalidTextEncoding",
                "The encoding type is not valid. Only UTF-8 encoding is supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::JSONParsingError,
            {
                s3::err::S3ErrorCode::JSONParsingError,
                "JSONParsingError",
                "An error occurred while parsing the JSON file. Check the file and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LexerInvalidChar,
            {
                s3::err::S3ErrorCode::LexerInvalidChar,
                "LexerInvalidChar",
                "The SQL expression contains a character that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LexerInvalidIONLiteral,
            {
                s3::err::S3ErrorCode::LexerInvalidIONLiteral,
                "LexerInvalidIONLiteral",
                "The SQL expression contains an operator that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LexerInvalidLiteral,
            {
                s3::err::S3ErrorCode::LexerInvalidLiteral,
                "LexerInvalidLiteral",
                "The SQL expression contains an operator that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LexerInvalidOperator,
            {
                s3::err::S3ErrorCode::LexerInvalidOperator,
                "LexerInvalidOperator",
                "The SQL expression contains a literal that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LikeInvalidInputs,
            {
                s3::err::S3ErrorCode::LikeInvalidInputs,
                "LikeInvalidInputs",
                "The argument given to the LIKE clause in the SQL expression is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MalformedXMLSelect,
            {
                s3::err::S3ErrorCode::MalformedXMLSelect,
                "MalformedXML",
                "The XML provided was not well formed or did not validate against our published schema. Check the service documentation and try "
                "again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MaxOperatorsExceeded,
            {
                s3::err::S3ErrorCode::MaxOperatorsExceeded,
                "MaxOperatorsExceeded",
                "Failed to parse SQL expression, try reducing complexity. For example, reduce number of operators used.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingRequiredParameter,
            {
                s3::err::S3ErrorCode::MissingRequiredParameter,
                "MissingRequiredParameter",
                "TheSelectRequest entity is missing a required parameter. Check the service documentation and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MultipleDataSourcesUnsupported,
            {
                s3::err::S3ErrorCode::MultipleDataSourcesUnsupported,
                "MultipleDataSourcesUnsupported",
                "Multiple data sources are not supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::NumberFormatError,
            {
                s3::err::S3ErrorCode::NumberFormatError,
                "NumberFormatError",
                "An error occurred while parsing a number. This error can be caused by underflow or overflow of integers.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ObjectSerializationConflict,
            {
                s3::err::S3ErrorCode::ObjectSerializationConflict,
                "ObjectSerializationConflict",
                "InputSerialization specifies more than one format (CSV, JSON, or Parquet), orOutputSerialization specifies more than one format "
                "(CSV or JSON). ForInputSerialization andOutputSerialization, you can specify only one format for each.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::OverMaxColumn,
            {
                s3::err::S3ErrorCode::OverMaxColumn,
                "OverMaxColumn",
                "The number of columns in the result is greater than the maximum allowable number of columns.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::OverMaxParquetBlockSize,
            {
                s3::err::S3ErrorCode::OverMaxParquetBlockSize,
                "OverMaxParquetBlockSize",
                "The Parquet file is above the max row group size.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::OverMaxRecordSize,
            {
                s3::err::S3ErrorCode::OverMaxRecordSize,
                "OverMaxRecordSize",
                "The length of a record in the input or result is greater than themaxCharsPerRecord limit of 1 MB.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParquetParsingError,
            {
                s3::err::S3ErrorCode::ParquetParsingError,
                "ParquetParsingError",
                "An error occurred while parsing the Parquet file. Check the file and try again.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParquetUnsupportedCompressionCodec,
            {
                s3::err::S3ErrorCode::ParquetUnsupportedCompressionCodec,
                "ParquetUnsupportedCompressionCodec",
                "The specified Parquet compression codec is not supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseAsteriskIsNotAloneInSelectList,
            {
                s3::err::S3ErrorCode::ParseAsteriskIsNotAloneInSelectList,
                "ParseAsteriskIsNotAloneInSelectList",
                "Other expressions are not allowed in theSELECT list when* is used without dot notation in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseCannotMixSqbAndWildcardInSelectList,
            {
                s3::err::S3ErrorCode::ParseCannotMixSqbAndWildcardInSelectList,
                "ParseCannotMixSqbAndWildcardInSelectList",
                "Cannot mix[] and* in the same expression in aSELECT list in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseCastArity,
            {
                s3::err::S3ErrorCode::ParseCastArity,
                "ParseCastArity",
                "The SQL expressionCAST has incorrect arity.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseEmptySelect,
            {
                s3::err::S3ErrorCode::ParseEmptySelect,
                "ParseEmptySelect",
                "The SQL expression contains an empty SELECT clause.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpected2TokenTypes,
            {
                s3::err::S3ErrorCode::ParseExpected2TokenTypes,
                "ParseExpected2TokenTypes",
                "The expected token in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedArgumentDelimiter,
            {
                s3::err::S3ErrorCode::ParseExpectedArgumentDelimiter,
                "ParseExpectedArgumentDelimiter",
                "The expected argument delimiter in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedDatePart,
            {
                s3::err::S3ErrorCode::ParseExpectedDatePart,
                "ParseExpectedDatePart",
                "The expected date part in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedExpression,
            {
                s3::err::S3ErrorCode::ParseExpectedExpression,
                "ParseExpectedExpression",
                "The expected SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedIdentForAlias,
            {
                s3::err::S3ErrorCode::ParseExpectedIdentForAlias,
                "ParseExpectedIdentForAlias",
                "The expected identifier for the alias in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedIdentForAt,
            {
                s3::err::S3ErrorCode::ParseExpectedIdentForAt,
                "ParseExpectedIdentForAt",
                "The expected identifier forAT name in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedIdentForGroupName,
            {
                s3::err::S3ErrorCode::ParseExpectedIdentForGroupName,
                "ParseExpectedIdentForGroupName",
                "GROUP is not supported in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedKeyword,
            {
                s3::err::S3ErrorCode::ParseExpectedKeyword,
                "ParseExpectedKeyword",
                "The expected keyword in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedLeftParenAfterCast,
            {
                s3::err::S3ErrorCode::ParseExpectedLeftParenAfterCast,
                "ParseExpectedLeftParenAfterCast",
                "The expected left parenthesis afterCAST in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedLeftParenBuiltinFunctionCall,
            {
                s3::err::S3ErrorCode::ParseExpectedLeftParenBuiltinFunctionCall,
                "ParseExpectedLeftParenBuiltinFunctionCall",
                "The expected left parenthesis in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedLeftParenValueConstructor,
            {
                s3::err::S3ErrorCode::ParseExpectedLeftParenValueConstructor,
                "ParseExpectedLeftParenValueConstructor",
                "The expected left parenthesis in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedMember,
            {
                s3::err::S3ErrorCode::ParseExpectedMember,
                "ParseExpectedMember",
                "The SQL expression contains an unsupported use ofMEMBER.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedNumber,
            {
                s3::err::S3ErrorCode::ParseExpectedNumber,
                "ParseExpectedNumber",
                "The expected number in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedRightParenBuiltinFunctionCall,
            {
                s3::err::S3ErrorCode::ParseExpectedRightParenBuiltinFunctionCall,
                "ParseExpectedRightParenBuiltinFunctionCall",
                "The expected right parenthesis character in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedTokenType,
            {
                s3::err::S3ErrorCode::ParseExpectedTokenType,
                "ParseExpectedTokenType",
                "The expected token in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedTypeName,
            {
                s3::err::S3ErrorCode::ParseExpectedTypeName,
                "ParseExpectedTypeName",
                "The expected type name in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseExpectedWhenClause,
            {
                s3::err::S3ErrorCode::ParseExpectedWhenClause,
                "ParseExpectedWhenClause",
                "The expectedWHEN clause in the SQL expression was not found.CASE is not supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseInvalidContextForWildcardInSelectList,
            {
                s3::err::S3ErrorCode::ParseInvalidContextForWildcardInSelectList,
                "ParseInvalidContextForWildcardInSelectList",
                "The use of* in the SELECT list in the SQL expression is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseInvalidPathComponent,
            {
                s3::err::S3ErrorCode::ParseInvalidPathComponent,
                "ParseInvalidPathComponent",
                "The SQL expression contains a path component that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseInvalidTypeParam,
            {
                s3::err::S3ErrorCode::ParseInvalidTypeParam,
                "ParseInvalidTypeParam",
                "The SQL expression contains a parameter value that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseMalformedJoin,
            {
                s3::err::S3ErrorCode::ParseMalformedJoin,
                "ParseMalformedJoin",
                "JOIN is not supported in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseMissingIdentAfterAt,
            {
                s3::err::S3ErrorCode::ParseMissingIdentAfterAt,
                "ParseMissingIdentAfterAt",
                "The expected identifier after the @ symbol in the SQL expression was not found.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseNonUnaryAgregateFunctionCall,
            {
                s3::err::S3ErrorCode::ParseNonUnaryAgregateFunctionCall,
                "ParseNonUnaryAgregateFunctionCall",
                "Only one argument is supported for aggregate functions in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseSelectMissingFrom,
            {
                s3::err::S3ErrorCode::ParseSelectMissingFrom,
                "ParseSelectMissingFrom",
                "The SQL expression contains a missing FROM after the SELECT list.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnExpectedKeyword,
            {
                s3::err::S3ErrorCode::ParseUnExpectedKeyword,
                "ParseUnExpectedKeyword",
                "The SQL expression contains an unexpected keyword.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnexpectedOperator,
            {
                s3::err::S3ErrorCode::ParseUnexpectedOperator,
                "ParseUnexpectedOperator",
                "The SQL expression contains an unexpected operator.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnexpectedTerm,
            {
                s3::err::S3ErrorCode::ParseUnexpectedTerm,
                "ParseUnexpectedTerm",
                "The SQL expression contains an unexpected term.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnexpectedToken,
            {
                s3::err::S3ErrorCode::ParseUnexpectedToken,
                "ParseUnexpectedToken",
                "The SQL expression contains an unexpected token.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnknownOperator,
            {
                s3::err::S3ErrorCode::ParseUnknownOperator,
                "ParseUnknownOperator",
                "The SQL expression contains an operator that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedAlias,
            {
                s3::err::S3ErrorCode::ParseUnsupportedAlias,
                "ParseUnsupportedAlias",
                "The SQL expression contains an unsupported use ofALIAS.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedCallWithStar,
            {
                s3::err::S3ErrorCode::ParseUnsupportedCallWithStar,
                "ParseUnsupportedCallWithStar",
                "Only COUNT with(*) as a parameter is supported in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedCase,
            {
                s3::err::S3ErrorCode::ParseUnsupportedCase,
                "ParseUnsupportedCase",
                "The SQL expression contains an unsupported use of CASE.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedCaseClause,
            {
                s3::err::S3ErrorCode::ParseUnsupportedCaseClause,
                "ParseUnsupportedCaseClause",
                "The SQL expression contains an unsupported use of CASE.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedLiteralsGroupBy,
            {
                s3::err::S3ErrorCode::ParseUnsupportedLiteralsGroupBy,
                "ParseUnsupportedLiteralsGroupBy",
                "The SQL expression contains an unsupported use of GROUP",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedSelect,
            {
                s3::err::S3ErrorCode::ParseUnsupportedSelect,
                "ParseUnsupportedSelect",
                "The SQL expression contains an unsupported use of SELECT.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedSyntax,
            {
                s3::err::S3ErrorCode::ParseUnsupportedSyntax,
                "ParseUnsupportedSyntax",
                "The SQL expression contains unsupported syntax.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ParseUnsupportedToken,
            {
                s3::err::S3ErrorCode::ParseUnsupportedToken,
                "ParseUnsupportedToken",
                "The SQL expression contains an unsupported token.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TruncatedInput,
            {
                s3::err::S3ErrorCode::TruncatedInput,
                "TruncatedInput",
                "Object decompression failed. Check that the object is properly compressed using the format specified in the request.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnrecognizedFormatException,
            {
                s3::err::S3ErrorCode::UnrecognizedFormatException,
                "UnrecognizedFormatException",
                "We encountered a record type that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedFunction,
            {
                s3::err::S3ErrorCode::UnsupportedFunction,
                "UnsupportedFunction",
                "We encountered an unsupported SQL function.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedParquetType,
            {
                s3::err::S3ErrorCode::UnsupportedParquetType,
                "UnsupportedParquetType",
                "The specified Parquet type is not supported.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedRangeHeader,
            {
                s3::err::S3ErrorCode::UnsupportedRangeHeader,
                "UnsupportedRangeHeader",
                "A range header is not supported for this operation.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedScanRangeInput,
            {
                s3::err::S3ErrorCode::UnsupportedScanRangeInput,
                "UnsupportedScanRangeInput",
                "Scan range queries are not supported on this type of object.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedSqlOperation,
            {
                s3::err::S3ErrorCode::UnsupportedSqlOperation,
                "UnsupportedSqlOperation",
                "We encountered an unsupported SQL operation.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedSqlStructure,
            {
                s3::err::S3ErrorCode::UnsupportedSqlStructure,
                "UnsupportedSqlStructure",
                "We encountered an unsupported SQL structure. Check the SQL Reference.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedStorageClass,
            {
                s3::err::S3ErrorCode::UnsupportedStorageClass,
                "UnsupportedStorageClass",
                "We encountered a storage class that is not supported. Only STANDARD, STANDARD_IA, and",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedSyntax,
            {
                s3::err::S3ErrorCode::UnsupportedSyntax,
                "UnsupportedSyntax",
                "We encountered syntax that is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::UnsupportedTypeForQuerying,
            {
                s3::err::S3ErrorCode::UnsupportedTypeForQuerying,
                "UnsupportedTypeForQuerying",
                "Your query contains an unsupported type for comparison (e.g. verifying that a Parquet INT96 column type is greater than 0).",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ValueParseFailure,
            {
                s3::err::S3ErrorCode::ValueParseFailure,
                "ValueParseFailure",
                "A timestamp parse failure occurred in the SQL expression.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ReplicationConfigurationNotFoundError,
            {
                s3::err::S3ErrorCode::ReplicationConfigurationNotFoundError,
                "ReplicationConfigurationNotFoundError",
                "There is no replication configuration for this bucket.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchResource,
            {
                s3::err::S3ErrorCode::NoSuchResource,
                "NoSuchResource",
                "The bucket is in a transitional state because of a previous deletion attempt. Try again later.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::BadRequest,
            {
                s3::err::S3ErrorCode::BadRequest,
                "BadRequest",
                "Amazon VPC configuration is required. Public access is not allowed on S3 on Outposts access points.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidOutpostState,
            {
                s3::err::S3ErrorCode::InvalidOutpostState,
                "InvalidOutpostState",
                "The request is not valid for the current state of the Outpost.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRequestOutposts2,
            {
                s3::err::S3ErrorCode::InvalidRequestOutposts2,
                "InvalidRequest",
                "The access point is not in a state where it can be deleted.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchOutpost,
            {
                s3::err::S3ErrorCode::NoSuchOutpost,
                "NoSuchOutpost",
                "The specified Outpost does not exist.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::AccountNotAuthorized,
            {
                s3::err::S3ErrorCode::AccountNotAuthorized,
                "AccountNotAuthorized",
                "This account not authorized to use AWS Organizations. Use your management account or delegated administrator account.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::ActivityMetricsMustEnabled,
            {
                s3::err::S3ErrorCode::ActivityMetricsMustEnabled,
                "ActivityMetricsMustEnabled",
                "Activity metrics must be enabled.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::AWSOrganizationsNotInUseException,
            {
                s3::err::S3ErrorCode::AWSOrganizationsNotInUseException,
                "AWSOrganizationsNotInUseException",
                "This account is not part of your organization.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::DefaultConfigurationDeleteForbidden,
            {
                s3::err::S3ErrorCode::DefaultConfigurationDeleteForbidden,
                "DefaultConfigurationDeleteForbidden",
                "The Default configuration cannot be deleted.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::DuplicateStorageLensGroupARN,
            {
                s3::err::S3ErrorCode::DuplicateStorageLensGroupARN,
                "DuplicateStorageLensGroupARN",
                "There are two or more entries of the same Storage Lens group ARN in this configuration.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EmptyExcludeContainer,
            {
                s3::err::S3ErrorCode::EmptyExcludeContainer,
                "EmptyExcludeContainer",
                "The exclude container cannot be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EmptyExcludeElement,
            {
                s3::err::S3ErrorCode::EmptyExcludeElement,
                "EmptyExcludeElement",
                "You must specify a Storage Lens group with your Exclude element.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EmptyIncludeContainer,
            {
                s3::err::S3ErrorCode::EmptyIncludeContainer,
                "EmptyIncludeContainer",
                "The include container cannot be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAWSOrgArn,
            {
                s3::err::S3ErrorCode::InvalidAWSOrgArn,
                "InvalidAWSOrgArn",
                "There is a malformed AWS Organizations ARN in the configuration.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::EmptyIncludeElement,
            {
                s3::err::S3ErrorCode::EmptyIncludeElement,
                "EmptyIncludeElement",
                "You must specify a Storage Lens group with your Include element.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidBucketFilter,
            {
                s3::err::S3ErrorCode::InvalidBucketFilter,
                "InvalidBucketFilter",
                "Organization-level configurations do not support bucket filters.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidConfigId,
            {
                s3::err::S3ErrorCode::InvalidConfigId,
                "InvalidConfigId",
                "The configuration ID is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidDestination,
            {
                s3::err::S3ErrorCode::InvalidDestination,
                "InvalidDestination",
                "The S3 bucket ARN is malformed.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidEncryptionMethod,
            {
                s3::err::S3ErrorCode::InvalidEncryptionMethod,
                "InvalidEncryptionMethod",
                "Only one encryption method can be specified.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidFilterForDefaultConfiguration,
            {
                s3::err::S3ErrorCode::InvalidFilterForDefaultConfiguration,
                "InvalidFilterForDefaultConfiguration",
                "The default configuration must not include any filters.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidIncludeExcludeContainers,
            {
                s3::err::S3ErrorCode::InvalidIncludeExcludeContainers,
                "InvalidIncludeExcludeContainers",
                "You can specify either an Include container or an Exclude container in a configuration. You cannot specify both in a configuration.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidIncludeExcludeElements,
            {
                s3::err::S3ErrorCode::InvalidIncludeExcludeElements,
                "InvalidIncludeExcludeElements",
                "Only one Include or Exclude element is allowed. At least one Include or Exclude element must be present.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidKMSEncryptionKeyId,
            {
                s3::err::S3ErrorCode::InvalidKMSEncryptionKeyId,
                "InvalidKMSEncryptionKeyId",
                "The KMS key ID ARN is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidMaximumPrefixDepth,
            {
                s3::err::S3ErrorCode::InvalidMaximumPrefixDepth,
                "InvalidMaximumPrefixDepth",
                "MaxDepth must be within the range [1,10].",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidMinimumStorageBytesPercentage,
            {
                s3::err::S3ErrorCode::InvalidMinimumStorageBytesPercentage,
                "InvalidMinimumStorageBytesPercentage",
                "MinStorageBytesPercentage must be within the range [1.00,100.00].",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidOrganizationARN,
            {
                s3::err::S3ErrorCode::InvalidOrganizationARN,
                "InvalidOrganizationARN",
                "The AWS Organizations ARN in the configuration is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidOrganizationForDefaultConfiguration,
            {
                s3::err::S3ErrorCode::InvalidOrganizationForDefaultConfiguration,
                "InvalidOrganizationForDefaultConfiguration",
                "The default configuration does not support organization-level metrics.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRegionForDefaultConfiguration,
            {
                s3::err::S3ErrorCode::InvalidRegionForDefaultConfiguration,
                "InvalidRegionForDefaultConfiguration",
                "The specified Region is not supported for default configuration.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidRegionName,
            {
                s3::err::S3ErrorCode::InvalidRegionName,
                "InvalidRegionName",
                "The Region name is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidStorageLensArn,
            {
                s3::err::S3ErrorCode::InvalidStorageLensArn,
                "InvalidStorageLensArn",
                "The S3 Storage Lens ARN is not required in input.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidStorageLensGroupARN,
            {
                s3::err::S3ErrorCode::InvalidStorageLensGroupARN,
                "InvalidStorageLensGroupARN",
                "This Storage Lens group ARN isn't valid or only Storage Lens groups in your account are allowed. Additionally, you must follow the "
                "Storage Lens group ARN structure:arn::s3:::storage-lens-group/ and adhere to the 64 character limit. Storage Lens group names can "
                "also contain only the following characters: a-z, A-Z, 0-9, hyphens (-), and underscores (_).",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingAccountLevelActivityMetrics,
            {
                s3::err::S3ErrorCode::MissingAccountLevelActivityMetrics,
                "MissingAccountLevelActivityMetrics",
                "Activity metrics must be enabled at the account level when activity metrics are enabled at the bucket level.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingBucketLevelActivityMetrics,
            {
                s3::err::S3ErrorCode::MissingBucketLevelActivityMetrics,
                "MissingBucketLevelActivityMetrics",
                "Activity metrics must be enabled at the bucket level when activity metrics are enabled at the account level.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingEncryptionMethod,
            {
                s3::err::S3ErrorCode::MissingEncryptionMethod,
                "MissingEncryptionMethod",
                "The encryption method cannot be blank. Specify either SSE-KMS or SSE-S3.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MissingPrefixLevelStorageMetrics,
            {
                s3::err::S3ErrorCode::MissingPrefixLevelStorageMetrics,
                "MissingPrefixLevelStorageMetrics",
                "Storage metrics at the prefix level are mandatory when the prefix level is enabled.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::OrganizationAccessDenied,
            {
                s3::err::S3ErrorCode::OrganizationAccessDenied,
                "OrganizationAccessDenied",
                "This account is not authorized to add AWS Organizations.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::OrgConfigurationNotSupported,
            {
                s3::err::S3ErrorCode::OrgConfigurationNotSupported,
                "OrgConfigurationNotSupported",
                "The specified Region does not support AWS Organizations in the configuration.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::ServiceNotEnabledForOrg,
            {
                s3::err::S3ErrorCode::ServiceNotEnabledForOrg,
                "ServiceNotEnabledForOrg",
                "The S3 Storage Lens service-linked role is not enabled for the organization.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::StorageMetricsMustEnabled,
            {
                s3::err::S3ErrorCode::StorageMetricsMustEnabled,
                "StorageMetricsMustEnabled",
                "Prefix-level storage metrics must be enabled.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyRegions,
            {
                s3::err::S3ErrorCode::TooManyRegions,
                "TooManyRegions",
                "The Regions container cannot have more than 50 Regions.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyStorageLensGroups,
            {
                s3::err::S3ErrorCode::TooManyStorageLensGroups,
                "TooManyStorageLensGroups",
                "You can't attach more than 50 Storage Lens groups to your Storage Lens dashboard.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ConfigurationAlreadyExists,
            {
                s3::err::S3ErrorCode::ConfigurationAlreadyExists,
                "ConfigurationAlreadyExists",
                "The specified configuration already exists.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::DuplicateElement,
            {
                s3::err::S3ErrorCode::DuplicateElement,
                "DuplicateElement",
                "Tags must be unique. The And logical operator includes duplicate tag keys. The Or logical operator includes duplicate tags. "
                "Logical operator includes duplicate prefixes or suffixes.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAge,
            {
                s3::err::S3ErrorCode::InvalidAge,
                "InvalidAge",
                "DaysLessThan and DaysGreaterThan must be positive numbers.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidFilter,
            {
                s3::err::S3ErrorCode::InvalidFilter,
                "InvalidFilter",
                "A filter must include one of the following "
                "elements: And, Or, MatchAnyTag, MatchAnyPrefix, MatchAnySuffix, MatchObjectAge, MatchObjectSize.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidLogicalOperator,
            {
                s3::err::S3ErrorCode::InvalidLogicalOperator,
                "InvalidLogicalOperator",
                "At least two sub elements must be present in the logical operators And or Or.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidMatchAnyPrefix,
            {
                s3::err::S3ErrorCode::InvalidMatchAnyPrefix,
                "InvalidMatchAnyPrefix",
                "The MatchAnyPrefix parameter can't be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidMatchAnySuffix,
            {
                s3::err::S3ErrorCode::InvalidMatchAnySuffix,
                "InvalidMatchAnySuffix",
                "The MatchAnySuffix parameter can't be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidMatchAnyTag,
            {
                s3::err::S3ErrorCode::InvalidMatchAnyTag,
                "InvalidMatchAnyTag",
                "The MatchAnyTag parameter can't be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidMatchObjectAge,
            {
                s3::err::S3ErrorCode::InvalidMatchObjectAge,
                "InvalidMatchObjectAge",
                "The MatchObjectAge parameter can't be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidMatchObjectSize,
            {
                s3::err::S3ErrorCode::InvalidMatchObjectSize,
                "InvalidMatchObjectSize",
                "The MatchObjectSize parameter can't be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidName,
            {
                s3::err::S3ErrorCode::InvalidName,
                "InvalidName",
                "Storage Lens group Name parameter must be between 1 and 64 characters. The Storage Lens group Name parameter must use "
                "the ^[a-zA-Z0-9-_]+$ pattern.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidNumericCombination,
            {
                s3::err::S3ErrorCode::InvalidNumericCombination,
                "InvalidNumericCombination",
                "This object age or object size combination isn't valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidPrefix,
            {
                s3::err::S3ErrorCode::InvalidPrefix,
                "InvalidPrefix",
                "The maximum length of a prefix is 1,024 characters. The prefix string can't be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidSize,
            {
                s3::err::S3ErrorCode::InvalidSize,
                "InvalidSize",
                "BytesLessThan and BytesGreaterThan must be positive numbers. The maximum object size can't exceed 50 TB. The minimum object size "
                "can't be greater than or equal to 50 TB.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidSuffix,
            {
                s3::err::S3ErrorCode::InvalidSuffix,
                "InvalidSuffix",
                "The maximum length of a suffix is 1,024 characters. The suffix string can't be empty.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::MismatchedName,
            {
                s3::err::S3ErrorCode::MismatchedName,
                "MismatchedName",
                "The name specified in the request doesn't match the Storage Lens group name.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyConfigurations,
            {
                s3::err::S3ErrorCode::TooManyConfigurations,
                "TooManyConfigurations",
                "You have attempted to create more Storage Lens group configurations than the 50 allowed.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyElements,
            {
                s3::err::S3ErrorCode::TooManyElements,
                "TooManyElements",
                "The Element exceeds the maximum number of elements allowed within a logical operator. Only 10 prefixes, suffixes, or tags are "
                "allowed.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LambdaInvalidResponse,
            {
                s3::err::S3ErrorCode::LambdaInvalidResponse,
                "LambdaInvalidResponse",
                "Returned to the original caller when WriteGetObjectResponse responds with ValidationError to AWS Lambda.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LambdaInvocationFailed,
            {
                s3::err::S3ErrorCode::LambdaInvocationFailed,
                "LambdaInvocationFailed",
                "Lambda function invocation failed.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::LambdaNotFound,
            {
                s3::err::S3ErrorCode::LambdaNotFound,
                "LambdaNotFound",
                "The AWS Lambda function was not found.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::LambdaPermissionError,
            {
                s3::err::S3ErrorCode::LambdaPermissionError,
                "LambdaPermissionError",
                "The caller is not authorized to invoke the Lambda function.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::LambdaResponseNotReceived,
            {
                s3::err::S3ErrorCode::LambdaResponseNotReceived,
                "LambdaResponseNotReceived",
                "The Lambda function exited without successfully calling WriteGetObjectResponse.",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::LambdaRuntimeError,
            {
                s3::err::S3ErrorCode::LambdaRuntimeError,
                "LambdaRuntimeError",
                "The Lambda function failed during execution.",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::LambdaTimeout,
            {
                s3::err::S3ErrorCode::LambdaTimeout,
                "LambdaTimeout",
                "The Lambda function did not respond in the allowed time.",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::ValidationError,
            {
                s3::err::S3ErrorCode::ValidationError,
                "ValidationError",
                "Validation errors might be returned from the WriteGetObjectResponse API operation and can occur for numerous reasons. See the "
                "error message for more details.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InternalErrors,
            {
                s3::err::S3ErrorCode::InternalErrors,
                "InternalErrors",
                "An internal server error occurred.",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::MultiRegionAccessPointAlreadyOwnedByYou,
            {
                s3::err::S3ErrorCode::MultiRegionAccessPointAlreadyOwnedByYou,
                "MultiRegionAccessPointAlreadyOwnedByYou",
                "You already have a Multi-Region Access Point with the same name.",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::MultiRegionAccessPointModifiedByAnotherRequest,
            {
                s3::err::S3ErrorCode::MultiRegionAccessPointModifiedByAnotherRequest,
                "MultiRegionAccessPointModifiedByAnotherRequest",
                "The action failed because another request is modifying the specified resource. Try resubmitting your request after the previous "
                "request has been completed.",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::MultiRegionAccessPointNotReady,
            {
                s3::err::S3ErrorCode::MultiRegionAccessPointNotReady,
                "MultiRegionAccessPointNotReady",
                "The specified Multi-Region Access Point is not ready to be updated.",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::MultiRegionAccessPointSameBucketRegion,
            {
                s3::err::S3ErrorCode::MultiRegionAccessPointSameBucketRegion,
                "MultiRegionAccessPointSameBucketRegion",
                "The buckets used to create a Multi-Region Access Point cannot be in the same Region.",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::MultiRegionAccessPointUnsupportedRegion,
            {
                s3::err::S3ErrorCode::MultiRegionAccessPointUnsupportedRegion,
                "MultiRegionAccessPointUnsupportedRegion",
                "One of the buckets supplied to create the Multi-Region Access Point is in a Region that is not supported.",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantAlreadyExists,
            {
                s3::err::S3ErrorCode::AccessGrantAlreadyExists,
                "AccessGrantAlreadyExists",
                "The specified access grant already exists",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsInstanceAlreadyExists,
            {
                s3::err::S3ErrorCode::AccessGrantsInstanceAlreadyExists,
                "AccessGrantsInstanceAlreadyExists",
                "Access Grants Instance already exists",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsInstanceNotEmptyError,
            {
                s3::err::S3ErrorCode::AccessGrantsInstanceNotEmptyError,
                "AccessGrantsInstanceNotEmptyError",
                "Please clean up locations before deleting the access grants instance",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsInstanceNotExistsError,
            {
                s3::err::S3ErrorCode::AccessGrantsInstanceNotExistsError,
                "AccessGrantsInstanceNotExistsError",
                "Access Grants Instance does not exist",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsInstanceResourcePolicyNotExists,
            {
                s3::err::S3ErrorCode::AccessGrantsInstanceResourcePolicyNotExists,
                "AccessGrantsInstanceResourcePolicyNotExists",
                "Access Grants Instance Resource Policy does not exist",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsLocationAlreadyExistsError,
            {
                s3::err::S3ErrorCode::AccessGrantsLocationAlreadyExistsError,
                "AccessGrantsLocationAlreadyExistsError",
                "The specified access grants location already exists",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsLocationNotEmptyError,
            {
                s3::err::S3ErrorCode::AccessGrantsLocationNotEmptyError,
                "AccessGrantsLocationNotEmptyError",
                "Please clean up access grants before deleting access grants location",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsLocationsQuotaExceededError,
            {
                s3::err::S3ErrorCode::AccessGrantsLocationsQuotaExceededError,
                "AccessGrantsLocationsQuotaExceededError",
                "The access grants location quota has been exceeded. Access Grants Locations Quota: {}. Please reach out to S3 if an increase "
                "is required.",
                1,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsQuotaExceededErrorAccessGrants,
            {
                s3::err::S3ErrorCode::AccessGrantsQuotaExceededErrorAccessGrants,
                "AccessGrantsQuotaExceededError",
                "The access grants quota has been exceeded. Access Grants Quota: {}. Please reach out to S3 if an increase is required.",
                1,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAccessGrant,
            {
                s3::err::S3ErrorCode::InvalidAccessGrant,
                "InvalidAccessGrant",
                "The specified Access Grant is invalid",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidAccessGrantsLocation,
            {
                s3::err::S3ErrorCode::InvalidAccessGrantsLocation,
                "InvalidAccessGrantsLocation",
                "The specified Access Grants Location is invalid",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidIamRole,
            {
                s3::err::S3ErrorCode::InvalidIamRole,
                "InvalidIamRole",
                "The specified IAM Role is invalid",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidIdentityCenterInstance,
            {
                s3::err::S3ErrorCode::InvalidIdentityCenterInstance,
                "InvalidIdentityCenterInstance",
                "The specified identity center instance is invalid",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidResourcePolicy,
            {
                s3::err::S3ErrorCode::InvalidResourcePolicy,
                "InvalidResourcePolicy",
                "The specified Resource Policy is invalid",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidResourcePolicyAccessGrants,
            {
                s3::err::S3ErrorCode::InvalidResourcePolicyAccessGrants,
                "InvalidResourcePolicy",
                "The specified Resource Policy is invalid",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTag,
            {
                s3::err::S3ErrorCode::InvalidTag,
                "InvalidTag",
                "This request contains a tag key or value that isn't valid. Valid characters include the following: [a-zA-Z+-=._:/]. Tag keys can "
                "contain up to 128 characters. Tag values can contain up to 256 characters.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchAccessGrantError,
            {
                s3::err::S3ErrorCode::NoSuchAccessGrantError,
                "NoSuchAccessGrantError",
                "The specified access grant does not exist",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::NoSuchAccessGrantsLocationError,
            {
                s3::err::S3ErrorCode::NoSuchAccessGrantsLocationError,
                "NoSuchAccessGrantsLocationError",
                "The specified access grants location does not exist",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::StsNotAuthorizedError,
            {
                s3::err::S3ErrorCode::StsNotAuthorizedError,
                "StsNotAuthorizedError",
                "An error occurred (StsNotAuthorizedError) when calling the GetDataAccess operation: User:access-grants.s3.amazonaws.com is not "
                "authorized to perform:sts:AssumeRole on resource: {}",
                1,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::StsPackedPolicyTooLargeError,
            {
                s3::err::S3ErrorCode::StsPackedPolicyTooLargeError,
                "StsPackedPolicyTooLargeError",
                "An error occurred (StsPackedPolicyTooLargeError) when calling the GetDataAccess operation: Serialized token too large for session",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::StsValidationError,
            {
                s3::err::S3ErrorCode::StsValidationError,
                "StsValidationError",
                "The error message varies depending on the validation error.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidTags,
            {
                s3::err::S3ErrorCode::InvalidTags,
                "InvalidTags",
                "Tag keys cannot start with AWS reserved prefix for system tags.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::InsufficientCapacityFSx,
            {
                s3::err::S3ErrorCode::InsufficientCapacityFSx,
                "InsufficientCapacity",
                "Maximum storage capacity of file system has been reached.",
                0,
                s3::http::HttpStatusCode::InsufficientStorage,
            },
        },
        {
            s3::err::S3ErrorCode::InvalidKey,
            {
                s3::err::S3ErrorCode::InvalidKey,
                "InvalidKey",
                "The specified key is not valid.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::AccessDeniedException,
            {
                s3::err::S3ErrorCode::AccessDeniedException,
                "AccessDeniedException",
                "The action cannot be performed because you do not have the required permission.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::BadRequestException,
            {
                s3::err::S3ErrorCode::BadRequestException,
                "BadRequestException",
                "The request is invalid or malformed.",
                0,
                s3::http::HttpStatusCode::BadRequest,
            },
        },
        {
            s3::err::S3ErrorCode::ConflictException,
            {
                s3::err::S3ErrorCode::ConflictException,
                "ConflictException",
                "The request failed because there is a conflict with a previous write. You can retry the request.",
                0,
                s3::http::HttpStatusCode::Conflict,
            },
        },
        {
            s3::err::S3ErrorCode::ForbiddenException,
            {
                s3::err::S3ErrorCode::ForbiddenException,
                "ForbiddenException",
                "The caller isn't authorized to make the request.",
                0,
                s3::http::HttpStatusCode::Forbidden,
            },
        },
        {
            s3::err::S3ErrorCode::InternalServerErrorException,
            {
                s3::err::S3ErrorCode::InternalServerErrorException,
                "InternalServerErrorException",
                "The request failed due to an internal server error.",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::NotFoundException,
            {
                s3::err::S3ErrorCode::NotFoundException,
                "NotFoundException",
                "The request was rejected because the specified resource could not be found.",
                0,
                s3::http::HttpStatusCode::NotFound,
            },
        },
        {
            s3::err::S3ErrorCode::TooManyRequestsException,
            {
                s3::err::S3ErrorCode::TooManyRequestsException,
                "TooManyRequestsException",
                "The limit on the number of requests per second was exceeded.",
                0,
                s3::http::HttpStatusCode::TooManyRequests,
            },
        },
    };

} // namespace

namespace s3
{
    namespace err
    {
        const s3::err::S3ErrorInfo& getS3ErrorInfo(s3::err::S3ErrorCode s3ErrorCode)
        {
            auto it = kS3ErrorInfoTable.find(s3ErrorCode);
            if (it != kS3ErrorInfoTable.end())
            {
                return it->second;
            }
            return kS3ErrorInfoTable.at(s3::err::S3ErrorCode::InternalError);
        }

        std::string formatErrorMessage(const S3ErrorInfo& info, const std::vector<std::string>& args)
        {
            // caution: messageTemplate不可能为空或空指针，因为在定义不同的S3ErrorInfo的时候就已经确认
            if (info.argCount != args.size())
            {
                SPDLOG_ERROR("Failed to format error message. template: {}, expect args count: {}, actual args count: {}", info.messageTemplate,
                             info.argCount, args.size());
                return info.messageTemplate;
            }

            fmt::dynamic_format_arg_store<fmt::format_context> store;
            for (std::size_t i = 0; i < args.size(); ++i)
            {
                store.push_back(args[i]);
            }

            return fmt::vformat(info.messageTemplate, store);
        }
    } // namespace err
} // namespace s3