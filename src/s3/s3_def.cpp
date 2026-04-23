#include "s3_def.hpp"

#include <cctype>
#include <map>
#include <unordered_map>

namespace s3
{
    namespace
    {
        std::string toLowerAscii(const std::string& s)
        {
            std::string out;
            out.reserve(s.size());
            for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
            {
                out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(*it))));
            }
            return out;
        }

        const std::map<S3ApiKind, const char*>& s3ApiKindToNameMap()
        {
            static const std::map<S3ApiKind, const char*> kMap = {
                {S3ApiKind::Unknown, "Unknown"},
                {S3ApiKind::AbortMultipartUpload, "AbortMultipartUpload"},
                {S3ApiKind::CompleteMultipartUpload, "CompleteMultipartUpload"},
                {S3ApiKind::CopyObject, "CopyObject"},
                {S3ApiKind::CreateBucket, "CreateBucket"},
                {S3ApiKind::CreateBucketMetadataConfiguration, "CreateBucketMetadataConfiguration"},
                {S3ApiKind::CreateBucketMetadataTableConfiguration, "CreateBucketMetadataTableConfiguration"},
                {S3ApiKind::CreateMultipartUpload, "CreateMultipartUpload"},
                {S3ApiKind::CreateSession, "CreateSession"},
                {S3ApiKind::DeleteBucket, "DeleteBucket"},
                {S3ApiKind::DeleteBucketAcl, "DeleteBucketAcl"},
                {S3ApiKind::DeleteBucketAnalyticsConfiguration, "DeleteBucketAnalyticsConfiguration"},
                {S3ApiKind::DeleteBucketCors, "DeleteBucketCors"},
                {S3ApiKind::DeleteBucketEncryption, "DeleteBucketEncryption"},
                {S3ApiKind::DeleteBucketIntelligentTieringConfiguration, "DeleteBucketIntelligentTieringConfiguration"},
                {S3ApiKind::DeleteBucketInventoryConfiguration, "DeleteBucketInventoryConfiguration"},
                {S3ApiKind::DeleteBucketLifecycle, "DeleteBucketLifecycle"},
                {S3ApiKind::DeleteBucketMetadataConfiguration, "DeleteBucketMetadataConfiguration"},
                {S3ApiKind::DeleteBucketMetadataTableConfiguration, "DeleteBucketMetadataTableConfiguration"},
                {S3ApiKind::DeleteBucketMetricsConfiguration, "DeleteBucketMetricsConfiguration"},
                {S3ApiKind::DeleteBucketOwnershipControls, "DeleteBucketOwnershipControls"},
                {S3ApiKind::DeleteBucketPolicy, "DeleteBucketPolicy"},
                {S3ApiKind::DeleteBucketReplication, "DeleteBucketReplication"},
                {S3ApiKind::DeleteBucketTagging, "DeleteBucketTagging"},
                {S3ApiKind::DeleteBucketWebsite, "DeleteBucketWebsite"},
                {S3ApiKind::DeleteObject, "DeleteObject"},
                {S3ApiKind::DeleteObjectTagging, "DeleteObjectTagging"},
                {S3ApiKind::DeleteObjects, "DeleteObjects"},
                {S3ApiKind::DeletePublicAccessBlock, "DeletePublicAccessBlock"},
                {S3ApiKind::GetBucketAbac, "GetBucketAbac"},
                {S3ApiKind::GetBucketAccelerateConfiguration, "GetBucketAccelerateConfiguration"},
                {S3ApiKind::GetBucketAcl, "GetBucketAcl"},
                {S3ApiKind::GetBucketAnalyticsConfiguration, "GetBucketAnalyticsConfiguration"},
                {S3ApiKind::GetBucketCors, "GetBucketCors"},
                {S3ApiKind::GetBucketEncryption, "GetBucketEncryption"},
                {S3ApiKind::GetBucketIntelligentTieringConfiguration, "GetBucketIntelligentTieringConfiguration"},
                {S3ApiKind::GetBucketInventoryConfiguration, "GetBucketInventoryConfiguration"},
                {S3ApiKind::GetBucketLifecycle, "GetBucketLifecycle"},
                {S3ApiKind::GetBucketLifecycleConfiguration, "GetBucketLifecycleConfiguration"},
                {S3ApiKind::GetBucketLocation, "GetBucketLocation"},
                {S3ApiKind::GetBucketLogging, "GetBucketLogging"},
                {S3ApiKind::GetBucketMetadataConfiguration, "GetBucketMetadataConfiguration"},
                {S3ApiKind::GetBucketMetadataTableConfiguration, "GetBucketMetadataTableConfiguration"},
                {S3ApiKind::GetBucketMetricsConfiguration, "GetBucketMetricsConfiguration"},
                {S3ApiKind::GetBucketNotification, "GetBucketNotification"},
                {S3ApiKind::GetBucketNotificationConfiguration, "GetBucketNotificationConfiguration"},
                {S3ApiKind::GetBucketOwnershipControls, "GetBucketOwnershipControls"},
                {S3ApiKind::GetBucketPolicy, "GetBucketPolicy"},
                {S3ApiKind::GetBucketPolicyStatus, "GetBucketPolicyStatus"},
                {S3ApiKind::GetBucketReplication, "GetBucketReplication"},
                {S3ApiKind::GetBucketRequestPayment, "GetBucketRequestPayment"},
                {S3ApiKind::GetBucketTagging, "GetBucketTagging"},
                {S3ApiKind::GetBucketVersioning, "GetBucketVersioning"},
                {S3ApiKind::GetBucketWebsite, "GetBucketWebsite"},
                {S3ApiKind::GetObject, "GetObject"},
                {S3ApiKind::GetObjectAcl, "GetObjectAcl"},
                {S3ApiKind::GetObjectAttributes, "GetObjectAttributes"},
                {S3ApiKind::GetObjectLegalHold, "GetObjectLegalHold"},
                {S3ApiKind::GetObjectLockConfiguration, "GetObjectLockConfiguration"},
                {S3ApiKind::GetObjectRetention, "GetObjectRetention"},
                {S3ApiKind::GetObjectTagging, "GetObjectTagging"},
                {S3ApiKind::GetObjectTorrent, "GetObjectTorrent"},
                {S3ApiKind::GetPublicAccessBlock, "GetPublicAccessBlock"},
                {S3ApiKind::HeadBucket, "HeadBucket"},
                {S3ApiKind::HeadObject, "HeadObject"},
                {S3ApiKind::ListBucketAnalyticsConfigurations, "ListBucketAnalyticsConfigurations"},
                {S3ApiKind::ListBucketIntelligentTieringConfigurations, "ListBucketIntelligentTieringConfigurations"},
                {S3ApiKind::ListBucketInventoryConfigurations, "ListBucketInventoryConfigurations"},
                {S3ApiKind::ListBucketMetricsConfigurations, "ListBucketMetricsConfigurations"},
                {S3ApiKind::ListBucketObjects, "ListBucketObjects"},
                {S3ApiKind::ListBuckets, "ListBuckets"},
                {S3ApiKind::ListDirectoryBuckets, "ListDirectoryBuckets"},
                {S3ApiKind::ListMultipartUploads, "ListMultipartUploads"},
                {S3ApiKind::ListObjectVersions, "ListObjectVersions"},
                {S3ApiKind::ListObjects, "ListObjects"},
                {S3ApiKind::ListObjectsV2, "ListObjectsV2"},
                {S3ApiKind::ListParts, "ListParts"},
                {S3ApiKind::PutBucketAbac, "PutBucketAbac"},
                {S3ApiKind::PutBucketAccelerateConfiguration, "PutBucketAccelerateConfiguration"},
                {S3ApiKind::PutBucketAcl, "PutBucketAcl"},
                {S3ApiKind::PutBucketAnalyticsConfiguration, "PutBucketAnalyticsConfiguration"},
                {S3ApiKind::PutBucketCors, "PutBucketCors"},
                {S3ApiKind::PutBucketEncryption, "PutBucketEncryption"},
                {S3ApiKind::PutBucketIntelligentTieringConfiguration, "PutBucketIntelligentTieringConfiguration"},
                {S3ApiKind::PutBucketInventoryConfiguration, "PutBucketInventoryConfiguration"},
                {S3ApiKind::PutBucketLifecycle, "PutBucketLifecycle"},
                {S3ApiKind::PutBucketLifecycleConfiguration, "PutBucketLifecycleConfiguration"},
                {S3ApiKind::PutBucketLogging, "PutBucketLogging"},
                {S3ApiKind::PutBucketMetricsConfiguration, "PutBucketMetricsConfiguration"},
                {S3ApiKind::PutBucketNotification, "PutBucketNotification"},
                {S3ApiKind::PutBucketNotificationConfiguration, "PutBucketNotificationConfiguration"},
                {S3ApiKind::PutBucketOwnershipControls, "PutBucketOwnershipControls"},
                {S3ApiKind::PutBucketPolicy, "PutBucketPolicy"},
                {S3ApiKind::PutBucketReplication, "PutBucketReplication"},
                {S3ApiKind::PutBucketRequestPayment, "PutBucketRequestPayment"},
                {S3ApiKind::PutBucketTagging, "PutBucketTagging"},
                {S3ApiKind::PutBucketVersioning, "PutBucketVersioning"},
                {S3ApiKind::PutBucketWebsite, "PutBucketWebsite"},
                {S3ApiKind::PutObject, "PutObject"},
                {S3ApiKind::PutObjectAcl, "PutObjectAcl"},
                {S3ApiKind::PutObjectLegalHold, "PutObjectLegalHold"},
                {S3ApiKind::PutObjectLockConfiguration, "PutObjectLockConfiguration"},
                {S3ApiKind::PutObjectRetention, "PutObjectRetention"},
                {S3ApiKind::PutObjectTagging, "PutObjectTagging"},
                {S3ApiKind::PutPublicAccessBlock, "PutPublicAccessBlock"},
                {S3ApiKind::RenameObject, "RenameObject"},
                {S3ApiKind::RestoreObject, "RestoreObject"},
                {S3ApiKind::SelectObjectContent, "SelectObjectContent"},
                {S3ApiKind::UpdateBucketMetadataInventoryTableConfiguration, "UpdateBucketMetadataInventoryTableConfiguration"},
                {S3ApiKind::UpdateBucketMetadataJournalTableConfiguration, "UpdateBucketMetadataJournalTableConfiguration"},
                {S3ApiKind::UpdateObjectEncryption, "UpdateObjectEncryption"},
                {S3ApiKind::UploadPart, "UploadPart"},
                {S3ApiKind::UploadPartCopy, "UploadPartCopy"},
                {S3ApiKind::WriteGetObjectResponse, "WriteGetObjectResponse"},
            };
            return kMap;
        }

        const std::unordered_map<std::string, S3ApiKind>& s3ApiKindFromNameMap()
        {
            static const std::unordered_map<std::string, S3ApiKind> kMap = {
                {"unknown", S3ApiKind::Unknown},
                {"abortmultipartupload", S3ApiKind::AbortMultipartUpload},
                {"completemultipartupload", S3ApiKind::CompleteMultipartUpload},
                {"copyobject", S3ApiKind::CopyObject},
                {"createbucket", S3ApiKind::CreateBucket},
                {"createbucketmetadataconfiguration", S3ApiKind::CreateBucketMetadataConfiguration},
                {"createbucketmetadatatableconfiguration", S3ApiKind::CreateBucketMetadataTableConfiguration},
                {"createmultipartupload", S3ApiKind::CreateMultipartUpload},
                {"createsession", S3ApiKind::CreateSession},
                {"deletebucket", S3ApiKind::DeleteBucket},
                {"deletebucketacl", S3ApiKind::DeleteBucketAcl},
                {"deletebucketanalyticsconfiguration", S3ApiKind::DeleteBucketAnalyticsConfiguration},
                {"deletebucketcors", S3ApiKind::DeleteBucketCors},
                {"deletebucketencryption", S3ApiKind::DeleteBucketEncryption},
                {"deletebucketintelligenttieringconfiguration", S3ApiKind::DeleteBucketIntelligentTieringConfiguration},
                {"deletebucketinventoryconfiguration", S3ApiKind::DeleteBucketInventoryConfiguration},
                {"deletebucketlifecycle", S3ApiKind::DeleteBucketLifecycle},
                {"deletebucketmetadataconfiguration", S3ApiKind::DeleteBucketMetadataConfiguration},
                {"deletebucketmetadatatableconfiguration", S3ApiKind::DeleteBucketMetadataTableConfiguration},
                {"deletebucketmetricsconfiguration", S3ApiKind::DeleteBucketMetricsConfiguration},
                {"deletebucketownershipcontrols", S3ApiKind::DeleteBucketOwnershipControls},
                {"deletebucketpolicy", S3ApiKind::DeleteBucketPolicy},
                {"deletebucketreplication", S3ApiKind::DeleteBucketReplication},
                {"deletebuckettagging", S3ApiKind::DeleteBucketTagging},
                {"deletebucketwebsite", S3ApiKind::DeleteBucketWebsite},
                {"deleteobject", S3ApiKind::DeleteObject},
                {"deleteobjecttagging", S3ApiKind::DeleteObjectTagging},
                {"deleteobjects", S3ApiKind::DeleteObjects},
                {"deletepublicaccessblock", S3ApiKind::DeletePublicAccessBlock},
                {"getbucketabac", S3ApiKind::GetBucketAbac},
                {"getbucketaccelerateconfiguration", S3ApiKind::GetBucketAccelerateConfiguration},
                {"getbucketacl", S3ApiKind::GetBucketAcl},
                {"getbucketanalyticsconfiguration", S3ApiKind::GetBucketAnalyticsConfiguration},
                {"getbucketcors", S3ApiKind::GetBucketCors},
                {"getbucketencryption", S3ApiKind::GetBucketEncryption},
                {"getbucketintelligenttieringconfiguration", S3ApiKind::GetBucketIntelligentTieringConfiguration},
                {"getbucketinventoryconfiguration", S3ApiKind::GetBucketInventoryConfiguration},
                {"getbucketlifecycle", S3ApiKind::GetBucketLifecycle},
                {"getbucketlifecycleconfiguration", S3ApiKind::GetBucketLifecycleConfiguration},
                {"getbucketlocation", S3ApiKind::GetBucketLocation},
                {"getbucketlogging", S3ApiKind::GetBucketLogging},
                {"getbucketmetadataconfiguration", S3ApiKind::GetBucketMetadataConfiguration},
                {"getbucketmetadatatableconfiguration", S3ApiKind::GetBucketMetadataTableConfiguration},
                {"getbucketmetricsconfiguration", S3ApiKind::GetBucketMetricsConfiguration},
                {"getbucketnotification", S3ApiKind::GetBucketNotification},
                {"getbucketnotificationconfiguration", S3ApiKind::GetBucketNotificationConfiguration},
                {"getbucketownershipcontrols", S3ApiKind::GetBucketOwnershipControls},
                {"getbucketpolicy", S3ApiKind::GetBucketPolicy},
                {"getbucketpolicystatus", S3ApiKind::GetBucketPolicyStatus},
                {"getbucketreplication", S3ApiKind::GetBucketReplication},
                {"getbucketrequestpayment", S3ApiKind::GetBucketRequestPayment},
                {"getbuckettagging", S3ApiKind::GetBucketTagging},
                {"getbucketversioning", S3ApiKind::GetBucketVersioning},
                {"getbucketwebsite", S3ApiKind::GetBucketWebsite},
                {"getobject", S3ApiKind::GetObject},
                {"getobjectacl", S3ApiKind::GetObjectAcl},
                {"getobjectattributes", S3ApiKind::GetObjectAttributes},
                {"getobjectlegalhold", S3ApiKind::GetObjectLegalHold},
                {"getobjectlockconfiguration", S3ApiKind::GetObjectLockConfiguration},
                {"getobjectretention", S3ApiKind::GetObjectRetention},
                {"getobjecttagging", S3ApiKind::GetObjectTagging},
                {"getobjecttorrent", S3ApiKind::GetObjectTorrent},
                {"getpublicaccessblock", S3ApiKind::GetPublicAccessBlock},
                {"headbucket", S3ApiKind::HeadBucket},
                {"headobject", S3ApiKind::HeadObject},
                {"listbucketanalyticsconfigurations", S3ApiKind::ListBucketAnalyticsConfigurations},
                {"listbucketintelligenttieringconfigurations", S3ApiKind::ListBucketIntelligentTieringConfigurations},
                {"listbucketinventoryconfigurations", S3ApiKind::ListBucketInventoryConfigurations},
                {"listbucketmetricsconfigurations", S3ApiKind::ListBucketMetricsConfigurations},
                {"listbucketobjects", S3ApiKind::ListBucketObjects},
                {"listbuckets", S3ApiKind::ListBuckets},
                {"listdirectorybuckets", S3ApiKind::ListDirectoryBuckets},
                {"listmultipartuploads", S3ApiKind::ListMultipartUploads},
                {"listobjectversions", S3ApiKind::ListObjectVersions},
                {"listobjects", S3ApiKind::ListObjects},
                {"listobjectsv2", S3ApiKind::ListObjectsV2},
                {"listparts", S3ApiKind::ListParts},
                {"putbucketabac", S3ApiKind::PutBucketAbac},
                {"putbucketaccelerateconfiguration", S3ApiKind::PutBucketAccelerateConfiguration},
                {"putbucketacl", S3ApiKind::PutBucketAcl},
                {"putbucketanalyticsconfiguration", S3ApiKind::PutBucketAnalyticsConfiguration},
                {"putbucketcors", S3ApiKind::PutBucketCors},
                {"putbucketencryption", S3ApiKind::PutBucketEncryption},
                {"putbucketintelligenttieringconfiguration", S3ApiKind::PutBucketIntelligentTieringConfiguration},
                {"putbucketinventoryconfiguration", S3ApiKind::PutBucketInventoryConfiguration},
                {"putbucketlifecycle", S3ApiKind::PutBucketLifecycle},
                {"putbucketlifecycleconfiguration", S3ApiKind::PutBucketLifecycleConfiguration},
                {"putbucketlogging", S3ApiKind::PutBucketLogging},
                {"putbucketmetricsconfiguration", S3ApiKind::PutBucketMetricsConfiguration},
                {"putbucketnotification", S3ApiKind::PutBucketNotification},
                {"putbucketnotificationconfiguration", S3ApiKind::PutBucketNotificationConfiguration},
                {"putbucketownershipcontrols", S3ApiKind::PutBucketOwnershipControls},
                {"putbucketpolicy", S3ApiKind::PutBucketPolicy},
                {"putbucketreplication", S3ApiKind::PutBucketReplication},
                {"putbucketrequestpayment", S3ApiKind::PutBucketRequestPayment},
                {"putbuckettagging", S3ApiKind::PutBucketTagging},
                {"putbucketversioning", S3ApiKind::PutBucketVersioning},
                {"putbucketwebsite", S3ApiKind::PutBucketWebsite},
                {"putobject", S3ApiKind::PutObject},
                {"putobjectacl", S3ApiKind::PutObjectAcl},
                {"putobjectlegalhold", S3ApiKind::PutObjectLegalHold},
                {"putobjectlockconfiguration", S3ApiKind::PutObjectLockConfiguration},
                {"putobjectretention", S3ApiKind::PutObjectRetention},
                {"putobjecttagging", S3ApiKind::PutObjectTagging},
                {"putpublicaccessblock", S3ApiKind::PutPublicAccessBlock},
                {"renameobject", S3ApiKind::RenameObject},
                {"restoreobject", S3ApiKind::RestoreObject},
                {"selectobjectcontent", S3ApiKind::SelectObjectContent},
                {"updatebucketmetadatainventorytableconfiguration", S3ApiKind::UpdateBucketMetadataInventoryTableConfiguration},
                {"updatebucketmetadatajournaltableconfiguration", S3ApiKind::UpdateBucketMetadataJournalTableConfiguration},
                {"updateobjectencryption", S3ApiKind::UpdateObjectEncryption},
                {"uploadpart", S3ApiKind::UploadPart},
                {"uploadpartcopy", S3ApiKind::UploadPartCopy},
                {"writegetobjectresponse", S3ApiKind::WriteGetObjectResponse},
            };
            return kMap;
        }
    } // namespace

    const char* s3ApiKindToString(S3ApiKind apiKind) noexcept
    {
        const std::map<S3ApiKind, const char*>& map = s3ApiKindToNameMap();
        const std::map<S3ApiKind, const char*>::const_iterator it = map.find(apiKind);
        if (it != map.end())
        {
            return it->second;
        }
        return "Unknown";
    }

    S3ApiKind stringToS3ApiKind(const std::string& s) noexcept
    {
        if (s.empty())
        {
            return S3ApiKind::Unknown;
        }

        const std::unordered_map<std::string, S3ApiKind>& map = s3ApiKindFromNameMap();
        const std::unordered_map<std::string, S3ApiKind>::const_iterator it = map.find(toLowerAscii(s));
        if (it != map.end())
        {
            return it->second;
        }
        return S3ApiKind::Unknown;
    }
} // namespace s3
