/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   test_parse_base_type.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/27 13:04:43
 *
 * @brief  unit test for parse_base_type.h
 *
 **/

#include <gtest/gtest.h>
#include "parse_base_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestParseBaseTypeSuite : public ::testing::Test {
public:
    TestParseBaseTypeSuite() : _base_parser(nullptr) {}
    virtual ~TestParseBaseTypeSuite() {}

    virtual void SetUp() {
        _base_parser = new goodcoder::ParseBaseType();
    }

    virtual void TearDown() {
        if (_base_parser != nullptr) {
            delete _base_parser;
        }
        _base_parser = nullptr;
    }

public:
    goodcoder::ParseBaseType *_base_parser;
};

TEST_F(TestParseBaseTypeSuite, test_parse_int_and_double) {
    std::string test_int = "123";
    std::string test_float = "1.23";

    int int_val = 0;
    _base_parser->parse_column_to_base<int>(test_int, &int_val);
    ASSERT_EQ(123, int_val);

    float float_val = 0.0f;
    _base_parser->parse_column_to_base<float>(test_float, &float_val);
    ASSERT_NEAR(1.23, float_val, 0.001);

    char* str_val = new char[256];
    _base_parser->parse_column_to_base<char*>(test_int, &str_val);
    ASSERT_EQ(0, strcmp("123", str_val));

    test_int = "abc";
    _base_parser->parse_column_to_base<int>(test_int, &int_val);
    ASSERT_EQ(0, int_val);

    test_float = "abc";
    _base_parser->parse_column_to_base<float>(test_float, &float_val);
    ASSERT_NEAR(0, float_val, 0.001);
}
