
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "ut_config.h"
#include "gtest/gtest.h"
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#ifdef RUN_ALL_TEST_CASE
TEST(leveldb, 001)
{
    std::string dir = "/Users/wu.feihu/tmp";
    std::string dbPath = dir + "/" + "testdb";
    leveldb::DB* db = nullptr;
    leveldb::Options options;
    leveldb::Status status;
    options.create_if_missing = true;
    EXPECT_TRUE(leveldb::DB::Open(options, dbPath, &db).ok());
    EXPECT_TRUE(db->Put(leveldb::WriteOptions(), "k1", "v1").ok());
    std::string value = "";
    db->Get(leveldb::ReadOptions(), "k1", &value);
    EXPECT_TRUE(db->Get(leveldb::ReadOptions(), "k1", &value).ok() && value == "v1");
    status = db->Delete(leveldb::WriteOptions(), "k1");

    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    std::map<std::string, std::string> m0;
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        m0[it->key().ToString()] = it->value().ToString();
    }
    // EXPECT_THAT(arr9, ::testing::ElementsAre("hello", "world", ""));
    delete db;
}
#endif
