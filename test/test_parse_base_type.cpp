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
 * @brief
 *
 **/

#include <gtest/gtest.h>
#include "parse_base_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS;
}

class TestParseBaseTypeSuite : public ::testing::Test {
public:
    TestParseBaseTypeSuite() {}
    virtual ~TestParseBaseTypeSuite() {}

    virtual void SetUp() {
        _base_parser = new goodcoder::ParseBaseType();
    }

    virtual void TearDown() {
        delete _base_parser;
    }

private:
    goodcoder::ParseBaseType *_base_parser;
};

TEST_F(TestParseBaseTypeSuite, test_parse_int_and_double) {
    std::string test_int = "123";
    std::string test_double = "1.23";
    int int_val = 0;
    double double_val = 0.0;
    _base_parser->parse_column_to_base<int>(test_int, &int_val);
    ASSERT_EQ(123, int_val);
    _base_parser->parse_column_to_base<double>(test_double, &double_val);
    ASSERT_NEAR(1.23, double_val, 0.001);
}
