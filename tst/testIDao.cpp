#include <gtest/gtest.h>
#include <iostream>
#include <stdlib.h>     // rand
#include "testKVPStorage.h"
#include "DaoInMemory.h"

#define TEST_MAX_KEY_LEN 10
#define TEST_MAX_VALUE_LEN 10

using namespace std;

IDao *dao = &DaoInMemory::GetInstance();

TEST(IDao_UnitTests, Set) {
    int key_len = rand() % 10;
    int value_len = rand() % 10;
    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);
    string cmd_output;

    testing::internal::CaptureStdout();
    dao->SetKVP(key, value);
    cmd_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("OK\n", cmd_output);
}

TEST(IDao_UnitTests, GetAfterSet) {
    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;
    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);
    std::string cmd_output;

    dao->SetKVP(key, value);
    testing::internal::CaptureStdout();
    dao->GetKVP(key);
    cmd_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(value + "\n", cmd_output);
}

TEST(IDao_UnitTests, DeleteAfterSet) {
    int key_len = rand() % 10;
    int value_len = rand() % 10;
    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);
    std::string cmd_output;

    dao->SetKVP(key, value);
    testing::internal::CaptureStdout();
    dao->DeleteKVP(key);
    cmd_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("OK\n", cmd_output);
}