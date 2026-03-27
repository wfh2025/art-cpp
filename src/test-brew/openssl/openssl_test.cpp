#include <map>
#include <set>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "openssl/err.h"
#include "openssl/sha.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(SHA256, 001)
{
    char input[] = "Hello, OpenSSL!";
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256((unsigned char*)input, strlen(input), hash);
}

#endif