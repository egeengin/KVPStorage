#include <gtest/gtest.h>
#include <iostream>
#include <stdlib.h>     // rand
#include "testKVPStorage.h"
#include "CommandHandler.h"

#define TEST_MAX_QUERY_LEN 10
#define TEST_MAX_KEY_LEN TEST_MAX_QUERY_LEN
#define TEST_MAX_VALUE_LEN TEST_MAX_QUERY_LEN

using namespace std;

ICommandHandler *ich = &CommandHandler::GetHandler();

TEST(ICommandHandler_UnitTests, QuasiRandom) {
#define  MONTE_CARLO_TRIAL 100
    int query_len, key_len, value_len;
    string query, key, value, input_line, output_line;

    for (int i = 0; i < MONTE_CARLO_TRIAL; i++) {
        query_len = rand() % 2 ? 3 : 6; // randomly 3 or 6 is selected - so named quasi -
        key_len = rand() % TEST_MAX_KEY_LEN;
        value_len = rand() % TEST_MAX_VALUE_LEN;

        query = testKVPStorage::GenerateRandomString(query_len);
        key = testKVPStorage::GenerateRandomString(key_len);
        value = testKVPStorage::GenerateRandomString(value_len);

        input_line = query + " " + key + " " + value;
        testing::internal::CaptureStdout();
        ich->HandleUserCommands(input_line);
        output_line = testing::internal::GetCapturedStdout();

        if (testKVPStorage::PrintInputs)
            std::cout << "Input: " << input_line << endl;

        if (query == "SET")
            EXPECT_EQ("OK\n", output_line);
        else if ((value_len == 0) && (query == "DELETE" || query == "SET"))
            EXPECT_EQ("OK\n", output_line);
        else
            EXPECT_EQ("Wrong input\n", output_line);
    }
}

TEST(ICommandHandler_UnitTests, Set) {
    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;

    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    string input_line = "SET " + key + " " + value;
    testing::internal::CaptureStdout();
    ich->HandleUserCommands(input_line);
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testKVPStorage::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    if (key_len == 0 || value_len == 0) {
        EXPECT_EQ("Wrong input\n", cmd_output);
    } else {
        EXPECT_EQ("OK\n", cmd_output);
    }
}

TEST(ICommandHandler_UnitTests, Get) {
    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;

    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    string input_line1 = "SET " + key + " " + value;
    ich->HandleUserCommands(input_line1); //First SET [key] [value]

    string input_line2 = "GET " + key;
    testing::internal::CaptureStdout();
    ich->HandleUserCommands(input_line2); //Then check GET [key]
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testKVPStorage::PrintInputs) {
        std::cout << "Input: " << input_line1 << endl;
        std::cout << "Input: " << input_line2 << endl;
    }

    if (key_len == 0) {
        EXPECT_EQ("Wrong input\n", cmd_output);
    } else {
        EXPECT_EQ((std::string) value + "\n", cmd_output);
    }
}

TEST(ICommandHandler_UnitTests, Delete) {
    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;

    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    string input_line1 = "SET " + key + " " + value;
    ich->HandleUserCommands(input_line1); //First SET [key] [value]

    string input_line2 = "DELETE " + key;
    testing::internal::CaptureStdout();
    ich->HandleUserCommands(input_line2); //Then check DELETE [key]
    string cmd_output = testing::internal::GetCapturedStdout();

    if (testKVPStorage::PrintInputs) {
        std::cout << "Input: " << input_line1 << endl;
        std::cout << "Input: " << input_line2 << endl;
    }

    if (key_len == 0) {
        EXPECT_EQ("Wrong input\n", cmd_output);
    } else {
        EXPECT_EQ("OK\n", cmd_output);
    }
}

TEST(ICommandHandler_UnitTests, ExtraInputs) {
    int query_len, key_len, value_len, extra_len;
    string query, key, value, extra, input_line, output_line;

    query_len = rand() % (TEST_MAX_QUERY_LEN - 1) + 1; // at least 1
    key_len = rand() % (TEST_MAX_KEY_LEN - 1) + 1;
    value_len = rand() % (TEST_MAX_VALUE_LEN - 1) + 1;
    extra_len = rand() % (TEST_MAX_QUERY_LEN - 1) + 1;

    query = testKVPStorage::GenerateRandomString(query_len);
    key = testKVPStorage::GenerateRandomString(key_len);
    value = testKVPStorage::GenerateRandomString(value_len);
    extra = testKVPStorage::GenerateRandomString(value_len);

    input_line = query + " " + key + " " + value + " " + extra;
    testing::internal::CaptureStdout();
    ich->HandleUserCommands(input_line);
    output_line = testing::internal::GetCapturedStdout();

    if (testKVPStorage::PrintInputs)
        std::cout << "Input: " << input_line << endl;

    EXPECT_EQ("Wrong input\n", output_line);
}